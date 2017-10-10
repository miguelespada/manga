from flask import Flask
app = Flask(__name__)
from flask import jsonify

@app.route('/ping')
def ping():
    return jsonify({"ok": "2"})


@app.route('/predict/<values>')
def predict(values):
    return jsonify({"ok": values})