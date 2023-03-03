import time
import paho.mqtt.client as paho
broker="192.168.8.130"
client= paho.Client("client-002")

print("connecting to broker ",broker)
client.connect(broker, 1883)

def on_message(client, userdata, message):
    time.sleep(1)
    print("received message =",str(message.payload.decode("utf-8")))


client.on_message=on_message
client.subscribe("CCO5/test")
client.loop_forever()
