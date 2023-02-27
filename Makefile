##########   BASE   ##########
# File name
NAME = main

# Sources
SRCS += main_vector.cpp
#SRCS += main_map.cpp
#SRCS += main_sujet.cpp
#SRCS += main_mazoise_reserve.cpp

OBJS = ${SRCS:.cpp=.o}

HEADER += vector.hpp
HEADER += map.hpp
HEADER += random_access_iterator.hpp
HEADER += pair.hpp
HEADER += red_black_tree.hpp
HEADER += red_black_tree_iterator.hpp
HEADER += reverse_iterator.hpp
HEADER += lexicographical_compare.hpp
HEADER += is_integral.hpp
HEADER += enable_if.hpp

INCLUDES_DIR =

LIB_INCLUDE =

# Compilateurs
CC = c++
#CFLAGS = -g3 -std=c++98
#CFLAGS = -g3 -Wall -Wextra -std=c++98
 CFLAGS = -g3 -Wall -Wextra -Werror -std=c++98

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
