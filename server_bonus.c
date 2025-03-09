/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenzidi <ybenzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:32:12 by ybenzidi          #+#    #+#             */
/*   Updated: 2025/03/09 20:32:12 by ybenzidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minitalk.h"

void	take_action(char *c, int *bit, int *pid)
{
	if (*c == '\0')
		kill(*pid, SIGUSR2);
	else
		ft_printf("%s",c);
	*c = 0;
	*bit = 0;
}

void	handle_bonus(int sig, siginfo_t *info, void *context)
{
	static int		bit;
	static char		c;
	static int		current_pid;
	static int		client_pid;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	current_pid = info->si_pid;
	if (client_pid != current_pid)
	{
		bit = 0;
		c = 0;
		client_pid = current_pid;
	}
	c <<= 1;
	if (sig == SIGUSR1)
		c += 1;
	bit++;
	if (bit == 8)
	{
		take_action(&c, &bit, &client_pid);
	}
	usleep(5);
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d \n",getpid());
	sa.sa_sigaction = &handle_bonus;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
	return (0);
}