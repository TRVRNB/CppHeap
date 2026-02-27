"""
This Python script will generate a file (numbers.txt) that can be used in main.cpp
"""
import sys, random

sys.stdout = open("numbers.txt", "w") # print directly to numbers.txt
data = ""
used_numbers = []

for i in range(100):
	# generate 100 numbers, no repeats!
	num = random.randint(1, 1000)
	while num in used_numbers: # keep looking; there will always be an available number
		num = random.randint(1, 1000)
	used_numbers.append(num) # was dumb, forgot this earlier
	data += str(num) # add this to the line
	if i != 99: # add space if it's not the last number
		data += " "

print(data)
