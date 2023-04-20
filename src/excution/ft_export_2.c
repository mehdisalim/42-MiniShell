#include "../../includes/minishell.h"

int	edit_var(char **str, char *var, char *value, int check)
{
	int		index_var;
	char	*free_var;
	char	*join_equal;

	index_var = ft_check_var_exist(str, var);
	if (index_var != -1 && *var)
	{
		join_equal = ft_strjoin(var, "=");
		free_var = str[index_var];
		if (value)
			str[index_var] = ft_strjoin(join_equal, value);
		else
		{
			if (check == ENV)
				str[index_var] = ft_strdup(join_equal);
			if (check == EXP && ft_strchr(str[index_var], '='))
				str[index_var] = ft_strdup(join_equal);
			else
				str[index_var] = ft_strdup(var);
		}
		free(free_var);
		free(join_equal);
		return (1);
	}
	return (0);
}

char	**add_var(char **env, char *var, char *value, int new)
{
	char	**add_line_env;
	char	*join_equal;
	int		i;
	int		lines;

	lines = ft_count_env(env);
	add_line_env = malloc((lines + 2) * sizeof(char *));
	if (!add_line_env)
		return (0);
	i = -1;
	while (env[++i])
		add_line_env[i] = ft_strdup(env[i]);
	join_equal = ft_strjoin(var, "=");
	if (value || new)
		add_line_env[i] = ft_strjoin(join_equal, value);
	else
		add_line_env[i] = ft_strdup(var);
	free(join_equal);
	free_split(env);
	add_line_env[i + 1] = 0;
	return (add_line_env);
}
