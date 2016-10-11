#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int BUF_SIZE = 1024;
    char buf[BUF_SIZE];
    ssize_t readLen = -1;
    while (readLen != 0) {
        readLen = read(STDIN_FILENO, (void *) buf, BUF_SIZE);
        if (readLen > 0) {
            ssize_t writeLen = 0;
            while (writeLen != readLen) {
                ssize_t result = write(STDOUT_FILENO, (void *) (buf + writeLen), readLen - writeLen);
                if (result == -1) {
                    fprintf(stderr, "Write Error %s\n", strerror(errno));
                    return 1;
                }
                writeLen += result;
            }
        } else if (readLen == -1) {
            fprintf(stderr, "Read Error %s\n", strerror(errno));
            return 2;
        }
    }
    return 0;
}