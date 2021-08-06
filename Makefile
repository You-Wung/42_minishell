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
		env.c\
		cmd/cd.c\
		cmd/echo.c\
		cmd/env.c\
		cmd/exit.c\
		cmd/export.c\
		cmd/pwd.c\
		cmd/unset.c\
		cmd/redirect_L.c\
		cmd/redirect_R.c\
		cmd/redirect_LL.c\
		cmd/redirect_RR.c\
		cmd/exec_cmd.c\
		cmd/pipe.c\
		libft/ft_memset.c\
		libft/ft_strlcpy.c\
		libft/ft_strlen.c\
		libft/ft_strjoin.c\
		libft/ft_split.c\
		libft/ft_atoi.c\
		libft/ft_strcmp.c

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