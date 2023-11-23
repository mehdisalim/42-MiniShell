#include "../../../includes/minishell.h"

char	*ft_str_tolower(char *cmd)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_calloc(ft_strlen(cmd) + 1, 1);
	if (!str)
		return (0);
	while (cmd[i])
	{
		str[i] = ft_tolower(cmd[i]);
		i++;
	}
	// str[i] = 0;
	return (str);
}

int	ft_get_index_reverse(char *str, char c, int count)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i && count)
	{
		if (str[i] == c)
			count--;
		if (count == 0)
			return (i);
		i--;
	}
	return (0);
}

char* ft_getvar_(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			break ;
	}
	return (ft_substr(str, 0, i));
}

// int ft_get_index(char *str, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
