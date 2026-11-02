#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

long copy_file(const char *src, const char *dst, size_t bufsize)
{
    char buf[8192];
    int in = open(src, O_RDONLY);
    if (in < 0) return -1;
    int out = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out < 0) { close(in); return -1; }

    long calls = 0;
    ssize_t n;

    /* TODO completed: count every read, stop at EOF, retry interrupted calls,
       and ensure all bytes from each successful read are written. */
    if (bufsize == 0 || bufsize > sizeof buf) {
        close(in); close(out); errno = EINVAL; return -1;
    }
    for (;;) {
        do {
            n = read(in, buf, bufsize);
            calls++;
        } while (n < 0 && errno == EINTR);

        if (n == 0) break;
        if (n < 0) {
            close(in); close(out);
            return -1;
        }

        ssize_t written = 0;
        while (written < n) {
            ssize_t w = write(out, buf + written, (size_t)(n - written));
            if (w < 0 && errno == EINTR) continue;
            if (w <= 0) {
                close(in); close(out);
                return -1;
            }
            written += w;
        }
    }

    if (close(in) < 0) { close(out); return -1; }
    if (close(out) < 0) return -1;
    return calls;
}

int main(void)
{
    FILE *f = fopen("records.dat", "w");
    if (!f) { perror("fopen"); return 1; }
    for (int i = 0; i < 10000; i++) fputc('A' + i % 26, f);
    if (fclose(f) != 0) { perror("fclose"); return 1; }

    size_t sizes[] = {1, 512, 4096};
    for (int i = 0; i < 3; i++) {
        long result = copy_file("records.dat", "copy.dat", sizes[i]);
        if (result < 0) { perror("copy_file"); return 1; }
        printf("buffer %4zu bytes: %5ld read() calls\n", sizes[i], result);
    }

    unlink("records.dat");
    unlink("copy.dat");
    return 0;
}
