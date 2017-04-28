import serial
import time
import subprocess
import pyautogui
import thread
import snowboydecoder
import sys
#from sensor import Sensor

#ser = serial.Serial('COM6',115200)
#ser.flushOutput()
#ser.flushInput()

# Hotword detector
def hotWord(models):
	sensitivity = [0.5]*len(models)
	detector = snowboydecoder.HotwordDetector(models, sensitivity=sensitivity)

	# main loop
	word = detector.start(detected_callback=snowboydecoder.play_audio_file,
					sleep_time=0.03)
	return(word)

# Function to execute sleepy activity	
def sleepy():
	def disp():
		subprocess.call('eog -f /home/udooer/gif/sleepy.gif', shell = True)
	
	thread.start_new_thread(disp, ())
	word = hotWord(['Tinku.pmdl'])
	if word == '1':
		print('Tinku')

# Function to execute blink activity
def blink():
	def disp():
		subprocess.call('eog --single-window /home/udooer/gif/blink.gif', shell = True)
	
	thread.start_new_thread(disp, ())
	word = hotWord(['Exit.pmdl'])
	if word == '1':
		print('Exit')
		pyautogui.hotkey('alt', 'f4')
		sys.exit(-1)
		
sleepy()
blink()
