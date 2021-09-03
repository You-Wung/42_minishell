NAME = minishell

CC = gcc

CFLAGS = -Werror -Wall -Wextra -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include

RM = rm -rf

SRCS =	main.c\
		readline.c\
		split_cmd.c\
		init_cmd.c\
		init_cmd2.c\
		signal.c\
		env.c\
		utils.c\
		cmd/cd.c\
		cmd/echo.c\
		cmd/env.c\
		cmd/exit.c\
		cmd/export.c\
		cmd/pwd.c\
		cmd/unset.c\
		cmd/redirect_L.c\
		cmd/redirect_LL.c\
		cmd/redirect_R.c\
		cmd/redirect_RR.c\
		cmd/exec_cmd_1.c\
		cmd/exec_cmd_2.c\
		cmd/pipe.c\
		cmd/semicolon.c\
		cmd/utils.c

LIBFT = libft/ft_memset.c\
		libft/ft_strlcpy.c\
		libft/ft_strlen.c\
		libft/ft_strjoin.c\
		libft/ft_split.c\
		libft/ft_atoi.c\
		libft/ft_strdup.c\
		libft/ft_strcmp.c\
		libft/ft_itoa.c\
		libft/ft_strchr.c

$(NAME) : $(SRCS) $(LIBFT)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT)

all : $(NAME)

fclean : clean
	make fclean -C libft/
	$(RM) $(NAME) $(O_LIBFT) $(OBJS)

clean :
	make clean -C libft/
	$(RM) $(NAME) 

re : fclean all

.PHONY:	all clean fclean re