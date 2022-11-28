##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

CFLAGS	+=	-Wall -Wextra -pedantic -p -ggdb3 -std=c99 -fsigned-char	\
-funsigned-bitfields -Wno-unused-parameter -fanalyzer

SRC = 	main.c
CSFML	=	-lcsfml-graphics -lcsfml-window -lcsfml-system
NAME = my_hunter

all: $(NAME)

$(NAME):
	make -C ./lib/my/ -j8
	gcc -c $(SRC) $(CFLAGS)
	gcc -o $(NAME) *.o -L ./lib -lmy -lm $(CSFML)

clean:
	make -C ./lib/my/ clean
	rm -f *.gcda
	rm -f *.gcno
	rm -f vgcore.*
	rm -f *.log
	rm -f *.o

fclean: clean
	rm -f ./lib/libmy.a
	rm -f ./lib/my/libmy.a
	rm -f $(NAME)
	rm -f my_ls

re: fclean all
