# Embedded Software for the Internet of Things: IoT_group31

Embedded Smart Feeder is a smart pet feeder that can automatize the food erogation for your pet. It allows you to schedule meals at specific time of the day and the feeder will dispense the correct dose of food autonomusly.

<!-- image here -->

## Features

The following features have been implemented and tested on the board.
<!-- todo when the project is completed -->

## Demo

<!-- A video demonstration of the project is available on [YouTube](link). -->
<!-- A brief presentation is available on [Google Slides](link). -->

## Authors

- Marcon Daniel - Software development, webserver
- Tezza Giacomo - Software development, presentation
- Conti Nicola - Software development, presentation

# Requirements

## Hardware requirements

Embedded Smart Feeder requires a Texas Instruments MSP432 microcontroller, which is based on a 32-bit ARM Cortex-M4 CPU.
<!-- if used in future uncomment otherwise delete -->
<!-- The [Educational Booster Pack](https://www.ti.com/tool/BOOSTXL-EDUMKII) with its additional hardware peripherals is also required.   -->
It's also used a Raspberry PI 3B+ as a webserver and Servo Motors to perform the erogation.
Development and testing have been performed on MSP-EXP432P401R Launchpad development kit.  

## Software requirements
Embedded Smart Feeder requires [MSP Driver Library](https://www.ti.com/tool/MSPDRIVERLIB) 
<!-- if used in future uncomment otherwise delete -->
<!-- and [MSP Graphics Library](https://www.ti.com/tool/MSP-GRLIB)  -->
to be downloaded and linked to the project.
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
<!-- - Modify Arm Linker > File Search Path in project properties by adding DriverLib and GrLib object files as follows:
`~\driver\source\ti\grlib\lib\ccs\m4f\grlib.a`  
`~\driver\source\ti\devices\msp432p4xx\driverlib\ccs\msp432p4xx_driverlib.lib` -->
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

# Acknowledgments

<a href="https://www.unitn.it/"><img src="https://www.unitn.it/sites/www.unitn.it/themes/unitn_theme/images/newlogo_unitn_it.png" width="300px"></a>

## Copyright

MIT Licence or otherwise specified. See [license](./LICENSE) file for details.
