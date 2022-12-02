##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

CC = gcc

CFLAGS	+=	-Wall -Wextra -pedantic -p -g3 -ggdb3 -std=c99 -fsigned-char	\
-funsigned-bitfields -Wno-unused-parameter -fanalyzer -I ./include/

SRC = 	draw.c			\
		event.c 		\
		init_destroy.c	\
		main.c
CSFML	=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
NAME = my_hunter

all: $(NAME)

$(NAME):
	make -C ./lib/my/ -j8
	$(CC) -c $(SRC) $(CFLAGS)
	$(CC) -o $(NAME) *.o -L ./lib -lmy -lm $(CSFML)

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f vgcore.*
	rm -f *.log
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	rm -f my_ls

re: fclean all
