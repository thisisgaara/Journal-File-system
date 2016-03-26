#
# This is the Makefile for phase 1 of JFS submission.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#

CC = gcc
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
#
default: jfs

# To create the executable file count we need the object files
# allocate.o, bootup.o, deallocate.o, functions.o, linked_list.o, main.o, read.o, write.o, test_application_transfer.o
#
jfs: allocate.o bootup.o deallocate.o functions.o linked_list.o main.o read.o write.o test_application_transfer.o 
	$(CC) $(CFLAGS) -o ./bin/jfs ./obj/allocate.o ./obj/bootup.o ./obj/deallocate.o ./obj/functions.o ./obj/linked_list.o ./obj/main.o ./obj/read.o ./obj/write.o ./obj/test_application_transfer.o -I.

# To create the object file allocate.o, we need the source
# file allocate.c
#
allocate.o:  ./src/allocate.c ./src/header.h ./src/user_header.h
	$(CC) -c -o ./obj/allocate.o ./src/allocate.c -I./src/.
bootup.o:  ./src/bootup.c ./src/header.h ./src/user_header.h
	$(CC) -c -o ./obj/bootup.o ./src/bootup.c -I../src/.
deallocate.o:  ./src/deallocate.c ./src/header.h ./src/user_header.h
	$(CC) -c -o ./obj/deallocate.o ./src/deallocate.c -I../src/.
functions.o:  ./src/functions.c ./src/header.h ./src/user_header.h
	$(CC) -c -o ./obj/functions.o ./src/functions.c -I../src/.
linked_list.o:  ./src/linked_list.c ./src/header.h ./src/user_header.h
	$(CC) -c -o ./obj/linked_list.o ./src/linked_list.c -I../src/.
main.o:  ./src/main.c ./src/header.h ./src/user_header.h
	$(CC) -c -o ./obj/main.o ./src/main.c -I../src/.
read.o:  ./src/read.c ./src/header.h ./src/user_header.h
	$(CC) -c -o ./obj/read.o ./src/read.c -I../src/.
write.o:  ./src/write.c ./src/header.h ./src/user_header.h
	$(CC) -c -o ./obj/write.o ./src/write.c -I../src/.
test_application_transfer.o:  ./src/test_application_transfer.c ./src/header.h ./src/user_header.h
	$(CC) -c -o ./obj/test_application_transfer.o ./src/test_application_transfer.c -I../src/.

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files, executable and *~ backup files:
#
clean: 
	-@rm -rf ./bin/* 2>/dev/null || true
	-@rm -rf ./obj/* 2>/dev/null || true
