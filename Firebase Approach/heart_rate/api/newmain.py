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
    client.subscribe("VRcycling/UserA/Speed")

def on_message(client, userdata, msg):
    message = msg.payload.decode()
    print("Received message: " + msg.payload.decode())

    doc_ref = db.collection(u'UserOneSpeed').document()
    timestamp = firestore.SERVER_TIMESTAMP
    doc_ref.set({
        u'speed': message,
        u'time': timestamp
    })

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.8.183", 1883, 60)
client.loop_start()

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("VRcycling/UserB/Speed")

def on_message(client, userdata, msg):
    message = msg.payload.decode()
    print("Received message: " + msg.payload.decode())

    doc_ref = db.collection(u'UserTwoSpeed').document()
    timestamp = firestore.SERVER_TIMESTAMP
    doc_ref.set({
        u'speed': message,
        u'time': timestamp
    })

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.8.183", 1883, 60)
client.loop_start()

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("VRcycling/UserA/Distance")

def on_message(client, userdata, msg):
    message = msg.payload.decode()
    print("Received message: " + msg.payload.decode())

    doc_ref = db.collection(u'UserOneDistance').document()
    timestamp = firestore.SERVER_TIMESTAMP
    doc_ref.set({
        u'distance': message,
        u'time': timestamp
    })

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.8.183", 1883, 60)
client.loop_start()


def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("VRcycling/UserB/Distance")

def on_message(client, userdata, msg):
    message = msg.payload.decode()
    print("Received message: " + msg.payload.decode())

    doc_ref = db.collection(u'UserTwoDistance').document()
    timestamp = firestore.SERVER_TIMESTAMP
    doc_ref.set({
        u'distance': message,
        u'time': timestamp
    })

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.8.183", 1883, 60)
client.loop_start()


def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("VRcycling/UserA/HR")

def on_message(client, userdata, msg):
    message = msg.payload.decode()
    print("Received message: " + msg.payload.decode())

    doc_ref = db.collection(u'UserOneHeart').document()
    timestamp = firestore.SERVER_TIMESTAMP
    doc_ref.set({
        u'bpm': message,
        u'time': timestamp
    })

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.8.183", 1883, 60)
client.loop_start()


def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("VRcycling/UserB/HR")

def on_message(client, userdata, msg):
    message = msg.payload.decode()
    print("Received message: " + msg.payload.decode())

    doc_ref = db.collection(u'UserTwoHeart').document()
    timestamp = firestore.SERVER_TIMESTAMP
    doc_ref.set({
        u'bpm': message,
        u'time': timestamp
    })

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.8.183", 1883, 60)
client.loop_start()


def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("VRcycling/UserA/SPO2")

def on_message(client, userdata, msg):
    message = msg.payload.decode()
    print("Received message: " + msg.payload.decode())

    doc_ref = db.collection(u'UserOneOxygen').document()
    timestamp = firestore.SERVER_TIMESTAMP
    doc_ref.set({
        u'spo2': message,
        u'time': timestamp
    })

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.8.183", 1883, 60)
client.loop_start()

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("VRcycling/UserB/SPO2")

def on_message(client, userdata, msg):
    message = msg.payload.decode()
    print("Received message: " + msg.payload.decode())

    doc_ref = db.collection(u'UserTwoOxygen').document()
    timestamp = firestore.SERVER_TIMESTAMP
    doc_ref.set({
        u'spo2': message,
        u'time': timestamp
    })

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message


client.connect("192.168.8.183", 1883, 60)
client.loop_start()

@app.route('/')
def home():
    return 'Hello, world!'

if __name__ == '__main__':
    app.run()



