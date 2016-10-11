#include "errno.h"
#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
bool slept = false;
void handler(int signum, siginfo_t *siginfo, void *context) {
    if(slept) return;
    int sigusrNumber = (signum == SIGUSR1 ? 1 : 2);
    printf("SIGUSR%d from %d\n", sigusrNumber, siginfo->si_pid);
    exit(0);
}
void assertError(int ret){
    if(ret == -1){
	int curerrno = errno;
	dprintf(STDERR_FILENO, "an error occured: %d\n", curerrno);
	exit(curerrno);
    }
}

int main() {
    struct sigaction action;
    action.sa_sigaction = &handler;
    action.sa_flags = SA_SIGINFO;
    assertError(sigemptyset(&action.sa_mask)); //UD otherwise
    assertError(sigaddset(&action.sa_mask, SIGUSR1));
    assertError(sigaddset(&action.sa_mask, SIGUSR2));

    if (sigaction(SIGUSR1, &action, NULL) == -1 || sigaction(SIGUSR2, &action, NULL) == -1) {
        dprintf(STDERR_FILENO, "Not able to install signal handler!\n");
        return errno;
    }
    sleep(10);
    slept = true;
    printf("No signals were caught\n");

    return 0;
}