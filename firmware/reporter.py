#!/bin/python

import serial
import tkinter as tk
import threading
import time
import pandas as pd
import numpy as np

FONT_SIZE = 60

# f = open('output.csv','w')
# f.write(',adc,raw,percent,timestamp')
# f.close()

adc = []
raw = []
per = []
t = []

def data_reader():
	while(True):
		try:
			# f = open('output.csv','a')
			data = 0
			adc_data = 0
			per_data = 0

			data = term.read(3)

			text_adc_data['text'] = str(round( (1.3*1024)/((data[0] << 0) | (data[1] << 8)),2))
			text_raw_data['text'] = str((data[0] << 0) | (data[1] << 8))
			text_per_data['text'] = str(data[2]) + '%'

			text_timestamp['text'] = time.ctime()
			# f.write(text_adc_data['text'] + ',' +
			# text_raw_data['text'] + ',' +
			# text_per_data['text'] +',' +
			# text_timestamp['text'])
			adc.append(text_adc_data['text'])
			raw.append(text_raw_data['text'])
			per.append(text_per_data['text'])
			t.append(text_timestamp['text'])

			# f.close()

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

df = pd.DataFrame({
	'adc' : adc,
	'raw' : raw,
	'percentage' : per,
	'timestamp' : t
})
df.to_csv('output.csv')
