# CMPUT379Assignment3
Assignment 3 for CMPUT 379.
Adam Otto, Justin Stuehmer

To run this program, simply create the executable with the "make" command then type into the console "./tvm379" followed by the arguments detailed
in the specs for this assignment.

This program starts by grabbing all of the arguments its given then initializes certain variables that will be used throughout the program.
Depending of the policy for the physical memory, one of two variables are allocated space in memeory to contain the information that will be read from the trace files.
The main bulk of the work done in the program is done within the while loop located at the end of the main function.
The first function call is "ReadTraceFile" which reads line by line 32bits from a supplied file.
"ReadTraceFile" will continue reading until it has reached the 'quantum' limit specified in the arguments.
After each read, it will remove the page offset and create an integer that represents the page number.
The program then takes the page number And determines if it exists within the TLB.
If it exists, the TLB is updated and the program reads the next line.
If it doesn't exists, we search the page table to see if it exists.
If it does, then the TLB is updated and the program continues.
If the TLB and the page table don't have the page number, then it is added into the page table and into physical memory.  The eviction policy for physical memory is determined by the passed in arguments.
After all the quantum lines are read, the program will continue on to the next trace file (if it exists).
The program will continue reading from the trace files until the end of file for all trace files are reached.  Once this is done, stats that were collected during execution are displayed and the program closes.

We tried to make our program as efficient as possible while also meeting the behavior specifications of LRU and FIFO eviction.
The data kept in the FIFO and LRU structures were kept unorganized.  This is because their position was important for determining which would be evicted.
This means that one inefficiency is searching through the structures to determine if a page number already exists within them.
The flip side is that removing is very quick, as eviction is done only at a certain position in the array for each structure.
One of the early on improvments was making an array of pointers for the files.  We would open the files are read them using fread; which would remember the index location it last read.
Our early method was to re-open the file every time we called the ReadTraceFile function.
We would pass in the previous index of the fread and call fread until we reached that point.

Despite our best efforts, for large trace files such as the provided "quick-sort-trace.bin" file provided still take a long time to execute.
On a weaker machine, it took over to 30 minutes for the program to finish one of the trace files provided.
