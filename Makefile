#name compiler 
CC = gcc


#compiler flags to use
CFLAGS = -Wall -g


# name source files
SRCS = calculator.c functions.c test.c

#name header file
HEADERS = functions.h

#object files directory 
OBJS = $(SRCS:.c=.o)


# output executable
TARGET = calculator


#build program
$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

##compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) %(CFLAGS) -c $< -o $@


#CLEAN THE BUILD FILES
clean:
	rm -f $(TARGET) $(OBJS)