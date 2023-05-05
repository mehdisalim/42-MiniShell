#include "../includes/minishell.h"

void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
        // rl_replace_line("", 0);
        rl_redisplay();
	}
}

int	main(int ac, char *av[], char *ev[])
{
	t_shell	_shell;

	
	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	_shell.env = ft_fill_env(ev, ft_count_env(ev));
	_shell.status = 0;
	while (1)
		minishel(&_shell);
	return (0);
}