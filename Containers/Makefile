
OBJS		=	${SRCS:.cpp=.o}

.cpp.o:
				$(CCPP) $(CPPFLAGS) -o $@ -c $<

SRCS			=	Test/main.cpp \
					Test/map.cpp \
					Test/vector.cpp \
					Test/stack.cpp \




CCPP			=	clang++
CPPFLAGS		=	-g -Wall -Wextra -Werror -std=c++98 -I ./
NAME			=	ft_containers

$(NAME):	${OBJS}
		${CCPP} ${CPPFLAGS} -o ${NAME} ${OBJS}


all:		$(NAME)


clean:
		rm -f ${OBJS}


fclean:		clean
		rm -f ${NAME}


re:		fclean ${NAME}


.PHONY:		all clean fclean re
