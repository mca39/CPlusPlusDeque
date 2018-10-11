###############################################################
# Program:
#     Week 04, DEQUE
#     Brother Ercanbrack, CS235
# Author:
#     Mariah Ashley
# Summary:
#     This program represents a deque. It is a circular line
#     where items can be added or removed from the front or 
#     the back of the line. the queue is considered full when
#     the back of the line is one less than the start of the 
#     line, in which case a new deque is created, the old one
#     is copied into it starting at location 0 with each item
#     in the same order, and the old deque is deleted. If the 
#     deque is not full, but the back of the line is equal to
#     capacity, the back of the line will move to location 0 t
#     make the line move in a cicular pattern.
# Time:
#     8 hour
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h week04.o nowServing.o
	g++ -o a.out week04.o nowServing.o
	tar -cf week04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week04.o       : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
week04.o: deque.h week04.cpp
	g++ -c week04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp

##############################################################
#clean up
##############################################################
clean:
	rm a.out *.o
