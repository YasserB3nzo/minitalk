/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenzidi <ybenzidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:32:17 by ybenzidi          #+#    #+#             */
/*   Updated: 2025/03/10 16:05:32 by ybenzidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./minitalk.h"

static int	g_checkrecive = 0;

static void	recieved(int sig)
{
	(void)sig;
	g_checkrecive = 1;
}

static void	send_message(int pid, char c)
{
	unsigned char	temp;
	int				i;

	temp = c;
	i = 7;
	while (i >= 0)
	{
		if (temp >> i & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(1);
		}
		i--;
		while (!g_checkrecive)
			pause();
		g_checkrecive = 0;
		usleep(400);
	}
}

int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	if (*str == '-' || *str == '+')
	{
		return (0);
	}
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

int	main(int ac, char *av[])
{
	int		server_pid;
	char	*msg;

	if (ac != 3)
	{
		ft_printf("Use this format: <PID> <message>\n");
		return (0);
	}
	server_pid = ft_atoi(av[1]);
	if (server_pid <= 0)
	{
		ft_printf("Invalid PID\n");
		return (0);
	}
	signal(SIGUSR1, recieved);
	msg = av[2];
	while (*msg)
	{
		send_message(server_pid, *msg);
		msg++;
	}
	return (1);
}
