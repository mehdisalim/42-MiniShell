#include "../includes/main.h"

char **ft_split_path(t_shell _shell)
{
	return(ft_split(_shell.path, ':'));
}

char **ft_split_cmd(t_shell _shell)
{
	return(ft_split(_shell.cmd, ' '));
}

int count_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

char *ft_args(char **cmd)
{
	int i;
	int j;
	int k;
	int len = 0;
	char *args;
	int num_of_args;

	i = 1;
	k = 0;
	while (cmd[i])
	{
		len += ft_strlen(cmd[i]);
		i++;
	}
	i = 0;
	num_of_args = count_args(cmd);
	args = malloc(sizeof (char) * (num_of_args + len) + 1);

	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
			args[k++] = cmd[i][j++];
		args[k++] = ' ';
		i++;
	}
	args[k] = 0;
	return (args);
}

void ft_exec_cmd(t_shell _shell)
{
	int i;
	int p;
	char *args;

	args = ft_args(_shell.cmd_split);
	i = 0;
	p = fork();
	if (p == 0)
	{
		while (_shell.path_split[i])
		{
			
			//printf("\t%s\n", _shell.path_split[i]);
			if (access(_shell.path_split[i], F_OK) == 0)
			{
				printf("%s\n%s\n", _shell.path_split[i], args);
				char *str[] = {_shell.path_split[i], args, NULL};
				if (execve(_shell.path_split[i], str, _shell.ev))
					printf("Error in execve function\n");
			}
			i++;
		}
		printf("%s: commond not found\n", _shell.cmd);	
	}
	wait(0);
}

void ft_join(t_shell *_shell)
{
	int i;

	i = 0;
	while(_shell->path_split[i])
	{
		_shell->path_split[i] = ft_strjoin(_shell->path_split[i], "/");
		_shell->path_split[i] = ft_strjoin(_shell->path_split[i], _shell->cmd_split[0]);
		//printf("%s\n", _shell->path_split[i]);
		i++;
	}
}

int main(int ac, char *av[], char *ev[])
{
	t_shell _shell;
	int i;

	i = 0;
	

	(void)ac;	
	(void)av;	
	(void)ev;	
	_shell.ac = ac;
	_shell.av = av;
	_shell.ev = ev;
	_shell.path = getenv("PATH");
	_shell.path_split = ft_split_path(_shell);

	_shell.cmd = readline("minishell:$");
	_shell.cmd_split = ft_split_cmd(_shell);
	ft_join(&_shell);
	//printf("%s\n", ft_args(_shell.cmd_split));
	/*
	while(_shell.path_split[i])
	{
		_shell.path_split[i] = ft_strjoin(_shell.path_split[i], "/");
		_shell.path_split[i] = ft_strjoin(_shell.path_split[i], _shell.cmd_split[0]);
		i++;
	}
	*/

	
	ft_exec_cmd(_shell);
	/*
	while (_shell.cmd_split[i])
		printf("%s\n", _shell.cmd_split[i++]);
	*/
    return (0);
}
