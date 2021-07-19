#ifndef MINISHELL_H
# define MINISHELL_H

/*define of color*/
#define COLOR_SET "\x1b[37m"
#define COLOR_RESET "\x1b[0m"
/*define*/
# define PIPE 1/* | */
# define R_REDIRECT 2/* > */
# define L_REDIRECT 3/* < */
# define R_APPEND 4/* >> */
# define L_APPEND 5/* << */
# define ERROR -1

/*include*/
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

typedef struct	s_cmd
{
	char		**cmd;/*커맨드, 마지막은 NULL*/
	char		**env;/*환경변수, 팔요없으면 NULL*/
	int			flag;/*0이면 끝, 리다이렉션이나, 파이프 대비*/
	int			comma_match;/* ' " ` 쌍 맞는지*/
	int			dcomma_match;
	int			backtick;
}				t_cmd;

typedef struct	s_id
{
	pid_t		pid[100];	/*시그널. fork된 만큼 pid 배열에 담고
							kill 함수 이용해서 signal 해당 프로세스로 보내고
							해당 프로세스에서 다른 모든 프로세스 kill 죽인다*/
}				t_id;


int	start_read(void);

#endif