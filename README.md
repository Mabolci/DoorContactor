# SimpleContactron
Simple contactron connecting with remote mqtt broker based on esp8266 NodeMcu
This is part of submission for university subject with the shortest acronime possible -- UMPANUMiW

# Main objectives
Software for microcontroller able to communicate via MQQT with Domoticz in order to propagate the information about the state of the door/window

# Hardware used
ESP 8266 (NodeMCU with 4MB flash) and contactor.

# Usage
In the code, replace `"WIFI_SSID"` and `"WIFI_PASSWORD"` with your network's ssid and password, than, replace `"MQTT_USERNAME"`, `"MQTT_PASSWORD"` and `"MQTT_SERVER_NAME"` as well. Sert proper port via variable `mqtt_port`. Plug the contactor to the `D4` pin on the NodeMcu board and ground.
Flash microcontroller and plug it into the internet

