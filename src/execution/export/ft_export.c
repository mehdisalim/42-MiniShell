#include "../../../includes/minishell.h"

int	check_var_error(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_var_error(t_shell *_shell, char *var)
{
	if (!check_var_error(var))
	{
		// printf("minishel: %s: `%s\': not a valid identifier\n", \
		// 	_shell->pipes->content->commands[0], var);
		ft_printf("minishell: not a valid identifier\n");
		_shell->status = 1;
		return (0);
	}
	return (1);
}

static int	ft_getvar_and_value(char *command, char **env, char **var, char **value)
{
	char	*s;
	char	*s1;
	(void)env;

	s = 0;
	s1 = 0;

	*var = ft_getvar(command);
		
	// if (*var[0] == '$' && ft_check_var_exist(env, *var) != -1)
	// 	*var = ft_getenv(env, *var);
	if (ft_strchr(command, '='))
	{
		*value = ft_strdup((ft_strchr(command, '=') + 1));
		// printf("value |%s|\n", *value);

		// if (*value && *value[0] == '$' && ft_check_var_exist(env, *value) != -1)
		// 	*value = ft_getenv(env, *value);
	}
	return (0);
}


static int	ft_add_var(t_shell *_shell)
{
	char	*var;
	char	*value;
	int		i;
	int		equal;

	i = 1;
	while (_shell->pipes->content->commands[i])
	{
		var = 0;
		value = 0;
		ft_getvar_and_value(_shell->pipes->content->commands[i], _shell->env, &var, &value);
		if (ft_strchr(_shell->pipes->content->commands[i], '='))
			equal = 1;
		else
			equal = 0;
		if (ft_var_error(_shell, var))
		{
			if (!edit_var(_shell->env, var, value, equal))
				_shell->env = add_var(_shell->env, var, value, equal);
		}
		free(var);
		free(value);
		i++;
	}
	return (0);
}

void	ft_exe_export(t_shell *_shell)
{
	int	pid;
	int	status;

	if (_shell->pipes->content->commands[1])
		ft_add_var(_shell);
	else
	{
		pid = fork();
		if (pid == -1)
			exit (1);
		if (pid == 0)
		{
			setup_all(_shell);
			ft_display_export(_shell->env);
			exit(0);
		}
		wait(&status);
		if (WIFEXITED(status))
			_shell->status = WEXITSTATUS(status);
	}
}
