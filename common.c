#define XOPEN_SOURCE 600 // strtoul

#include <stdlib.h>
#include <errno.h>

#include "err.h"
#include "common.h"

int
convert_channel_num(
    char *s,
    unsigned int *channel_num,
    err_t err
) {
    unsigned int ui;

    if (!convert_string_to_unsigned_int(s, &ui)) {
        err_set2(err, "invalid channel number \"%s\"", s);
        return 0;
    }

    if (ui > 15) {
        err_set2(err, "invalid channel number \"%s\", should be 0..15", s);
    }

    *channel_num = ui;
    return 1;
}

int
convert_sample_num(
    char *s,
    unsigned int *sample_num,
    err_t err
) {
    unsigned int ui;

    if (!convert_string_to_unsigned_int(s, &ui)) {
        err_set2(err, "invalid sample number \"%s\"", s);
        return 0;
    }

    if (ui > 16383) {
        err_set2(err, "invalid sample number \"%s\", should be 0..16383", s);
    }

    *sample_num = ui;
    return 1;
}

int
convert_string_to_unsigned_int(
    char *s,
    unsigned int *ui
) {
    char *endptr;
    unsigned int c;

    errno = 0;
    c = strtoul(s, &endptr, 0);

    if (
        errno   != 0    ||
        *s      == '\0' ||
        *endptr != '\0'
    ) {
        return 0;
    }

    *ui = c;
    return 1;
}

