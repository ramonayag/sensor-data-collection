'''
=> read the serial port
=> parse the data
=> print it to the terminal
=> add the data to the file
'''
import serial 
# import time


activityName = input()

# port Arduino is plugged in 
arduino_port = "/dev/cu.usbserial-1410"
baud = 115200;
fileName = "{}Data.csv".format(activityName)
print_labels = True
line = 0 

#numOfMinutes minute from now
# numOfMinutes = 3
# timeout = time.time() + 60* numOfMinutes  

#set up the serial connection and create the file
ser = serial.Serial(arduino_port, baud) #serial connection
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "a")
print('Created file')

#write data to csv for 1 minute 
try: 
	while True:
		# try:
		if print_labels:
			if line ==0:
				print("Printing column headers")
			else: 
				print("Line" + str(line) + "writting...")
		
		#display data to the terminal 
		getData = ser.readline()
		data = (getData[0:][:-2]).decode()

		#append data to the file
		file = open(fileName, "a")
		file.write(data + "\n")
		line = line + 1
except KeyboardInterrupt:
	print("Exception Thrown")
	pass
		# except:
		# 	print("Exception Thrown")
		# 	file.close() #close file


print("Data collection complete! File closed")
file.close() #close file
