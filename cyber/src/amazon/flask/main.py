from flask import Flask, render_template, redirect, url_for ,request

from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField
from wtforms.validators import DataRequired

import os
import requests
from ast import literal_eval

app = Flask(__name__)
app.config['SECRET_KEY'] = "secret keyyyy123"

class LocationForm(FlaskForm):
    name = StringField('Enter city', validators=[DataRequired()])
    submit = SubmitField('Search')

@app.route("/" , methods=["GET", "POST"])
def index():
    name = None
    form  = LocationForm()
    if form.validate_on_submit():
        key =  "ba19daa0b8174964b837b2033758eedd"
        base_url = "http://api.openweathermap.org/data/2.5/" 
        data = requests.get(base_url + "weather?q=" + request.form['name'] + "&APPID=" +key).content
        data = literal_eval(data.decode())
        if(data["cod"] == 200):
            return render_template('location.html' ,data = data)
        return render_template('err_page.html' ,err_code = data["cod"])

    return render_template('index.html' ,name = name ,form = form)

if __name__ == "__main__":
    app.debug = True
    app.run(host=os.getenv('IP', '127.0.0.1'), 
            port=int(os.getenv('PORT', 3031)))
