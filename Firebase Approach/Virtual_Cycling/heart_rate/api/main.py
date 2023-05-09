import time
import random
from flask import Flask, request
from firebase_admin import firestore
from config.firebase import firebase_app
from apscheduler.schedulers.background import BackgroundScheduler

# Initialize Flask app
app = Flask(__name__)

# Initialize Firestore client
db = firestore.client()

@app.route('/')
def home():
    return 'Hello, world!'

def insert_heart_rate():
    random_number = random.randint(60, 90)

    # Store heart rate in Firestore
    doc_ref = db.collection(u'heart_rate').document()
    timestamp = firestore.SERVER_TIMESTAMP
    doc_ref.set({
        u'rate': random_number,
        u'time': timestamp
    })

def insert_bicycle_speed():
    random_number = round(random.uniform(0, 30), 2)

    # Store bicycle speed in Firestore
    doc_ref = db.collection(u'bicycle_speed').document()
    timestamp = firestore.SERVER_TIMESTAMP
    doc_ref.set({
        u'speed': random_number,
        u'time': timestamp
    })

scheduler = BackgroundScheduler(daemon=True)
scheduler.add_job(func=insert_heart_rate, trigger='interval', seconds=10)
scheduler.add_job(func=insert_bicycle_speed, trigger='interval', seconds=2)
scheduler.start()

if __name__ == '__main__':
    app.run()
