import time
import random
from flask import Flask, request
from firebase_admin import firestore
from config.firebase import firebase_app
from apscheduler.schedulers.background import BackgroundScheduler

import paho.mqtt.client as mqtt

# Initialize Flask app
app = Flask(__name__)

# Initialize Firestore client
db = firestore.client()

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("VirtualCycling/lak")

def on_message(client, userdata, msg):
    message = msg.payload.decode()
    print("Received message: " + msg.payload.decode())

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message


client.connect("test.mosquitto.org", 1883, 60)



@app.route('/')
def home():
    return 'Hello, world!'

def insert_heart_rate(msg=85):
    random_number = msg

    # Store heart rate in Firestore
    doc_ref = db.collection(u'UserOneHeart').document()
    timestamp = firestore.SERVER_TIMESTAMP
    doc_ref.set({
        u'bpm': random_number,
        u'time': timestamp
    })

def insert_bicycle_speed():
    random_number = round(random.uniform(0, 30), 2)

    # Store bicycle speed in Firestore
    doc_ref = db.collection(u'UserOneBicycle').document()
    timestamp = firestore.SERVER_TIMESTAMP
    doc_ref.set({
        u'speed': random_number,
        u'time': timestamp
    })

scheduler = BackgroundScheduler(daemon=True)
scheduler.add_job(func=insert_heart_rate, trigger='interval', seconds=5)
scheduler.add_job(func=insert_bicycle_speed, trigger='interval', seconds=5)
scheduler.start()

if __name__ == '__main__':
    app.run()

client.loop_start()

while True:
    # Continue with other tasks or add a delay to prevent the script from exiting immediately
    pass