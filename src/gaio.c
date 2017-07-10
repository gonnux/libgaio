#include <fcntl.h>
#include <stdarg.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <libgenc/genc_generic.h>
#include "gaio.h"

int gaio_Nop_read(struct gaio_Io* io, void* buffer, int readSize) {
    return 0;
}

int gaio_Nop_write(struct gaio_Io* io, void* buffer, int writeSize) {
    return 0;
}

int gaio_Nop_sendfile(struct gaio_Io* outIo, struct gaio_Io* inIo, int* offset, int count) {
    return 0;
}

int gaio_Nop_fcntl(struct gaio_Io* io, int command, int argCount, ...) {
    return 0;
}

int gaio_Nop_fileno(struct gaio_Io* io) {
    return -1;
}

int gaio_Nop_close(struct gaio_Io* io) {
    return 0;
}

int gaio_FdPointer_read(struct gaio_Io* io, void* buffer, int readSize) {
    return read(*((int*)io->object.pointer), buffer, readSize);
}

int gaio_FdPointer_write(struct gaio_Io* io, void* buffer, int writeSize) {
    return write(*((int*)io->object.pointer), buffer, writeSize);
}

int gaio_FdPointer_fcntl(struct gaio_Io* io, int command, int argCount, ...) {
    va_list args;
    va_start(args, argCount);
    int returnValue = fcntl(*((int*)io->object.pointer), command, argCount, args);
    va_end(args);
    return returnValue;
}

int gaio_FdPointer_fileno(struct gaio_Io* io) {
    return (*((int*)io->object.pointer));
}

int gaio_FdPointer_close(struct gaio_Io* io) {
    int returnValue = close(*((int*)io->object.pointer));
    *((int*)io->object.pointer) = -1;
    return returnValue;
}

int gaio_Generic_sendfile(struct gaio_Io* outIo, struct gaio_Io* inIo, int* offset, int count) {
    return sendfile(outIo->fileno(outIo), inIo->fileno(inIo), offset, count);
}

