#include <6502.h>
#include <cx16.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <cbm.h>

#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "config.h"

#define BUF_SIZE 40
#define SCREEN 0xFFED

static char* get_bar();
static char* get_os();
static char* get_host();
static char* get_resolution();
static char* get_cpu();
static char* get_memory();
static char* get_tv_mode();
static char* get_gpu();
static char *get_kernel();

struct conf {
    char *label,
    *(*function)();
} config[] = CONFIG;

