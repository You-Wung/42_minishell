#ifndef MINISHELL_H
# define MINISHELL_H

/*include*/
#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>

/*define of color*/
#define COLOR_SET "\x1b[37m"
#define COLOR_RESET "\x1b[0m"
/*define for flag*/
# define PIPE 1/* | */
# define R_RE 2/* > */
# define L_RE 3/* < */
# define R_APP 4/* >> */
# define L_APP 5/* << */
# define SEMICOLON 6/* ; */

# define ERROR -1

typedef struct		s_cmd
{
	char			**cmd;/*커맨드, 마지막은 NULL*/
	char			**env;/*환경변수, 팔요없으면 NULL*/
	int				flag;/*0이면 끝, 리다이렉션이나, 파이프 대비*/
}					t_cmd;

typedef struct	s_match
{
	int			comma;/* ' " ` 쌍 맞는지*/
	int			dcomma;
	int			backtick;
}				t_match;


typedef struct	s_id
{
	pid_t		pid[100];	/*시그널. fork된 만큼 pid 배열에 담고
							kill 함수 이용해서 signal 해당 프로세스로 보내고
							해당 프로세스에서 다른 모든 프로세스 kill 죽인다*/
}				t_id;


int	start_read(char **env);
void	fill_cmd(t_cmd **c, char *input, char **env);/*cmd채우는 함수*/
char	*init_cmd(t_cmd *c, char *input, char **env);/*실제로 cmd에 인덱스 넣어주는과정*/
void	set_flag(t_cmd *c, char *input);/*flag 설정*/
void	init_signal();/*시그널 처리*/



#endif