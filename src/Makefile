CC = 	eval cc 

FILES = main.c  

FLAGS = $(shell pkg-config --libs --cflags raylib)

TARGET = main

all:

	$(CC) $(FILES) $(FLAGS) -o $(TARGET)

	@echo "Starting program.."

	./$(TARGET)


clean : 
	rm -rf main
