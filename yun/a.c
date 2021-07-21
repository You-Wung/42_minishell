#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// #include <libxm12/libxml/parser.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd
{
	char		**cmd;/*커맨드, 마지막은 NULL*/
	char		**env;/*환경변수, 팔요없으면 NULL*/
	int			flag;/*0이면 끝, 리다이렉션이나, 파이프 대비*/
}				t_cmd;

typedef struct s_shell
{
	int exit_status;	// 0은 성공, 1 ~ 255 는 오류 코드(error code)
	int exit;			// 0은 실행중, 1은 종료
}				t_shell;

#define PATH_MAX 200
#define SUCCESS 0
#define ERROR -1



size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

static int	count(char const *s, char c)
{
	int		i;
	int		n;
	int		st;

	n = 0;
	i = 0;
	st = 0;
	while (s[i])
	{
		if (s[i] == c)
			st = 0;
		else if (st == 0)
		{
			st = 1;
			n++;
		}
		i++;
	}
	return (n);
}

static int	count_c(char const *s, char c, int i)
{
	int			n;

	n = 0;
	while (s[i] != c && s[i++])
		n++;
	return (n);
}

static char	**get_str(char **str, char const *s, char c, int n)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	while (s[i] && j < n)
	{
		k = 0;
		while (s[i] == c)
			i++;
		str[j] = malloc(sizeof(char) * count_c(s, c, i) + 1);
		if (!str[j])
		{
			while (j > 0)
				free((void *)str[j--]);
			free(str);
			return (NULL);
		}
		while (s[i] != c && s[i])
			str[j][k++] = s[i++];
		str[j++][k] = '\0';
	}
	str[j] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char		**str;
	int			n;

	if (s == NULL)
		return (NULL);
	n = count(s, c);
	str = malloc(sizeof(char *) * (n + 1));
	if (!str)
		return (NULL);
	return (get_str(str, s, c, n));
}

void	run_cmd(const char *cmd)
{
	int		i;
	char	**ar;

	i = 0;
	ar = ft_split(cmd, ' ');
	cmd = ft_strjoin("/bin/", ar[0]);
	execve(cmd, ar, NULL);
	cmd = ft_strjoin("/usr/local/bin/", ar[0]);
	execve(cmd, ar, NULL);
	cmd = ft_strjoin("/usr/bin/", ar[0]);
	execve(cmd, ar, NULL);
	cmd = ft_strjoin("/user/sbin/", ar[0]);
	execve(cmd, ar, NULL);
	cmd = ft_strjoin("/sbin/", ar[0]);
	execve(cmd, ar, NULL);
	perror(ar[0]);
}

int	check(unsigned long long ans, int sign)
{
	if (ans > 9223372036854775807)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (ans * sign);
}

int	ft_atoi(const char *str)
{
	unsigned long long	ans;
	int					sign;

	if (*str == 0)
		return (0);
	ans = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ('0' <= *str && *str <= '9'))
	{
		ans = ans * 10 + (*str - '0');
		str++;
	}
	return (check(ans, sign));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}



int ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n",cwd);
		return (SUCCESS);
	}
	else
		return (ERROR);
}

int ft_cd(char **cmd)
{
	char cwd[PATH_MAX];

	if (ft_strcmp(cmd[1], ".."))
	{
		if (getcwd(cwd, PATH_MAX))
			return (SUCCESS);
		else
			return (ERROR);
		cmd[1] = ft_strjoin("/", cmd[1]);
		cmd[1] = ft_strjoin(cwd, cmd[1]);
	}
	chdir(cmd[1]);
	return (SUCCESS);
}


int is_num(char *str)
{
	while (*str)
	{
		if ('0' > *str && *str > '9')
			return (ERROR);
		str++;
	}
	return (SUCCESS);
}

void ft_exit(char **cmd, t_shell *mini)
{
	mini->exit_status = 0;
	mini->exit = 1;
	printf("exit\n");
	if (cmd[1] && cmd[2])	// 인자가 2개 이상인 경우
	{
		mini->exit = 0;
		mini->exit_status = 1;
		printf("minishell: too many arguments\n");
	}
	else if (cmd[1] && is_num(cmd[1]) == ERROR)	// 인자가 숫자가 아닌 경우
	{
		mini->exit_status = 255;
		printf("minishell: numeric argument required\n");
	}
	else if (cmd[1])	// 인자가 숫자인 경우
		mini->exit_status = ft_atoi(cmd[1]);
}

int main(int ac, char *av[], char *env[])
{
	char **cmd;
    char* input, shell_prompt[100];
	t_shell mini;

	mini.exit = 0;
    while (mini.exit == 0) {
        input = readline("mini $ ");
        if (!input)
            break;
        add_history(input);
		cmd = ft_split(input, ' ');
		
		// int i=0;
		// while (env[i])
		// 	printf("%s\n", env[i++]);

		if (ft_strcmp(cmd[0], "cd") == 0)		// cd
			ft_cd(cmd);
		else if (ft_strcmp(cmd[0], "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(cmd[0], "exit") == 0)	// exit
			ft_exit(cmd, &mini);
		else
		{
			int	pid;
			int	status;
		
			if (input)
			{
				pid = fork();
				if (pid > 0)
					waitpid(pid, &status, 0);
				else if (pid == 0)
					run_cmd((const char *)input);
			}
		}
printf("%d %d\n", mini.exit, mini.exit_status);
        // Free input.
        free(input);
    }
	return (mini.exit_status);
}
