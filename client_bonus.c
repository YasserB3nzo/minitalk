/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenzidi <ybenzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:32:14 by ybenzidi          #+#    #+#             */
/*   Updated: 2025/03/09 20:32:14 by ybenzidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./minitalk.h"

static int	g_ack_received = 0;
void	received_message(void)
{
	ft_printf("The message was received\n");
}
static void	recieved_bonus(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR2)
		received_message();
	else if (sig == SIGUSR1)
		g_ack_received = 1;
}
int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	if (*str == '-' || *str == '+')
		return (0);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			result = result * 10 + (*str - '0');
			str++;
		}
		else
			return (0);
	}
	return (result);
}
void	handler_bonus(int pid, char c)
{
	unsigned char	temp;
	int				i;

	temp = c;
	i = 8;
	while (i > 0)
	{
		i--;
		g_ack_received = 0;
		if (temp >> i & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				return ;
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return ;
		}
		while (!g_ack_received)
			pause();
		usleep(5);
	}
}
void	sent_msg(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
		handler_bonus(pid, str[i++]);
	handler_bonus(pid, '\0');
}
int	main(int argc, char **argv)
{
	int pid;
	struct sigaction sa;
	if (argc != 3)
	{
		ft_printf("Use this format: <PID> <message>\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("Invalid PID\n");
		return (0);
	}
	sa.sa_sigaction = &recieved_bonus;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sent_msg(argv[2], pid);
	return (0);
}