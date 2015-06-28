CC = g++

BUILD_DIR = ./BUILD/

CFLAGS =

CPPFLAGS = -std=c++14 -stdlib=libc++

OBJ = minecraftd.o log.o MCInstance.o exceptions.o

minecraftd : $(OBJ)
	$(CC) -o minecraftd $(OBJ)
	
minecraftd.o : minecraftd.cpp MCInstance.h exceptions.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) minecraftd.cpp

log.o : Log.h Log.cpp exceptions.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) 