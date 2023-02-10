# Import dependencies

import pickle
from flask import Flask, request, render_template

# Create flask application

flask_app = Flask(__name__)

# Load the Multinomial Naive Bayes model and the TF-IDF Vectorizer

model = pickle.load(open("model.pkl", "rb"))
vectorizer = pickle.load(open("vectorizer.pkl", "rb"))

@flask_app.route("/")
def home():
    return render_template("index.html")

@flask_app.route("/predict", methods = ["POST"])
def predict():
    if request.method == "POST":
        # Obtain input from "index.html"

        sms = request.form['sms']
        input_sms = [sms]

        # Convert the input SMS to a numerical representation using TF-IDF
        
        input_sms_features = vectorizer.transform(input_sms)

        # Make prediction on the input SMS using Naive Bayes model (Ham = 1 & Spam = 0)

        prediction_input_sms = model.predict(input_sms_features)
        
    if prediction_input_sms == 0:
        return render_template("index.html", spam_sms = "The SMS is a Spam!", prev_input = sms)
    else:
        return render_template("index.html", ham_sms = "The SMS is a Ham (not Spam)!", prev_input = sms)

if __name__ == "__main__":
    flask_app.run(debug=True)