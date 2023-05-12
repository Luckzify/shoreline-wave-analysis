import streamlit as st
import paho.mqtt.client as mqtt
import time

st.set_page_config(
    page_title="Wave Generator",
    page_icon="🌊",
    initial_sidebar_state="expanded",
)

def wavetype_coversion(wavetype):
    if type(wavetype) == str:
        if wavetype == 'None':
            return  0
        elif wavetype == 'Mono Pulse':
            return 1
        elif wavetype == 'Constant Pulse':
            return 2
        elif wavetype == 'Fast Slow Pulse':
            return 3
    else:
        if wavetype == 0:
            return "None"
        elif wavetype == 1:
            return "Mono Pulse"
        elif wavetype == 2:
            return "Constant Pulse"
        elif wavetype == 3:
            return "Fast Slow Pulse"

client = mqtt.Client()

wavetype = "None"
speed = 0
distance = 0

st.header("Dashboard 🌊")

slider_tab, number_tab = st.tabs(["Slider", "Number"])

with slider_tab:
    with st.form("slider_form"):
        wavetype = st.selectbox(
            'Wavetype:',
            ('None','Mono Pulse','Constant Pulse', 'Fast Slow Pulse'))

        speed = st.slider('Speed:', 0, 7500, value=1000, step=100)
        distance = st.slider('Distance:', 0, 200, value=100, step=10)
        
        submitted = st.form_submit_button("Update and run")
        if submitted:
            wavetype = wavetype_coversion(wavetype)
            client.connect("test.mosquitto.org",1883,60)
            client.publish("wave/motor", f"{wavetype} {speed} {distance}")
            client.disconnect()
            st.success("Running!")
            time.sleep(1)

with number_tab:
    with st.form("number_form"):
        wavetype = st.selectbox(
            'Wavetype:',
            ('None','Mono Pulse','Constant Pulse', 'Fast Slow Pulse'))

        speed = st.number_input('Speed:', 0, value=1000, max_value=7500)
        distance = st.number_input('Distance:', 0, value=100, max_value=200)
        
        submitted = st.form_submit_button("Update and run")
        if submitted:
            wavetype = wavetype_coversion(wavetype)
            client.connect("test.mosquitto.org",1883,60)
            client.publish("wave/motor", f"{wavetype} {speed} {distance}")
            client.disconnect()
            st.success("Running!")
            time.sleep(1)
    