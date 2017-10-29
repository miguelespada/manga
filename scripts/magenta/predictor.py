import magenta
from flask import Flask
app = Flask(__name__)
from flask import jsonify
import generator
from random import random

@app.route('/ping')
def ping():
  return jsonify({"ok": "1"})


@app.route('/predict/<values>')
def predict(values):

  prediction = -1 
  temp = 1.1 + random() / 10.0

  while prediction == -1:
    primer = generator.encodePrimer(values)
    prediction = generator.generate(primer, temperature=temp)
    print temp
    temp += 0.05


  return jsonify({"prediction": prediction})


@app.route('/planner/<changes>')
def plan(changes):
  return jsonify({"plan": changes})


app.run(host= '0.0.0.0')