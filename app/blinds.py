import RPi.GPIO as GPIO
import sleep

GPIO.setmode(GPIO.BCM)

pin_up = 26
pin_down = 13

GPIO.setup( pin_up   , GPIO.OUT )
GPIO.setup( pin_down , GPIO.OUT )
GPIO.output( pin_up  , GPIO.LOW )
GPIO.output( pin_down, GPIO.LOW )

def move_shutters( pin, sec ):
    GPIO.output(pin, GPIO.HIGH)
    sleep(sec)
    GPIO.output(pin, GPIO.LOW)

move_shutters( pin_up , 20 )
while True:
    now      = datetime.now()
    now_time = now.time()

    if now_time >= time( 23,00 ):
        move_shutters( pin_down, 20 )
        sleep( 3600*7 )

    sleep(1)
