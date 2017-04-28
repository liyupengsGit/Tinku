import serial
import time
import subprocess
import pyautogui
import thread

ser = serial.Serial('/dev/ttyUSB0',115200)
ser.flushOutput()
ser.flushInput()
print ser.name
print ser.readline()

# Function to execute YES expression
def yes():
	ser.write(bytearray([1,1]))
	subprocess.call('eog -f --single-window /home/udooer/gif/yes.gif', shell = True)

# Function to execute NO expression
def no():
	ser.write(bytearray([1,2]))
	subprocess.call('eog -f --single-window /home/udooer/gif/no.gif', shell = True)	

# Function to execute SLEEPY expression
def sleepy():
	#ser.write(bytearray([1,2]))
	subprocess.call('eog -f --single-window /home/udooer/gif/sleepy.gif', shell = True)	

# Function to execute BLINK expression
def blink():
	subprocess.call('eog -f --single-window /home/udooer/gif/blink.gif', shell = True)	

yes()
