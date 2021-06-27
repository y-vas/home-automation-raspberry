#!/usr/bin/python

print('hi loo')
exit()

import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode( GPIO.BCM )

relations = [
  # room , sound_pin, reley_pin, reley_status
  [ 1 , 17 , 34 , 0 ],
  [ 2 , 17 , 34 , 0 ],
  [ 3 , 17 , 34 , 0 ],
  [ 4 , 17 , 34 , 0 ],
  [ 0 , 17 , 34 , 0 ],
];

########################################
############### 5th room ###############
############ blinds schedule ###########

def switch( id ):
    if relations[id] == 1:
        GPIO.setup(reley, GPIO.HIGH)
    else:
        GPIO.setup(reley, GPIO.LOW)
    relations[id] = int(relations[id]!=1)

for id, sound, reley, rs in relations:
    GPIO.setup(sound, GPIO.IN)
    GPIO.setup(reley, GPIO.IN)

    GPIO.add_event_detect( sound, GPIO.BOTH, bouncetime=300)
    GPIO.add_event_callback(sound, lambda: switch(id) )

while True: sleep(1)
