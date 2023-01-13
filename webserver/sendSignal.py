import RPi.GPIO as GPIO
from time import sleep

pin = 11

GPIO.setmode(GPIO.BCM)
GPIO.setup(pin, GPIO.OUT)
GPIO.output(pin, 1)
sleep(1)
GPIO.output(pin, 0)
