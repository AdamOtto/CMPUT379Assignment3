# CMPUT379Assignment3
Assignment 3 for CMPUT 379.

To run this program, simply create the executable with the "make" command then type into the console "./tvm379" followed by the arguments detailed
in the specs for this assignment.

This program starts by grabbing all of the arguments its given then initializes certain variables that will be used throughout the program.
Depending of the policy for the physical memory, one of two variables are allocated space in memeory to contain the information that will be read from the trace files.
The main bulk of the work done in the program is done within the while loop located at the end of the main function.
The first function call is "ReadTraceFile" which reads line by line 32bits from a supplied file.
"ReadTraceFile" will continue reading until it has reached the 'quantum' limit specified in the arguments.
After each read, it will remove the page offset and create an integer that represents the page number.

