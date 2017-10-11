import magenta
import ast
import time
import numpy as np
from random import randint
import os

import tensorflow as tf
import magenta

from magenta.models.drums_rnn import drums_rnn_config_flags
from magenta.models.drums_rnn import drums_rnn_model
from magenta.models.drums_rnn import drums_rnn_sequence_generator

from magenta.protobuf import generator_pb2
from magenta.protobuf import music_pb2
import pretty_midi


humanNotes = [36, 45, 46]
machineNotes = [38, 48, 51]
mapping = {}

mapping[42] = 51
mapping[49] = -1
mapping[50] = 48


def binNotes(notes, length = 0.125):
    beats = notes[-1].start / length
    bins = [[] for i in range( int(beats + 1) )]
    for note in notes: 
        beat = int(note.start / length)
        midi = remap(note.pitch)
        if midi != -1: bins[beat].append(midi)
    return bins

def uniqueNotes(bins):
    return set(sum(bins, []))

def fragment(bins, i, length=12):
    i = (i % (len(bins) / length))
    return bins[length*i: length*(i + 1)]


def remap(pitch):
    if pitch in humanNotes: return -1
    elif pitch in machineNotes: return pitch
    return mapping[pitch]

def binNotes(notes, length = 0.125):
    beats = notes[-1].start / length
    bins = [[] for i in range( int(beats + 1) )]
    for note in notes: 
        beat = int(note.start / length)
        midi = remap(note.pitch)
        if midi != -1: bins[beat].append(midi)
    return bins

def getDistance(fragment, primer_drums):
  distance = 0
  for i in range(len(primer_drums)):
      s = frozenset(fragment[i])
      p = primer_drums[i]
      distance += len(s.union(p).difference(p))
  return distance

def encondeFragment(frag):
  ss = ""
  for n in machineNotes:
      s = str(n) + ","
      for f in frag:
          if n in f: 
              s += "1"
          else:
              s += "0"
      ss += s
      ss += ";"
  return ss

def encodePrimer(values):
    data = map(lambda x: x.split(','), values.split(';')[:-1])
    lines = [x[1] for x in data]
    midiNotes = [x[0] for x in data]

    primer = []
    for i in range(len(lines[0])):
        beat = []
        for j in range(len(midiNotes)):
            if lines[j][i] == '1':
                beat.append(int(midiNotes[j]))
        primer.append(tuple(beat))
        
    return str(primer)
    
bundle_file = os.path.expanduser("drum_kit_rnn.mag")
bundle = magenta.music.read_bundle_file(bundle_file)

config_id = bundle.generator_details.id
config = drums_rnn_model.default_configs[config_id]

beam_size = 1
branch_factor = 1

config.hparams.batch_size = min(
      config.hparams.batch_size, beam_size * branch_factor)


generator = drums_rnn_sequence_generator.DrumsRnnSequenceGenerator(
  model=drums_rnn_model.DrumsRnnModel(config),
  details=config.details,
  steps_per_quarter=config.steps_per_quarter,
  bundle=bundle)




example = "[(36,45), (), (36,), (), (36,), (36,), (), (36,), (36,46,), (45,), (36,46,), ()]"

def generate(primer = example, qpm = 120, num_steps = 120, 
            temperature = 1, branch_factor=1, beam_size=2, steps_per_iteration=1):
   
  primer_drums = magenta.music.DrumTrack(
      [frozenset(pitches)
       for pitches in ast.literal_eval(primer)])

  primer_sequence = primer_drums.to_sequence(qpm=qpm)
  seconds_per_step = 60.0 / qpm / generator.steps_per_quarter
  total_seconds = num_steps * seconds_per_step
  generator_options = generator_pb2.GeneratorOptions()

  input_sequence = primer_sequence
  last_end_time = (max(n.end_time for n in primer_sequence.notes)
                   if primer_sequence.notes else 0)

  generate_section = generator_options.generate_sections.add(
      start_time=last_end_time + seconds_per_step,
      end_time=total_seconds)

  if generate_section.start_time >= generate_section.end_time:
    tf.logging.fatal(
      'Priming sequence is longer than the total number of steps '
      'requested: Priming sequence length: %s, Generation length '
      'requested: %s',
      generate_section.start_time, total_seconds)
  else:
    generator_options.args['temperature'].float_value = temperature
    generator_options.args['beam_size'].int_value = beam_size
    generator_options.args['branch_factor'].int_value = branch_factor
    generator_options.args['steps_per_iteration'].int_value = steps_per_iteration

    generated_sequence = generator.generate(input_sequence, generator_options)
    generated_midi = magenta.music.sequence_proto_to_pretty_midi(generated_sequence)
    instrument = generated_midi.instruments[1]

  bins = binNotes(instrument.notes)

  distances = []
  for i in range(12):
    distances.append(getDistance(fragment(bins, i), primer_drums))

  # print "MAX distance: ", max(distances)
  # print "MAX fragment: ", np.argmax(distances)
  # print "AVG distance: ", np.average(distances)

  return encondeFragment(fragment(bins, np.argmax(distances)))

