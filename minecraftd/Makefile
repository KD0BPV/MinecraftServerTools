CC = clang++

BUILD_DIR = build

CFLAGS = -std=c++14

.phony : all

all : $(BUILD_DIR) $(BUILD_DIR)/minecraftd

$(BUILD_DIR)/minecraftd : $(BUILD_DIR)/minecraftd.o $(BUILD_DIR)/MCInstance.o
	$(CC) $(BUILD_DIR)/minecraftd.o $(BUILD_DIR)/MCInstance.o \
	-o $(BUILD_DIR)/minecraftd -lsystemd -lpthread -latomic

$(BUILD_DIR)/minecraftd.o : minecraftd.cc exceptions.hh
	$(CC) -c $(CFLAGS) minecraftd.cc -o $(BUILD_DIR)/minecraftd.o

$(BUILD_DIR)/MCInstance.o : MCInstance.cc MCInstance.hh
	$(CC) -c $(CFLAGS) MCInstance.cc -o $(BUILD_DIR)/MCInstance.o

$(BUILD_DIR) :
	mkdir $(BUILD_DIR)

.PHONY : clean disinfect

clean :
	rm $(BUILD_DIR)/*

disinfect :
	rm -Rf $(BUILD_DIR)
