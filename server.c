/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenzidi <ybenzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:32:08 by ybenzidi          #+#    #+#             */
/*   Updated: 2025/03/09 20:32:08 by ybenzidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./minitalk.h"

void	take_action(char *c, int *bit)
{
	ft_printf("%c", *c);
	*c = 0;
	*bit = 0;
}
void	handle_signals(int sig, siginfo_t *info, void *context)
{
	static int	bit;
	static char	c;
	static int	client_pid;
	int			current_pid;

	current_pid = info->si_pid;
	(void)context;
	if (client_pid == 0)
		client_pid = current_pid;
	if (client_pid != current_pid)
	{
		bit = 0;
		c = 0;
		client_pid = current_pid;
	}
	c <<= 1;
	if (sig == SIGUSR1)
		c |= 1;
	bit++;
	if (bit == 8)
		take_action(&c, &bit);
	usleep(100);
	kill(client_pid, SIGUSR1);
}
int	main(void)
{
	struct sigaction sa;
	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = handle_signals;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}