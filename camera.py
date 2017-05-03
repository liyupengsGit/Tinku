# -*- coding: utf-8 -*-
"""
Created on Tue May  2 02:38:37 2017

@author: Swapnil
"""
import cv2
import thread
import snowboydecoder
import pyautogui
import copy
import time

def hotWord(model, key):
    #sensitivity = [0.5]*len(models)
    detector = snowboydecoder.HotwordDetector(model, sensitivity=0.5)
    # main loop
    # make sure you have the same numbers of callbacks and models
    word = detector.start(detected_callback=snowboydecoder.play_audio_file,
                    sleep_time=0.03)
    if (word == '1'):
        pyautogui.press(key)

class camera(object):
	def __init__(self):
		self.cap = cv2.VideoCapture(2)
		self.cap.set(3, 320)
		self.cap.set(4, 240)
		self.face_cascade = cv2.CascadeClassifier('frontalface_default.xml')
		
	def picture(self):
		thread.start_new_thread(hotWord, ('cheese.pmdl','s'))
		while True:
			ret, frame = self.cap.read()
			img = copy.copy(frame)
			gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
			faces = self.face_cascade.detectMultiScale(gray, 1.3, 5)
			for (x, y, w, h) in faces:
				cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 2)

			cv2.imshow('img', img)
			k = cv2.waitKey(1)
			if k == ord('s'):
				cv2.imwrite('picture.png',frame)
				break
		self.cap.release()
		cv2.destroyAllWindows()
		def close(delay):
			time.sleep(delay)
			pyautogui.press('esc')
		
		thread.start_new_thread(close, (2,))
		image = cv2.imread('picture.png')
		cv2.imshow('img',image)
		cv2.waitKey(0)
		cv2.destroyAllWindows()

	def video(self):
		fourcc = cv2.VideoWriter_fourcc(*'XVID')
		out = cv2.VideoWriter('output.avi', fourcc, 20.0, (640,480))
		record = 0
		thread.start_new_thread(hotWord, ('record video.pmdl', 's'))
		while True:
			ret, img = self.cap.read()
			gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
			faces = self.face_cascade.detectMultiScale(gray, 1.3, 5)
			for (x, y, w, h) in faces:
				cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 2)

			cv2.imshow('img', img)
			k = cv2.waitKey(1)
			if k == ord('s') and record == 0:
				record = 1
				thread.start_new_thread(hotWord, ('No.pmdl', 'esc'))
			elif k == 27 and record == 1:
				record = 0
				out.release()
				break
				
			if (record):
				print "Recording"
				out.write(img)
        
		self.cap.release()
		cv2.destroyAllWindows()

#cam = camera()
#cam.video()