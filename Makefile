##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

CFLAGS	+=	-Wall -Wextra -pedantic -p -g3 -ggdb3 -std=c99 -fsigned-char	\
-funsigned-bitfields -Wno-unused-parameter -fanalyzer

SRC = 	draw.c	\
		main.c
CSFML	=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
NAME = my_hunter

all: $(NAME)

$(NAME):
	gcc -c $(SRC) $(CFLAGS)
	gcc -o $(NAME) *.o -L ./lib -lmy -lm $(CSFML)

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
