CC = clang
CFLAGS = -Wall -Wextra -g

build: mygit

mygit: mygit.c
	$(CC) $(CFLAGS) -o mygit mygit.c

clean:
	rm -f mygit
