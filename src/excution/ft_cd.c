#include "../../includes/minishell.h"

static void	ft_chdir(t_shell *_shell, char *str)
{
	char *cur_working;

	cur_working = getcwd(NULL, 1024);
	if (!chdir(str))
	{
		ch_pwd(_shell);
		_shell->status = 0;
		//add_var(char **env, char *var, char *value, int equal)
		if (!edit_var(_shell->env, "OLDPWD", cur_working, 1))
			_shell->env = add_var(_shell->env, "OLDPWD", cur_working, 1);
		return ;
	}
	// ft_printf("minishell: %s: No such file or directory\n", _shell->pipes->content->commands[1]);
	ft_printf("minishell: No such file or directory\n");
	_shell->status = 1;
}

void	ft_exe_cd(t_shell *_shell)
{
	char	*str;
	// int		status;
	// int		pid;
	if (_shell->pipes->next || _shell->i > 1)
		return ;
	// pid = fork();
	// if (pid == -1)
	// 	return ;
	// if (pid == 0)
	// {
		if (_shell->pipes->content->commands[1] == NULL
			|| !ft_strncmp(_shell->pipes->content->commands[1], "~", 1))
		{
			str = ft_getenv(_shell->env, "HOME");
			if (!str)
			{
				ft_printf("minishell: %s: HOME not set\n", _shell->pipes->content->commands[0]);
				_shell->status = 1;
			}
			else
			{
				ft_chdir(_shell, str);
				free(str);
			}
		}
		else
			ft_chdir(_shell, _shell->pipes->content->commands[1]);
		
		// exit (0);
	// }
	// wait(&status);
	// if (WIFEXITED(status))
    //     _shell->status = WEXITSTATUS(status);
}
