This is a little project i wrote for my teacher, it's an esp32 project, that controlls a 40m long chaing of LED lights via a locally hosted website.
It can be built using platformio, the dependecies are already listed in `platformio.ini`, and it should work just by running `pio run`

The LED strip is connected on pin 18.
The esp itself has two "modes", either it creates an AP that you can connect to, or it connects to a WiFi network. 
If the WiFi ssid and password are empty it starts an AP, otherwise it connects to a Wifi Netowrk.
When entering the ssid and password for a WiFi network they are then saved onto the esp memory, so they can later be read.

Via the website you can controll:
- if the LEDs are on, off or automatically controlled (they turn on between 5:30-7:30, and 16:00-22:00 GMT+1)
- the brightness
- nothing else
