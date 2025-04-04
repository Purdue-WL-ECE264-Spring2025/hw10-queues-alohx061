CFLAGS = -std=c99 -g -Wall -Wshadow -Wvla -Werror -Wunreachable-code
OBJS = main.o linked_list.o tile_game.o queue.o
HEADERS = linked_list.h tile_game.h
APP = hw10

.PHONY: clean

$(APP): $(OBJS)
	$(CC) $(CFLAGS) *.o -o $(APP)

clean:
	/bin/rm -rf *.o
	/bin/rm -rf $(APP)

test1: $(APP)
	./$(APP) testcases/1.txt

valgrind1: $(APP)
	valgrind ./$(APP) testcases/1.txt

test2: $(APP)
	./$(APP) testcases/2.txt

valgrind2: $(APP)
	valgrind --leak-check=full ./$(APP) testcases/2.txt

test3: $(APP)
	./$(APP) testcases/3.txt

%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@ $(CFLAGS)
