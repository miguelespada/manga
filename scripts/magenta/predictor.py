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
  prediction = generator.generate(primer, temperature=1.1)

  return jsonify({"prediction": prediction})