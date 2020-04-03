import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO_TRIGGER1 = 17
GPIO_ECHO1 = 16

GPIO_TRIGGER2 = 27
GPIO_ECHO2 = 20

GPIO_TRIGGER3 = 22
GPIO_ECHO3 = 21

GPIO.setup(GPIO_TRIGGER1, GPIO.OUT)
GPIO.setup(GPIO_TRIGGER2, GPIO.OUT)
GPIO.setup(GPIO_TRIGGER3, GPIO.OUT)

triggers = [GPIO_TRIGGER1, GPIO_TRIGGER2, GPIO_TRIGGER3]

GPIO.setup(GPIO_ECHO1, GPIO.IN)
GPIO.setup(GPIO_ECHO2, GPIO.IN)
GPIO.setup(GPIO_ECHO3, GPIO.IN)

echoes = [GPIO_ECHO1, GPIO_ECHO2, GPIO_ECHO3]

distances = [0] * 3

def measureDistance(trigger, echo):
	GPIO.output(trigger, True)
	
	time.sleep(0.00001)
	GPIO.output(trigger, False)
	
	StartTime = time.time()
	StopTime = time.time()
	
	while GPIO.input(echo) == 0:
		StartTime = time.time()
	while GPIO.input(echo) == 1:
		StopTime = time.time()
		
	TimeElapsed = StopTime - StartTime
	
	distance = (TimeElapsed * 34300) / 2
	
	return distance
	
if __name__ == '__main__':
	try:
		while True:
			for index in range(len(triggers)):
				distances[index] = measureDistance(triggers[index], echoes[index])
				
			for index in range(len(distances)):
				print(distances[index], end='\t')
			print('')
			time.sleep(1)
				
	except KeyboardInterrupt:
		GPIO.cleanup()
		print('Stopped')
		
