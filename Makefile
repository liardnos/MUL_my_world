##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile for bistro-matic
##

SRC		=		*.c

SRCT 	=		./tests/

NAME	=		a.out

FLAGS	=		-L./lib/my -lmy -I./include/ -l csfml-graphics -l m
#-fno-diagnostics-show-labels -fno-diagnostics-show-labels fdiagnostics-generate-patch -Wall -Wextra
#fsyntaxe-only
TFLAG 	= 		-lcriterion --coverage -fprofile-arcs

COV 	=		--exclude tests/ -o coverage.html



all:
	clear
	make -C ./lib/my build
	gcc -o $(NAME) $(SRC) $(FLAGS)

allO4:
	make -C ./lib/my buildO6
	gcc -o $(NAME) $(SRC) $(FLAGS) -Ofast

run: all
	make fclean
	./$(NAME)

runO4: allO4
	make fclean
	./$(NAME)

clean:
	rm -f $(OBJ)
	make -C ./lib/my clean
	rm -f *.html
	rm -f *.gcno
	rm -f *.gcda

fclean:	clean
	#rm -f $(NAME)
	make -C ./lib/my fclean
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.html
	rm -f vgcore.*
	rm -f callgrind.*

clear:
	clear

re: clear fclean all

tests_run: fclean
	make -C ./lib/my re
	gcc -o $(NAME) $(SRC) $(SRCT) $(TFLAG) $(FLAGS)
	-./$(NAME)
	gcovr --exclude tests/
	gcovr --html $(COV) --html-title $(NAME) --html-details
	rm -f *.gcno
	rm -f *.gcda

valgrind: fclean
	clear
	make -C ./lib/my valgrind
	gcc -g -o $(NAME) $(SRC) $(FLAGS)
	valgrind -s --leak-check=full --track-origins=yes  --show-leak-kinds=definite ./$(NAME) #&> valgrind_log

callgrind: fclean
	rm -f callgrind.*
	clear
	make -C ./lib/my valgrind
	gcc -g -o $(NAME) $(SRC) $(FLAGS)
	-valgrind --tool=callgrind ./$(NAME) 3 #&> valgrind_log
	-kcachegrind callgrind.*

callgrindO6: fclean
	rm -f callgrind.*
	clear
	make -C ./lib/my buildO6
	gcc -g -o $(NAME) $(SRC) $(FLAGS) -O6
	-valgrind --tool=callgrind ./$(NAME) 3 #&> valgrind_log
	-kcachegrind callgrind.*
