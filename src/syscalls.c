#include "hal.h"
#include <stddef.h>
#include <sys/stat.h>

int _write(int fd, char *buf, int len) {
    (void)fd, (void)buf, (void)len;
    if (fd == 1) uart_write_buf(UART_DEBUG, buf, (size_t)len);
    return -1;
}

int _fstat(int fd, struct stat *st) {
    (void)fd;
    st->st_mode = S_IFCHR;
    return 0;
}

void *_sbrk(int incr) {
    extern char _end;
    static unsigned char *heap = NULL;
    unsigned char *prev_heap;
    if (heap == NULL) heap = (unsigned char *)&_end;
    prev_heap = heap;
    heap += incr;
    return prev_heap;
}

int _open(const char *path) {
    (void)path;
    return -1;
}

int _close(int fd) {
    (void)fd;
    return -1;
}

int _isatty(int fd) {
    (void)fd;
    return 1;
}

int _lseek(int fd, int ptr, int dir) {
    (void)fd, (void)ptr, (void)dir;
    return 0;
}

void _exit(int status) {
    (void)status;
    for (;;) asm volatile("BKPT #0");
}

void _kill(int pid, int sig) { (void)pid, (void)sig; }

int _getpid(void) { return -1; }

int _read(int fd, char *buf, int len) {
    (void)fd;
    for (int i = 0; i < len; i++) { buf[i] = uart_read_byte(UART_DEBUG); }
    return len;
}

int _link(const char *a, const char *b) {
    (void)a, (void)b;
    return -1;
}

int _unlink(const char *a) {
    (void)a;
    return -1;
}

int _stat(const char *path, struct stat *st) {
    (void)path, (void)st;
    return -1;
}

int mkdir(const char *path, mode_t mode) {
    (void)path, (void)mode;
    return -1;
}

void _init() {}
