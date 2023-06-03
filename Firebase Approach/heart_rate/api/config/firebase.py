import firebase_admin
from firebase_admin import credentials

cred = credentials.Certificate("./config/credentials.json")

# Initialize Firebase app
firebase_app = firebase_admin.initialize_app(cred)