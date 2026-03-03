# Embodiment & Sound

## Breathing sensors

Setup:

1. Plug in the router

2. Open `read_ohm_wifi_esp32` in the Arduino IDE

3. Connect the ESP via the micro-usb cable to the computer

4. In the code, change the IP address and port (line 11, 12)

5. Adjust value range if necessary

    - The Serial console (open with magnifying glass on the top right) should already show you readings (115200 baud rate)
    - Line 72 has the min and max values you can change to what you are reading right now

6. Disconnect the ESP from the computer

7. Connect the battery pins on the ESP and after a moment you should be able to receive the messages in TouchDesigner

That's it!

Disconnecting: better to disconnect the battery at the pins (and not at the clip).


### FAQ

- What board should I select?
  DOIT ESP32 DEVKIT V1

- What port should I select?
  Despends on your computer!

-
