# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>

void signal_handler(int signum, siginfo_t *siginfo, void *ucontext)
{
    if (signum != SIGUSR1) return;
    if (siginfo->si_code != SI_QUEUE) return;

    printf("receiver: Got value %d\n",
	    siginfo->si_int);
}

int main(int argc, char **argv)
{
    pid_t pid = getpid();
    struct sigaction signal_action;

    printf("receiver: PID is %d\n", pid);

    signal_action.sa_sigaction = signal_handler;
    sigemptyset (&signal_action.sa_mask);
    signal_action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &signal_action, NULL);

    while(1) sleep(100);
    return EXIT_SUCCESS;
}