import serial
import time
import sys, tty, termios

ser = serial.Serial('/dev/ttyUSB0',115200,timeout=1)
ser.flushOutput()
ser.flushInput()

print 'Serial connected'
print ser.name
# The getch method can determine which key has been pressed
# by the user on the keyboard by accessing the system files
# It will then return the pressed key as a variable
def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

while True:
    # Keyboard character retrieval method is called and saved
    # into variable
    char = getch()

    # The robot will drive forward when the "w" key is pressed
    if(char == "w"):
    	ser.write('2')
    # The robot will reverse when the "s" key is pressed
    if(char == "s"):
    	ser.write('8')
    # The "a" key will toggle the steering left
    if(char == "a"):
        ser.write('6')
    # The "d" key will toggle the steering right
    if(char == "d"):
        ser.write('4')
    # The "x" key will break the loop and exit the program
    if(char == "x"):
        print("Program Ended")
        break
