try:
    import RPi.GPIO as GPIO
except:
    from random import random
    with open('log.txt', 'w') as f:
        f.write(str(random()))
    exit(0)
    
from time import sleep

pin = 21

GPIO.setmode(GPIO.BCM)
GPIO.setup(pin, GPIO.OUT)
GPIO.output(pin, 1)
sleep(1)
GPIO.output(pin, 0)
