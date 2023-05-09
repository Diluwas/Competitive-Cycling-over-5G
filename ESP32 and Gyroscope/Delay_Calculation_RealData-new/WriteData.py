#import time
from datetime import datetime
import paho.mqtt.client as paho
broker="test.mosquitto.org"
client= paho.Client("client-002")
file = open("example.txt", "w")

print("connecting to broker ",broker)
client.connect(broker, 1883)

def on_message(client, userdata, message):
    #ts=time.time()
    time_now = datetime.now()
    current_time = time_now.strftime("%H:%M:%S")
    xyz=current_time+"  ---> "+str(message.payload.decode("utf-8"))
    print(xyz)
    file.write(xyz)


client.on_message=on_message
client.subscribe("Mytest")
client.loop_forever()
file.close()