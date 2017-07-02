#include <fcntl.h>
#include <gaio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
    struct gaio_Io io;
    int fd = STDOUT_FILENO;
    io.object.pointer = &fd;
    char* buf = "HELLO WORLD!\n";
    io.read = gaio_Nop_read;
    io.write = gaio_FdPointer_write;
    io.write(&io, buf, sizeof("HELLO WORLD!\n") - 1);
    io.close = gaio_Nop_close;
    io.close(&io);
    io.fcntl = gaio_FdPointer_fcntl;
    io.fcntl(&io, F_SETFL, io.fcntl(&io, F_GETFL, 0) | O_NONBLOCK);
};
