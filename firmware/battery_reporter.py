#!/bin/python

import serial
import tkinter as tk
import threading
import time

FONT_SIZE = 60

def data_reader():
	while(True):
		try:
			data = 0
			adc_data = 0
			per_data = 0

			data = term.read(5)
			adc_data = (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24)
			text_adc_data['text'] = str(adc_data / 100)
			text_raw_data['text'] = str(133120 // adc_data) + '/ 1024'

			per_data = (data[4])
			text_per_data['text'] = str(per_data)

			text_timestamp['text'] = time.ctime()
		except:
			continue




term = serial.Serial('/dev/ttyUSB0', baudrate=9600)

root = tk.Tk()

tk.Label(root, text='ADC Reading   ', font=('', FONT_SIZE)).grid(row=0, column=0)
text_adc_data = tk.Label(root, text='', font=('', FONT_SIZE))
text_adc_data.grid(row=0, column=1)

tk.Label(root, text='Percent   ', font=('', FONT_SIZE)).grid(row=1, column=0)
text_per_data = tk.Label(root, text='', font=('', FONT_SIZE))
text_per_data.grid(row=1, column=1)

tk.Label(root, text='Raw ADC Reading', font=('', FONT_SIZE)).grid(row=2, column=0)
text_raw_data = tk.Label(root, text='', font=('', FONT_SIZE))
text_raw_data.grid(row=2, column=1)

tk.Label(root, text='Timestamp', font=('', FONT_SIZE)).grid(row=3, column=0)
text_timestamp = tk.Label(root, text='', font=('', FONT_SIZE))
text_timestamp.grid(row=3, column=1)

threading.Thread(target=data_reader, args=()).start()

root.mainloop()