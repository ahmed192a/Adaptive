# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>

typedef struct MSG
{
    int Process_id;
    int service_id;
    int port_num;
}MSG;

int main(int argc, char **argv)
{
    union sigval sigval;
    pid_t pid;

    MSG* newMsg = new MSG;
    newMsg->Process_id = 1;
    newMsg->service_id = 9;
    newMsg->port_num = 2;

    if (argc < 2 || (pid = atoi(argv[1])) < 0)
	return EXIT_FAILURE;
    //sigval.sival_int = time(NULL) & 0xff;
    sigval.sival_int = newMsg->Process_id;
    printf("sender: sending %d to PID %d\n",
    sigval.sival_int, pid);
    sigqueue(pid, SIGUSR1, sigval);

    sigval.sival_int = newMsg->service_id;
    printf("sender: sending %d to PID %d\n",
        sigval.sival_int, pid);
    sigqueue(pid, SIGUSR1, sigval);

    sigval.sival_int = newMsg->port_num;
    printf("sender: sending %d to PID %d\n",
        sigval.sival_int, pid);
    sigqueue(pid, SIGUSR1, sigval);

    return EXIT_SUCCESS;
}