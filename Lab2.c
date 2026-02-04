#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(void) {

    const int numberOfChildren = 17;
    pid_t childPids[17];
    int status;

    printf("Parent process PID: %d\n", getpid());

    for (int i = 0; i < numberOfChildren; i++) {

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // CHILD PROCESS
            printf("Child #%d PID=%d starting...\n", i, getpid());

            switch (i) {

                //  VALID COMMANDS 
                case 0:
                    printf("Executing: ls -l\n");
                    execvp("ls", (char *const[]){"ls", "-l", NULL});
                    break;

                case 1:
                    printf("Executing: date\n");
                    execvp("date", (char *const[]){"date", NULL});
                    break;

                case 2:
                    printf("Executing: pwd\n");
                    execvp("pwd", (char *const[]){"pwd", NULL});
                    break;

                case 3:
                    printf("Executing: whoami\n");
                    execvp("whoami", (char *const[]){"whoami", NULL});
                    break;

                case 4:
                    printf("Executing: uname -a\n");
                    execvp("uname", (char *const[]){"uname", "-a", NULL});
                    break;

                case 5:
                    printf("Executing: id\n");
                    execvp("id", (char *const[]){"id", NULL});
                    break;

                case 6:
                    printf("Executing: ps\n");
                    execvp("ps", (char *const[]){"ps", NULL});
                    break;

                case 7:
                    printf("Executing: uptime\n");
                    execvp("uptime", (char *const[]){"uptime", NULL});
                    break;

                case 8:
                    printf("Executing: hostname\n");
                    execvp("hostname", (char *const[]){"hostname", NULL});
                    break;

                case 9:
                    printf("Executing: echo \"Hello Aty\"\n");
                    execvp("echo", (char *const[]){"echo", "Hello Aty", NULL});
                    break;

                //  INVALID COMMANDS 
                case 10:
                    printf("Executing invalid command: badcommand123\n");
                    execvp("badcommand123", (char *const[]){"badcommand123", NULL});
                    perror("execvp failed");
                    exit(127);

                case 11:
                    printf("Executing invalid command: not_a_real_cmd\n");
                    execvp("not_a_real_cmd", (char *const[]){"not_a_real_cmd", NULL});
                    perror("execvp failed");
                    exit(127);

                //ABORT CHILDREN 
                case 12:
                    printf("Child #%d calling abort() intentionally\n", i);
                    abort();

                case 13:
                    printf("Child #%d calling abort() intentionally\n", i);
                    abort();

                //  VALID COMMANDS
                case 14:
                    printf("Executing: env\n");
                    execvp("env", (char *const[]){"env", NULL});
                    break;

                case 15:
                    printf("Executing: wc --help\n");
                    execvp("wc", (char *const[]){"wc", "--help", NULL});
                    break;

                case 16:
                    printf("Executing: printf \"Done\\n\"\n");
                    execvp("printf", (char *const[]){"printf", "Done\n", NULL});
                    break;
            }
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }

        // PARENT stores PID
        childPids[i] = pid;
    }

    // PARENT WAITING
    int normalZero = 0;
    int normalNonZero = 0;
    int signaled = 0;

    for (int i = 0; i < numberOfChildren; i++) {
        pid_t w = waitpid(childPids[i], &status, 0);

        if (w < 0) {
            perror("waitpid");
            continue;
        }

        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            printf("[Parent] Child #%d (PID=%d) exited normally with code %d\n",
                   i, childPids[i], code);

            if (code == 0) normalZero++;
            else normalNonZero++;
        }
        else if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            printf("[Parent] Child #%d (PID=%d) terminated by signal %d\n",
                   i, childPids[i], sig);
            signaled++;
        }
    }

    // ---------- SUMMARY ----------
    printf("Normal exit, code 0:          %d\n", normalZero);
    printf("Normal exit, non-zero code:   %d\n", normalNonZero);
    printf("Terminated by signal:         %d\n", signaled);

    return 0;
}
