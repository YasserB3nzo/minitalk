CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = client.c server.c

OBJS = $(SRCS:.c=.o)

LIBFTPRINTF = ./my-printf/libftprintf.a

all: client server

client: client.o $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o client client.o -L./my-printf -lftprintf

server: server.o $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o server server.o -L./my-printf -lftprintf

client.o: client.c
	$(CC) $(CFLAGS) -c client.c -o client.o

server.o: server.c
	$(CC) $(CFLAGS) -c server.c -o server.o

clean:
	rm -f $(OBJS) client server

.PHONY: all clean
