# Embedded Software for the Internet of Things: IoT_group31

Embedded Smart Feeder is a smart pet feeder that can automatize the food erogation for your pet. It allows you to schedule meals at specific time of the day and the feeder will dispense the correct dose of food autonomusly.

![Inside](https://i.imgur.com/thVOqGj.jpg)

## Features

The following features have been implemented and tested on the board.
- Web Interface to edit feeding schedules.
- ChronJobs to handle timed comunications.
- GPIO comunication between the RaspberryPI and the MSP432.
- GPIO sensing and debouncing on MSP432.
- Iterrupt Service Routines system to control the Servo Motor.
- Servo Motor movement using PWM.

## Demo

A video demonstration of the project is available on [YouTube](https://www.youtube.com/playlist?list=PLDc6qaqn1_iXD7BgPODJwvfgZr5sRzeQW).
A brief presentation is available on [Google Slides](https://docs.google.com/presentation/d/1O1WLHBDQUMl41cEYhrukCoQteXkMGJ9-R98tLyEIqY4/edit?usp=sharing).

## Authors

- Marcon Daniel: Software development, webserver
- Tezza Giacomo: Software development, presentation
- Conti Nicola: Software development, presentation

# Requirements

## Hardware requirements

Embedded Smart Feeder requires a Texas Instruments MSP432 microcontroller, which is based on a 32-bit ARM Cortex-M4 CPU.
<!-- if used in future uncomment otherwise delete -->
<!-- The [Educational Booster Pack](https://www.ti.com/tool/BOOSTXL-EDUMKII) with its additional hardware peripherals is also required.   -->
It's also used a Raspberry PI 3B+ as a webserver and Servo Motors to perform the erogation.
Development and testing have been performed on MSP-EXP432P401R Launchpad development kit.  

## Software requirements
Embedded Smart Feeder requires [MSP Driver Library](https://www.ti.com/tool/MSPDRIVERLIB) to be downloaded and linked to the project.
It's also required Python and some Python library to run the webserver, more information in the [Web Server setup](#webserver) section.
Embedded Smart Feeder code can be built and burned to the board using [Code Composer Studio IDE](https://www.ti.com/tool/CCSTUDIO), more information in the [Board setup](#board) section.

# Getting Started

## Board

To compile and execute Embedded Smart Feeder on your TI launchpad, follow the steps:

- Download, install and execute CCStudio.
- Create a new project into CCStudio by clicking File > New > CCS Project.
- Select the correct target board and the project name, and click Finish.
- Locate the project in your file system and clone this repository inside its root folder. 
- Modify Arm Compiler > Include Options in project properties by adding the DriverLib source folder as follows:
`~\driver\source`
- Modify Arm Linker > File Search Path in project properties by adding DriverLib object files as follows:
`~\driver\source\ti\devices\msp432p4xx\driverlib\ccs\msp432p4xx_driverlib.lib`
- Build and flash the project to the board

## WebServer

To setup and run the webserver, follow the steps:

- Make sure to have python 3.6+ installed
- Go to the previously cloned repository
```
cd IoT_group31/
```
- You can optionally start a virtual enviroment (you will need to install also virtualenv or you can use the one you prefer)
```
virtualenv venv
source venv/bin/activate
```
- Install dependencies
```
pip install -r webserver/requirements.txt
```
- Run the application
```
python webserver/app.py
```

# Project Description
The following sections describe the most interesting parts of the implementation.

## CronJobs
The cron command-line utility is a job scheduler on Unix-like operating systems.
We use cron to schedule jobs, also known as cron jobs, to run periodically at fixed times, dates, or intervals.
From the backend of the website it's created a cron job that runs a Python script to sets specific GPIO pins of the RaspberryPI to an high logical level and then back to low logical level, to comunicate with the MSP432.

```python
# file: webserver/app.py
@app.route('/set_snack/<t>')
def set_snack(t):
    t = int(t)

    job = cron.new(command=f'python {getcwd()}/sendSignal.py', comment=str(unixtime()))
    job.setall(time((t// 60), (t % 60)))

    cron.write()

    return redirect('/')
```

```python
# file: webserver/sendSignal.py
import RPi.GPIO as GPIO
from time import sleep

pin = 21
GPIO.setmode(GPIO.BCM)
GPIO.setup(pin, GPIO.OUT)
GPIO.output(pin, 1)
sleep(0.1)
GPIO.output(pin, 0)
```

## PWM
The Pulse-Width Modulation uses the width of a pulse to modulate an amplitude, that reflects the duty cycle, which describes the proportion of the high state in one pulse period.
It's used to move the servo the needed angle, converting a value from 0 to 180 degrees, to a time period that the servo needs to move to get to that angle.

![pwm](https://i.imgur.com/Tg8Y91F.jpg)

The PWM signal produced should have a frequency of 50Hz that is the PWM period should be 20ms.
Out of which the On-Time can vary from 1ms to 2ms.
So when the On-Time is 1ms the motor will be in 0 degrees and when 1.5ms the motor will be 90 degrees, similarly when it is 2ms it will be 180 degrees.
So by varying the On-time from 1ms to 2ms the motor can be controlled from 0 degrees to 180 degrees.

## Debouncing
When a GPIO signal is generated from the RaspberryPI or a button on the board is pressed once by the user, it happens that the corresponding interrupt is generated multiple times.
This issue is caused by electrical noise which occurs when the switch is on the threshold position between on and off:
it is possible that an interrupt is generated the first time, the ISR is executed, then the input is still oscillating and another interrupt is generated.

To avoid this issue a debouncer is needed.
It can be a hardware device like a logic counter connected to a timer or even a simple capacitor.
Otherwise a software solution may be preferable: in this project, whenever a button is pressed and the corresponding ISR is executed, a countdown with the system Timer32 is started, and it will last 1/4 of the clock cycles per second (therefore 3 MHz / 4 = 0.75 Mega ticks).
If a second interrupt is generated because of bouncing, the ISR checks whether the timer reached 0, otherwise it just returns.

# Acknowledgments

<a href="https://www.unitn.it/"><img src="https://www.unitn.it/sites/www.unitn.it/themes/unitn_theme/images/newlogo_unitn_it.png" width="300px"></a>

## Copyright

MIT Licence or otherwise specified. See [license](./LICENSE) file for details.
