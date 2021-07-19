#ifndef MINISHELL_H
# define MINISHELL_H

# define PIPE 1/* | */
# define R_REDIRECT 2/* > */
# define L_REDIRECT 3/* < */
# define R_APPEND 4/* >> */
# define L_APPEND 5/* << */

typedef struct s_cmd
{
	char		**cmd;/*커맨드, 마지막은 NULL*/
	char		**env;/*환경변수, 팔요없으면 NULL*/
	int			flag;/*0이면 끝, 리다이렉션이나, 파이프 대비*/
}				t_cmd;


#endif