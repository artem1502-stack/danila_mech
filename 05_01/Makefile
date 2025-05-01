CC		=	gcc
CFLAGS	=	#-Wall -Werror -Wextra
SOURCES	=	main.c fun.c
HEADERS	=	h.h
OBJECTS	=	$(SOURCES:.c=.o)
RESULT	=	our_program

all: $(SOURCES) $(RESULT) $(HEADERS)

$(RESULT):	$(OBJECTS) $(HEADERS)
	@$(CC) $(OBJECTS) -o $(RESULT)

.c.o: $(HEADERS)
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm $(OBJECTS)

fclean:
	@make clean
	@rm $(RESULT)

re:
	@make fclean
	@make
