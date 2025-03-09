#include "./minitalk.h"

static int checkrecive = 0;

static void recieved(int sig)
{
    (void)sig;
    checkrecive = 1;
}

static void send_message(int pid, char c)
{
    unsigned char temp = c;
    int i = 7;

    while (i >= 0)
    {
        if (temp >> i & 1)
        {
            if (kill(pid, SIGUSR1) == -1)
            {
                ft_printf("Error: Failed to send SIGUSR1\n");
                return;
            }
        }
        else
        {
            if (kill(pid, SIGUSR2) == -1)
            {
                ft_printf("Error: Failed to send SIGUSR2\n");
                return;
            }
        }
        i--;
        while (!checkrecive)
            pause();
        checkrecive = 0;
    }
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

int main(int ac, char *av[])
{
    if (ac != 3)
    {
        ft_printf("Use this format: <PID> <message>\n");
        return 0;
    }

    int server_pid = ft_atoi(av[1]);
    if (server_pid <= 0)
    {
        ft_printf("Invalid PID\n");
        return 0;
    }

    signal(SIGUSR1, recieved);

    char *msg = av[2];
    while (*msg)
    {
        send_message(server_pid, *msg);
        usleep(200);
        msg++;
    }

    return 1;
}