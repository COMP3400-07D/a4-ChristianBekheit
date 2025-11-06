#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {
    int n = argc -1;

    if (n==0){
        static const char msg[] = "ERROR: no arguments\n";
        write(2, msg, sizeof(msg)-1);
        return 1;
    }

    char *eargs[4];
    eargs[0] = "echo";

    if (n%2 ==1){
        int mid = 1 + n / 2;
        eargs[1] = (char *)argv[mid];
        eargs[2] = NULL;
    } else {
        int left = n / 2;
        int right = left + 1;
        eargs[1] = (char *)argv[left];
        eargs[2] = (char *)argv[right];
        eargs[3] = NULL;
    }

    int ret = execv("/bin/echo", eargs);
    if (ret == -1){
        perror("exec");
        return 1;
    }
    return 0;

}
