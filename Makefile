# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		= 	ft_malcolm

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

SRC			= 	.

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			=	main.c			\
				init.c			\
				malcolm.c		\
				parse.c

SRCDIR		= srcs
SRCS		= $(addprefix $(SRCDIR)/, $(SRC))

OBJDIR		= .obj
OBJS		= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# -=-=-=-=-    INCLUDES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

HEADERS		=	./incs/ft_malcolm.h ./libft/libft.h

LIBFT		=	./libft/libft.a

MAKE		=	Makefile

# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pedantic -g# -fsanitize=address
INCLUDES	= -I

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: make_libft $(NAME)

$(NAME): $(OBJS) $(HEADERS) $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

make_libft:
	@make -C libft

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES)./libft/ -c $< -o $@

docker_up:
	docker network create --subnet=172.18.0.0/16 my_bridge
	docker run -dit --name containerA --network my_bridge --ip 172.18.0.2 alpine sh
	docker run -dit --name containerB --network my_bridge --ip 172.18.0.3 alpine sh

docker_down:
	docker stop containerA containerB
	docker rm containerA containerB
	docker network rm my_bridge

example: $(NAME)
	sudo ./ft_malcolm 172.18.0.2 FF:FF:FF:FF:FF:FF 172.18.0.3 FF:FF:FF:FF:FF:FF	

clean:
	@/bin/rm -fr $(OBJDIR)
	@make -C ./libft clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all

.PHONY:  all clean fclean re make_libft docker_up docker_down example
