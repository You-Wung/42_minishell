#include "../minishell.h"

int del_use(void)
{
    pid_t   pid;
    int     status;
    char    **del;

    pid = fork();
    if (pid < 0)
    {
        printf("fork error\n");
        return (-1);
    }
    if (pid == 0)
    {
        del = ft_split("rm ./%%user_tmp", ' ');
        run_cmd(del);
    }
    if (pid > 0)
        waitpid(pid, &status, 0);
    return (0);
}

int ft_redirect_LL(t_cmd *c)
{
    pid_t   pid;
    int     in;
    int     status;
    char    *buf;

    pid = fork();
    if (pid < 0)
    {
        printf("fork error\n");
        return (-1);
    }
    if (pid == 0)
    {
        in = open("%%user_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (in < 0)
            return (ERROR);
        while(1)
        {
            buf = readline(" > ");
            if (ft_strcmp(buf, c[1].cmd[0]) == 0)
                break ;
            if (buf)
            {
                write(in, buf, ft_strlen(buf));
                write(in, "\n", 1);
            }
            free(buf);
        }
        close(in);

        in = open("%%user_tmp", O_RDONLY);
        if (in < 0)
        {
            printf("minishell: no such file or directory\n");
            return (ERROR);
        }
        dup2(in, STDIN_FILENO);
        run_cmd(c[0].cmd);
        close(in);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        if (del_use() == -1)
            return (-1);
    }
    return (0);
}
