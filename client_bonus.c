#include "./minitalk.h"

static int	g_ack_received = 0;

void	received_message(int sig)
{
	(void)sig;
	ft_printf("\033[1;32mThe message was received\033[0m\n");
}

static void	recieved_bonus(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR2)
		received_message(sig);
	else if (sig == SIGUSR1)
		g_ack_received = 1;
}
int ft_atoi(const char *str)
{
    int result = 0;
    int sign = 1;

    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    while (*str)
    {
        if (*str >= '0' && *str <= '9')
        {
            result = result * 10 + (*str - '0');
            str++;
        }
        else
        {
            return 0;
        }
    }
    return result * sign;
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
				return;
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return;
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
	int					pid;
	struct sigaction	sa;

	if (argc != 3)
	{
        ft_printf("Use this format: <PID> <message>\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	int server_pid = ft_atoi(argv[1]);
    if (server_pid <= 0)
    {
        ft_printf("Invalid PID\n");
        return 0;
    }
	sa.sa_sigaction = &recieved_bonus;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sent_msg(argv[2], pid);
	return (0);
}