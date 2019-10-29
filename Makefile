OBJECTS = *.o
SRC = snake.cpp src/*.cpp
FLAGS = -lncurses
NAME = ft_snake

all: $(NAME)

$(NAME):
	clang++ $(FLAGS) $(SRC) -o $(NAME) 

lldb:
	clang++ $(FLAGS) $(SRC) -o $(NAME) -g

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run:
	./$(NAME)