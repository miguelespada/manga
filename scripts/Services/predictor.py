from flask import Flask
app = Flask(__name__)
from flask import jsonify

@app.route('/ping')
def ping():
  return jsonify({"ok": "2"})


@app.route('/predict/<values>')
def predict(values):
  print(values.split('&'))
  data = map(lambda x: x.split(','), values.split(';')[:-1])
  lines = [x[1] for x in data]
  midiNotes = [x[0] for x in data]
  return jsonify({"ok": "ok"})