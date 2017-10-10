from flask import Flask
app = Flask(__name__)
from flask import jsonify

@app.route('/ping')
def ping():
    return jsonify({"ok": "1"})