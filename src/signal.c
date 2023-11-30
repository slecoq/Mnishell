
#include "minishell.h"

extern int	g_received_signal;

void	ft_signal_handler(int num)
{
	g_received_signal = num;
	if (g_received_signal != 0)
	{
		if (g_received_signal == SIGINT)
		{
			ft_putstr_fd(1, "\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		g_received_signal = 0;
	}
}

void	ft_sigquit_handler(void)
{
	printf("exit\n");
}

void	ft_init_signals(void)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &term);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
