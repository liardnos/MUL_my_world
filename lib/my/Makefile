##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## My makefile
##

SOURCE	=	*.c \
			lld/*.c \
			csfml/*.c \
			mat/*.c
			#btr/*.c

OBJ		=	$(SOURCE:.c=.o)

all:
	gcc -c $(SOURCE)
	ar rc libmy.a *.o
	cp libmy.a ../
	cp *.h ../../include/

build:
	gcc -c $(SOURCE)
	ar rc libmy.a *.o
	cp libmy.a ../
	cp *.h ../../include/

buildO6:
	gcc -c $(SOURCE) -O6
	ar rc libmy.a *.o
	cp libmy.a ../
	cp *.h ../../include/
	rm -f *.o

clean:
	rm -f *.o

fclean:
	rm -f *.o
	rm -f libmy.a
	rm -f ../libmy.a
	rm -f ../../include/my.h

re: clean all

valgrind: fclean
	gcc -g -c $(SOURCE)
	ar rc libmy.a *.o
	cp libmy.a ../
	cp *.h ../../include/
	rm -f *.o
