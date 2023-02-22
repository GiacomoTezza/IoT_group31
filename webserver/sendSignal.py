try:
    import RPi.GPIO as GPIO
except:
    # Mainly for debug purposes while not running on a raspberry
    from random import random
    with open('log.txt', 'w') as f:
        f.write("Not found GPIO\n")
        f.write(str(random()))
    exit(0)
    
from time import sleep

pin = 21

GPIO.setmode(GPIO.BCM)
GPIO.setup(pin, GPIO.OUT)
GPIO.output(pin, 1)
sleep(0.1)
GPIO.output(pin, 0)
