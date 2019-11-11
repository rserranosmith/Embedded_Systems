# Ultrasonic Sensor

Created Fall 2019

An ultrasonic sensor works by sending and recieving sound pulses, similar to echolocation. The HC-SR04 works in the following manner:

- To tell the sensor to send the sound pulses, the `trigger` must be held high for at least 10us.
- 8 high frequency pulses are sent after the trigger is brought back low.
- When the sensor recieves the sound pulses back, an electronic pulse is sent through the `echo` pin and is held high for amount of time that it took for the sensor to recieve the sound pulse.

Measuring the amount of time that the `echo` pin was held high allows for the discovery of how far an object is from the sensor.

![alt text](https://www.electronicwings.com/public/images/user_images/images/Sensor%20%26%20Modules/Ultrasonic%20module%20HC-SR%2004/2_Ultrasonic_module_timing_diagram.png)

Reference: Electronic Wings

## Parts List

---

| Part                      | Quantity |
| ------------------------- | -------- |
| LED (Optional)            | 1        |
| 220-Ohm Resistor          | 1        |
| HC-SR04 Ultrasonic Sensor | 1        |

## Wiring Up

---

| Pin         | Port   |
| ----------- | ------ |
| VCC         | 5v     |
| GND         | Ground |
| Trigger     | PORTB1 |
| Echo        | PORTD2 |
| LED (Anode) | PORTB3 |

## Formula

---

<br>
Clock Speed:

16000000 Hz / 8 = 2000000 Hz

1 / 2000000 Hz = `0.0000005 seconds (0.5 us)`
<br> <br> <br>
Distance:

Speed of Sounds - 343 m/s

343 m/s x (100 cm/m) x (10^-6 s/us) = 0.0343 cm/us

0.0343 ~ (35/1024)

Distance = 0.5 x clkCounts x (35/1024) / 2

Distance = (clkCounts / 4) x (35/1024)

`Distance = (clkCounts x 35) / 4096`

## Compilation

---

NOTE: Compilation instructions are for Mac. Please read the makefile and make the appropriate changes for windows.

Step 1: Connect the arduino to the computer.

Step 2: Type:

```
ls /dev/tty.usbmodem*
```

Step 3: Copy the output and change line 31 of the makefile

```
PROGRAMMER = -c arduino -b 115200 -P /dev/tty.usbmodem14501
```

Step 4: Type

```
make flash
```

This should upload the code onto the arduino.

Step 5: Type

```
screen /dev/cu.usbmodem*
```

This will allow for the user to see the output in the terminal window.
