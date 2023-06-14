#import time
from datetime import datetime
import paho.mqtt.client as paho
broker="test.mosquitto.org"
client= paho.Client("client-002")
#file = open("example.txt", "w")

print("connecting to broker ",broker)
client.connect(broker, 1883)
print("connected to broker ",broker)

def on_message(client, userdata, message):
    #ts=time.time()
    time_now = datetime.now()
    #current_time = time_now.strftime("%H:%M:%S")
    xyz=str(time_now)+"  ---> "+str(message.payload.decode("utf-8"))
    print(xyz)
    #file.write(xyz)


client.on_message=on_message
client.subscribe("VRcycling/test")
client.loop_forever()
#file.close()