#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>     // fork, execv, write, access
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // waitpid, WIFEXITED, WEXITSTATUS
#include <errno.h>
#include <stdio.h>      // snprintf, perror
#include <string.h>
// TODO: Include more header files (read the manpages to find out more!)
static void wout(const char *s) { write(1, s, strlen(s)); }
static void werr(const char *s) { write(2, s, strlen(s)); }
int main(int argc, const char* argv[]) {
    // TODO: Complete and document
    if (argc == 1) {
        werr("ERROR: no arguments\n");
        return 1;
    }
    if (argc != 3){
        werr("USAGE: ./partc WORD FILE\n");
        return 1;
    }

    const char *word = argv[1];
    const char *file = argv[2];

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0){
        char *args[] = { "grep", "-s", "-q", (char *)word, (char*)file, NULL};
        execv("/usr/bin/grep", args);

        perror("exec");
        _exit(127);
    }
    int status = 0;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return 1;
    }
    if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        if (code == 0) {
            wout("FOUND: ");
            wout(word);
            wout("\n");
            return 0;
        } else if (code == 1) {
            wout("NOT FOUND: ");
            wout(word);
            wout("\n");
            return 0;
        } else {
            // grep exit 2 (or other) => generic ERROR and exit 2
            werr("ERROR\n");
            return 2;
        }
    }

    // Child didn’t exit normally
    werr("ERROR\n");
    return 2;
}