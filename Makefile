NAME = minishell

CC = gcc

CFLAGS = -Werror -Wall -Wextra -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include

RM = rm -rf

SRCS =	main.c\
		readline.c\
		split_cmd.c\
		init_cmd.c\
		init_cmd2.c\
		init_cmd3.c\
		signal.c\
		env.c\
		utils.c\
		utils2.c\
		utils3.c\
		cmd/cd.c\
		cmd/echo.c\
		cmd/env.c\
		cmd/exit.c\
		cmd/export.c\
		cmd/pwd.c\
		cmd/unset.c\
		cmd/redirect.c\
		cmd/exec_cmd_1.c\
		cmd/exec_cmd_2.c\
		cmd/exec_cmd_3.c\
		cmd/pipe.c\
		cmd/pipe_utils.c\
		cmd/utils.c\
		cmd/env_utils.c\
		cmd/redirect_one.c
	
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
