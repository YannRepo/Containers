##########   BASE   ##########
# File name
NAME = main

# Sources
SRCS += main.cpp

OBJS = ${SRCS:.cpp=.o}

HEADER += map.hpp
HEADER += ../10_Tools/reverse_iterator.hpp
HEADER += ../10_Tools/lexicographical_compare.hpp
HEADER += ../10_Tools/is_integral.hpp
HEADER += ../10_Tools/enable_if.hpp

HEADER += pair.hpp
HEADER += red_black_tree.hpp
HEADER += red_black_tree_iterator.hpp

INCLUDES_DIR =

LIB_INCLUDE =

# Compilateurs
CC = c++
CFLAGS = -g3 -std=c++98
#CFLAGS = -g3 -Wall -Wextra -std=c++98
# CFLAGS = -Wall -Wextra -Werror -std=c++98

##########   RULES   ##########

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	${CC} ${SRCS} -o ${NAME} ${CFLAGS} ${INCLUDES_DIR} ${LIB_INCLUDE}

%.o: %.cpp $(HEADER)
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
