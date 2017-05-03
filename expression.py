import time
import subprocess
import pyautogui
import thread

class expression(object):
	def __init__(self, ser):
		def disp():
			subprocess.call('eog -f', shell = True)
		self.port = ser
		thread.start_new_thread(disp, ())
	# Function to execute YES expression
	def yes(self):
		self.port.write(bytearray([1,1]))
		subprocess.call('eog -f --single-window /home/udooer/gif/yes.gif', shell = True)

	# Function to execute NO expression
	def no(self):
		self.port.write(bytearray([1,2]))
		subprocess.call('eog -f --single-window /home/udooer/gif/no.gif', shell = True)	

	# Function to execute SLEEPY expression
	def sleepy(self):
		#ser.write(bytearray([1,2]))
		subprocess.call('eog -f --single-window /home/udooer/gif/sleepy.gif', shell = True)	

	# Function to execute BLINK expression
	def blink(self):
		subprocess.call('eog -f --single-window /home/udooer/gif/blink.gif', shell = True)
