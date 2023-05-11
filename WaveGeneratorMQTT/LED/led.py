import streamlit as st
import paho.mqtt.client as mqtt
import time


st.title("MQTT")

client = mqtt.Client()

if st.button('OFF'):
    client.connect("test.mosquitto.org",1883,60)
    client.publish("led/control", "0")
    client.disconnect()
    st.write("LED is OFF")
    
if st.button('ON'):
    client.connect("test.mosquitto.org",1883,60)
    client.publish("led/control", "1")
    client.disconnect()
    st.write("LED is ON")
    