#ifndef MINISHELL_H
# define MINISHELL_H

/*include*/
# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <termios.h>
# include <errno.h>

/*define of color*/
# define COLOR_SET "\x1b[1;95m"
# define COLOR_RESET "\x1b[0m"
/*define for flag*/
# define PIPE 1/* | */
# define R_RE 2/* > */
# define L_RE 3/* < */
# define R_APP 4/* >> */
# define L_APP 5/* << */
# define SEMI 6/* ; */

# define ERROR -1
# define SUCCESS 0
/*커맨드, 마지막은 NULL*/
/*0이면 끝, 리다이렉션이나, 파이프 대비*/
typedef struct s_cmd
{
	char	**cmd;
	int		flag;
}	t_cmd;

/* ' " ` 쌍 맞는지*/
typedef struct s_match
{
	int	comma;
	int	dcomma;
	int	backtick;
}	t_match;

typedef struct s_env
{
	char			name[256];
	char			content[256];
	struct s_env	*next;
	int				flag;
}	t_env;

/*전역변수*/
/*pnum : pid[pnum]*/
/*qmark echo $?*/
typedef struct s_ext
{
	struct termios	restore;
	pid_t			pid[100];
	int				pnum;
	int				writing;	
	int				size_pi;
	int				size_se;
	t_env			*env;
	char			**n_env;
	int				qmark;
}	t_ext;

void	init_env(char **env);
int		start_read(void);
char	*make_prompt(void);

char	*fill_cmd(t_cmd *c, char *input);/*cmd채우는 함수*/
int		count_cmd(char *input);/* | > < ; 기준으로 커맨드 몇개로 잘릴까 */
char	*init_cmd(t_cmd *c, char *input);/*실제로 cmd에 인덱스 넣어주는과정*/
char	*set_flag(t_cmd *c, char *input, int *sign);/*flag 설정*/
int		check_input(char *input, t_match *m);
void	init_signal(void);/*시그널 처리*/
int		is_flag(char c);
char	*edit_input(char **input);
void	check_qmark(char **str);
int		all_space(char *input);

/* 명령어 */
int		ft_cd(t_env *env, char **cmd);
int		ft_echo(t_env *env, char **cmd);
int		ft_env(t_env *env);
int		ft_exit(char **cmd, int flag);
int		ft_export(t_env *env, char **cmd);
int		ft_pwd(void);
int		ft_redirect_L(t_cmd *c);
int		ft_redirect_R(t_cmd *c);
int		ft_redirect_RR(t_cmd *c);
int		ft_redirect_LL(t_cmd *c);
int		ft_unset(t_env **env, char **cmd);
int		ft_pipe(t_cmd *c);
int		ft_semicolon(t_cmd *c);

int		vaild_env_name(char c);
int		check_open(int in, t_cmd *c);
int		exec_cmd(t_cmd *c);
int		use_builtin(t_cmd *c, t_env *e);
int		use_redirect(t_cmd *c);
int		run_cmd(char **cmd, t_env *env);
int		use_redi_cmd(t_cmd *c);

#endif