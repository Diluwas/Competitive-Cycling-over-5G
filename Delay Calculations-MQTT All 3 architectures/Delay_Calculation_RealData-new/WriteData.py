#import time
from datetime import datetime
import paho.mqtt.client as paho
broker="test.mosquitto.org"
client= paho.Client("client-002")


print("connecting to broker ",broker)
client.connect(broker, 1883)

def on_message(client, userdata, message):
    #ts=time.time()
    #time_now = datetime.now()
    #current_time = time_now.strftime("%H:%M:%S")
    xyz=str(message.payload.decode("utf-8"))
    print(message.payload.decode("utf-8"))
    #with open("G:\FYP\ESP32 and Gyroscope\Delay_Calculation_RealData-new\my.txt", "a") as file2:
        #file2.write(str(xyz)+"\n")


client.on_message=on_message
client.subscribe("VRcycling/test1")
client.loop_forever()
