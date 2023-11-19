#NAME: JHEANEY PERICO ID: 3115469

CC = gcc
CFLAGS = -Wall -std=c11

App: test_myCode.o myCode.o myCode.h
	$(CC) $(CFLAGS) -lc -lm -lncurses -ltinfo $(^) -o $(@)

%.o:%.c
	$(CC) $(CFLAGS) -c $(^) -o $(@)

.PHONY: clean

clean:
	rm *.o App
