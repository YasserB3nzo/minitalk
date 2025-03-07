#include "./minitalk.h"

void take_action(char c)
{
    ft_printf("%c", c);
}

void handle_signals(int sig, siginfo_t *info, void *context)
{
    static int bit = 0;
    static char c = 0;
    static int client_pid = 0;
    int current_pid = info->si_pid;

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
    {
        take_action(c);
        bit = 0;
        c = 0;
    }

    if (kill(client_pid, SIGUSR1) == -1)
    {
        ft_printf("Error: Failed to send signal to client");
    }
}

int main(void)
{
    struct sigaction sa;

    printf("Server PID: %d\n", getpid());

    sa.sa_sigaction = handle_signals;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1)
    {
        pause();
    }

    return 0;
}
