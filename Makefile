# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		= 	ft_malcolm

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

SRC			= 	.

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			=	main.c

SRCDIR		= srcs
SRCS		= $(addprefix $(SRCDIR)/, $(SRC))

OBJDIR		= .obj
OBJS		= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

DEPDIR		= .dep
DEPS		= $(addprefix $(DEPDIR)/, $(SRC:.c=.d))

# -=-=-=-=-    INCLUDES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

HEADERS		=	./incs/ft_malcolm.h ./libft/libft.h

LIBFT		=	./libft/libft.a

MAKE		=	Makefile

# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pedantic -g -fsanitize=address
INCLUDES	= -I./

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(HEADERS) $(SRCS)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT)

${LIBFT}:
	@make -C ./libft

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(LIBFT) Makefile
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -MT $@ -MMD -MP -c $< -o $@
	@mkdir -p $(DEPDIR)
	@mv $(patsubst %.o,%.d,$@) $(subst $(OBJDIR),$(DEPDIR),$(@D))/
	
clean:
	@/bin/rm -f $(OBJS)
	@make -C ./libft clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all

.PHONY:  all clean fclean re ${LIBFT}