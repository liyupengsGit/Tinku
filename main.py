import serial
import time
import subprocess
import pyautogui
import thread
import snowboydecoder
import sys
# Custom Modules
import expression
import camera

# Open serial port to communicate with arduino
ser = serial.Serial('/dev/ttyUSB0',115200)
ser.flushOutput()
ser.flushInput()
print ser.name
#print ser.readline()

# Hotword detector
def hotWord(models):
	sensitivity = [0.5]*len(models)
	detector = snowboydecoder.HotwordDetector(models, sensitivity=sensitivity)

	# main loop
	word = detector.start(detected_callback=snowboydecoder.play_audio_file,
					sleep_time=0.03)
	return(word)
	
exp = expression.expression(ser)
exp.sleepy()
awake = hotWord(['Tinku.pmdl'])		# Listening for word 'Tinku' while sleeping
if (awake == '1'): 
	exp.blink()
	while(True):
		word = hotWord(['take a picture.pmdl', 'Exit.pmdl'])
		print word
		if (word == '1'):
			cam = camera.camera()
			cam.picture()
		elif (word == '2'):
			pyautogui.hotkey('alt','f4')
			break;
