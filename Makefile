##
## Makefile for  in /home/eax/dev/phantom-controller/src
## 
## Made by eax
## Login   <soules_k@epitech.net>
## 
## Started on  Thu Sep 18 00:55:22 2014 eax
## Last update Thu Sep 18 01:57:14 2014 eax
##

CC	=	gcc

CFLAGS	=	-W -Wall -Wextra -I/usr/local/include/libusb-1.0/
LDFLAGS	=	-lpthread -L/usr/local/lib -lusb-1.0

SRC	=	src/usb.c \
		src/usb-transfer.c \
		src/main.c \
		src/pc_parse.c

OBJ	=	$(SRC:.c=.o)

NAME	=	phantom-contoller


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
