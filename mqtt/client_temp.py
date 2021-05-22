import paho.mqtt.client as mqtt         #import the client1
import time
import io

def on_message(client, userdata, message):
    print("message received " ,str(message.payload.decode("utf-8")))
    print("message topic=",message.topic)
    print("message qos=",message.qos)
    print("message retain flag=",message.retain)

def get_temp():
    temp_file = open("/sys/class/thermal/thermal_zone0/temp", "r")
    tempC = float(temp_file.readline()) / 1000
    cputemp = "CPU temp: %s" % tempC
    temp_file.close()
    return cputemp

broker_address="localhost"

print("creating new instance")
client = mqtt.Client("watts_temp") #create new instance
client.on_message=on_message #attach function to callback

print("connecting to broker")
client.connect(broker_address) #connect to broker

# print("Subscribing to topic","watts/temp")
# client.subscribe("watts/temp")

client.loop_start() #start the loop
while True:
    print("Publishing message to topic","watts/temp")
    client.publish("watts/temp", get_temp())
    time.sleep(4) # wait
client.loop_stop() #stop the loop
