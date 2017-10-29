import magenta
from flask import Flask
app = Flask(__name__)
from flask import jsonify
import generator

@app.route('/ping')
def ping():
  return jsonify({"ok": "1"})


@app.route('/predict/<values>')
def predict(values):

  primer = generator.encodePrimer(values)
  prediction = generator.generate(primer, temperature=1.2)

  return jsonify({"prediction": prediction})


@app.route('/planner/<changes>')
def plan(changes):
  return jsonify({"plan": changes})


app.run(host= '0.0.0.0')