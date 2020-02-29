#/bin/bash

# mosquitto_install.sh
# simple install and enable of mosquitto message broker on raspberry pi

sudo apt install mosquitto mosquitto-clients

# /* enables the broker and restarts after reboot
sudo systemctl enable mosquitto  

# /* check status of the broker
sudo systemctl status mosquitto 
