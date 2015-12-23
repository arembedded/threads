INC_DIR=/home/arembedded/threads

threads: threads.c $(INC_DIR)/util/util.c
	gcc threads.c $(INC_DIR)/util/util.c -I$(INC_DIR) -lpthread -o threads.o

all: threads

clean:
	rm -rf *.o	
