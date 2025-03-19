CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = client.c client_bonus.c server.c server_bonus.c

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

bonus: client_bonus server_bonus

client_bonus : client_bonus.o $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o client_bonus client_bonus.o -L./my-printf -lftprintf

server_bonus: server_bonus.o $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o server_bonus server_bonus.o -L./my-printf -lftprintf

client_bonus.o: client_bonus.c
	$(CC) $(CFLAGS) -c client_bonus.c -o client_bonus.o

server_bonus.o: server_bonus.c
	$(CC) $(CFLAGS) -c server_bonus.c -o server_bonus.o

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f client server client_bonus server_bonus

re: fclean all 
.PHONY: all clean