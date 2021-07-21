NAME = minishell

CC = gcc

#CFLAGS = -Werror -Wall -Wextra -lreadline
CFLAGS = -lreadline

RM = rm -rf

SRCS =	main.c\
		readline.c\
		split_cmd.c\
		init_cmd.c\
		libft/ft_memset.c\
		libft/ft_strlcpy.c

$(NAME) :
	gcc $(CFLAGS) $(SRCS) -o $(NAME)
	./$(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(NAME)

re : fclean all