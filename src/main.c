#include "../includes/main.h"

/*
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
	i = 1;
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
*/

void exec_path_cmd(t_shell *_shell)
{
	if (ft_strchr(_shell->cmd, '/'))
	{
		if (access(_shell->first_part_cmd_l, F_OK) == 0)
		{
			if (execve(_shell->first_part_cmd_l, _shell->cmd_split, _shell->ev) == -1)
				printf("Error in execve function\n");
		}
		printf("bash: %s: No such file or directory\n", _shell->cmd_split[0]);
		exit (127);
	}
}
void ft_exec_cmd(t_shell *_shell)
{
	int i;
	int p;

	i = 0;
	p = fork();
	if (p == -1)
		exit(0);
	if (p == 0)
	{
		exec_path_cmd(_shell);
		while (_shell->path[i])
		{
			if (access(_shell->path[i], F_OK) == 0)
			{
				if (execve(_shell->path[i], _shell->cmd_split, _shell->ev) == -1)
					printf("Error in execve function\n");
			}
			i++;
		}
		printf("bash: %s: command not found\n", _shell->cmd_split[0]);
		exit (127);
	}
	wait(0);
}

void ft_join(t_shell *_shell)
{
	int i;
	char *help_for_free;

	i = 0;
	// if (ft_strchr(_shell->cmd, '/'))
	// {
	// 	free_split(_shell->pa);
	// 	_shell->pa[i] = _shell->cmd_split[0];
	// 	return ;
	// }

	while(_shell->path[i])
	{
		help_for_free = ft_strjoin(_shell->path[i], "/");
		free(_shell->path[i]);
		_shell->path[i] = help_for_free;
		help_for_free = ft_strjoin(_shell->path[i], _shell->cmd_split[0]);
		free(_shell->path[i]);
		_shell->path[i] = help_for_free;
		i++;
	}
}

// char *ft_get_pwd(t_shell *_shell)
// {
// 	int i;
// 	char **str;
// 	i = 0;
// 	while (_shell->ev[i])
// 	{
// 		str = ft_split(_shell->ev[i], '=');
// 		if (!ft_strncmp(str[0], "PWD",3))
// 			return (_shell->ev[i]);
// 		free_split(str);
// 		i++;
// 	}
// 	return (0);
// }

// void ch_oldpwd(t_shell *_shell)
// {
// 	int i;
// 	char **str;
// 	char *help_for_free;
// 	i = 0;
// 	while (_shell->ev[i])
// 	{
// 		str = ft_split(_shell->ev[i], '=');
// 		if (!ft_strncmp(str[0], "OLDPWD",6))
// 		{
// 			help_for_free = ft_strjoin("PWD=", ft_get_pwd(_shell));
// 			// free(pwd);
// 			_shell->ev[i] = help_for_free;
// 		}
// 		free_split(str);
// 		i++;
// 	}

// void ch_paths(t_shell *_shell, char *pwd)
// {
// 	ch_oldpwd(_shell);
// 	ch_pwd(_shell, pwd);
// }

// void skipdot_slash(char *str)
// {
// 	if (str[0] == '.' && str[1] == '/')
// 		str = (str + 2);
// }

void ft_exe_cd(t_shell _shell)
{
	if (_shell.cmd_split[1] == NULL || !ft_strncmp(_shell.cmd_split[1], "~", 1))
		cd_home(&_shell);
	// else if (!ft_strncmp(_shell.cmd_split[1], "/", 1))
	// 	cd_root(&_shell);
	// else if (!ft_strncmp(_shell.cmd_split[1], "..", 2))
	// 	cd_2dots(&_shell);
	else
		cd_path(&_shell);
}




int	ft_check_v(char **env, char *var)
{
	int		i;
	char	**str;

	i = 0;
	if (var[0] == '$')
		var++;
	while (env[i])
	{
		str = ft_split(env[i], '=');
		// printf("%s\n", str[0]);
		if (!ft_strncmp(str[0], var,ft_strlen(var)))
			return (i);
		free_split(str);
		i++;
	}
	return (-1);
}


void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
        //rl_replace_line("", 0);
        rl_redisplay();
	}
}

int	ft_edit_var(t_shell *_shell, char *var, char *value)
{
	int index_var;

	index_var = ft_check_v(_shell->ev, var);
	if (index_var != -1)
	{
		char *join_equal = ft_strjoin(var, "=");
		if (value)
		{
			printf("%s\n", var);
			printf("%d\n", ft_check_v(_shell->ev, var));
			if (ft_check_v(_shell->ev, var) != -1)
				_shell->ev[index_var] = ft_strjoin(join_equal, value);
			else
				_shell->ev[index_var] = ft_strjoin(join_equal, ft_getenv(_shell->ev , value));

		}
		else
			_shell->ev[index_var] = join_equal;
		return (1);
	}
	return (0);
}

int ft_count_env(char **env)
{

	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void fill_env(t_shell *_shell, char **ev, char *var, char *value)
{
	static int	for_free;
	char		*join_equal;
	int			i;

	i = 0;
	while (_shell->ev[i])
	{
		ev[i] = _shell->ev[i];
		i++;
	}
	join_equal = ft_strjoin(var, "=");
	// printf("%s\n", var);
	// printf("%d\n", ft_check_v(_shell->ev, var));
	if (ft_check_v(_shell->ev, var) != -1)
		ev[i] = ft_strjoin(join_equal, value);
	else
	{
		ev[i] = ft_strjoin(join_equal, ft_getenv(_shell->ev , value));
	}
	ev[i + 1] = 0;
	if (!for_free && for_free++)
		free_split(_shell->ev);
	free(var);
	_shell->ev = ev;
}

long ft_abs(long num)
{
	if (num > 0)
		return (num);
	else
		return (num * -1);
}
int check_var_error(char *var)
{
	int i;
	
	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char *ft_getenv(char **env, char *var)
{

	int index;
	char **str;

	index = ft_check_v(env, var);
	str = ft_split(env[index], '=');
	return (str[1]);
}

int ft_add_var(t_shell *_shell)
{
	char	*var;
	char	*value;
	char	**ev;
	int 	i;

	i = 1;
	value = 0;
	ev = malloc(sizeof(char *) * (ft_count_env(_shell->ev) + 2));
	if (!ev)
		return (0);

	while (_shell->cmd_split[i])
	{
		var = ft_substr(_shell->cmd_split[i], 0,\
		(ft_abs(ft_strchr(_shell->cmd_split[i], '=') - _shell->cmd_split[i])));
		if (!check_var_error(var))
			printf("bash: %s: `%s\': not a valid identifier\n", _shell->cmd_split[0], _shell->cmd_split[i++]);
		if (!_shell->cmd_split[i])
			return (0);
		if (ft_strchr(_shell->cmd_split[i], '='))
		{
			value = (ft_strchr(_shell->cmd_split[i], '=') + 1);
			if (!ft_edit_var(_shell, var, value))
			{
				printf("here\n");
				fill_env(_shell, ev, var, value);
			}
		}
		i++;
	}
	return (1);
}

void ft_exe_export(t_shell *_shell)
{
	if (_shell->cmd_split[1])
	{
		// printf("%d\n", ft_count_env(_shell->ev));
		ft_add_var(_shell);
		// printf("%d\n", ft_count_env(_shell->ev));

	}
	else
	{
		printf("No thing here\n");
	}
}

void ft_exe_command(t_shell *_shell)
{
	if (!ft_strncmp(_shell->first_part_cmd_l, PWD, 4)
		|| !ft_strncmp(_shell->first_part_cmd_l + (ft_get_index_reverse(_shell->first_part_cmd_l, '/', 1) + 1), PWD, 4))
		ft_exe_pwd(*_shell);
	else if (!ft_strncmp(_shell->first_part_cmd_l, ENV, 4)
		|| !ft_strncmp(_shell->first_part_cmd_l + (ft_get_index_reverse(_shell->first_part_cmd_l, '/', 1) + 1), ENV, 4))
		ft_exe_env(*_shell);
	else if (!ft_strncmp(_shell->first_part_cmd_l, CD, 3)
		|| !ft_strncmp(_shell->first_part_cmd_l + (ft_get_index_reverse(_shell->first_part_cmd_l, '/', 1) + 1), CD, 3))
		ft_exe_cd(*_shell);
	else if ((!ft_strncmp(_shell->first_part_cmd_l, EXP, 7)
		|| !ft_strncmp(_shell->first_part_cmd_l + (ft_get_index_reverse(_shell->first_part_cmd_l, '/', 1) + 1), EXP, 7)))
		ft_exe_export(_shell);
	// else if (!ft_strncmp(_shell->first_part_cmd_l, EXP, 7))
	// 	ft_exe_export(_shell);
	else
		ft_exec_cmd(_shell);

	
	
	 
	// if (_shell.cmd_split[0][0] == '/')
	// {
	// 	if (!ft_strncmp(&_shell.cmd_split[0][ft_get_index_reverse(_shell.cmd_split[0], '/') + 1], PWD, 3))
	// 		ft_pwd(1);        // is freed
	// }
	// else if (!ft_strncmp(&_shell.cmd_split[0][ft_get_index_reverse(_shell.cmd_split[0], '/')], PWD, 3))
	// 	ft_pwd(1);        // is freed


	// while (_shell.cmd_split[i])
	// {

	// 	if (path[i])
	// }
	// if (!ft_strncmp(_shell->cmd_split[0], PWD, 3))
	// else if (!ft_strncmp(_shell->cmd_split[0], "echo", 4))
	// 	ft_exe_echo(*_shell);
	// else if (!ft_strncmp(_shell->cmd_split[0], CD, 2))
	// 	ft_exe_cd(*_shell);
	// else if (!ft_strncmp(_shell->cmd_split[0], ENV, 3))
	// 	ft_exe_env(*_shell);
	// else if (!ft_strncmp(_shell->cmd_split[0], EXIT, 4))
	// 	exit (0);
	// //else if (!ft_strncmp(_shell->cmd_split[0], "export", 6))
	// //	ft_exe_export(_shell)
}


void print_struct(t_shell *_shell)
{
	int i = 0;
	// printf("path\t|%s|\n", _shell->path[]);
	while(_shell->path[i])
		printf("path splt\t|%s|\n", _shell->path[i++]);
	printf("-----------------------\n");
	

	i = 0;
	while(_shell->path[i])
		printf("pa splt\t\t|%s|\n", _shell->path[i++]);
	printf("-----------------------\n");

	printf("cmd\t\t|%s|\n", _shell->cmd);
	printf("first_part_cmd_l\t|%s|\n", _shell->first_part_cmd_l);
	printf("-----------------------\n");

	i = 0;
	while(_shell->cmd_split[i] != 0)
		printf("cmd splt\t|%s|\n", _shell->cmd_split[i++]);
}


int ft_init(t_shell *_shell)
{
	// _shell->path_split = ft_split(getenv("PATH"), ':');
	_shell->path = ft_split(getenv("PATH"), ':');

	_shell->cmd = readline("minishell:$ ");
	if (*_shell->cmd == 0)
		return (0);
	if (_shell->cmd == 0)
		exit (1);
	add_history(_shell->cmd);
	_shell->cmd_split = ft_split(_shell->cmd, ' ');
	_shell->first_part_cmd_l = ft_str_tolower(_shell->cmd_split[0]);
	_shell->second_part = _shell->cmd_split[1];
	return (1);

}

void ft_exe(t_shell *_shell)
{
	if (!ft_init(_shell))
		return ;
	ft_join(_shell);       // is freed
	ft_exe_command(_shell);

}

int main(int ac, char *av[], char *ev[])
{
	t_shell _shell;
	
	// (void)ac;
	// (void)av;
	// (void)ev;

	// printf("\n%d\n", ft_check_v(ev, "PATH"));
	// printf("\n%d\n", ""));


	// signal(SIGINT, sig_handler);

	_shell.ac = ac;
	_shell.av = av;
	_shell.ev = ev;
	while (1)
		ft_exe(&_shell);

	return (0);
}
