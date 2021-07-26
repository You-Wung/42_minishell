NAME = minishell

CC = gcc

#CFLAGS = -Werror -Wall -Wextra -lreadline
CFLAGS = -lreadline

RM = rm -rf

SRCS =	main.c\
		readline.c\
		split_cmd.c\
		init_cmd.c\
		init_cmd2.c\
		signal.c\
		libft/ft_memset.c\
		libft/ft_strlcpy.c\
		libft/ft_strlen.c

$(NAME) :
	gcc $(CFLAGS) $(SRCS) -o $(NAME) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include
	#gcc $(CFLAGS) $(SRCS) -o $(NAME)
	#./$(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(NAME)

re : fclean all