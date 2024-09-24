#include "main.h"

int main(void) {
    char* bar = get_bar();
    char* memory = get_memory();
    char* host = get_host();
    char* os = get_os();
    char* cpu = get_cpu();
    printf("%s%s%s%s%s%s",bar,host,cpu,memory,os,bar);
    free(bar);
    free(memory);
    free(host);
    free(os);
    free(cpu);
    return 0;
}

static char* get_bar() {
    size_t i;
    char* bar = calloc(BUF_SIZE,sizeof(char));
    char* host = get_host();
    size_t length = strlen(host);
    free(host);
    for (i = 0; i < length; i++) {
        bar[i] = '-';
    }
    bar[i] = '\n';
    return bar;
}

static char* get_cpu() {
    unsigned char cpu = getcpu();
    char* cpu_string = malloc(BUF_SIZE);

    if(cpu == CPU_6502) {
        snprintf(cpu_string,BUF_SIZE,"CPU: 6502\n");
    }
    else if(cpu == CPU_65C02) {
        snprintf(cpu_string,BUF_SIZE,"CPU: 65C02\n");
    }
    else if(cpu == CPU_65816) {
        snprintf(cpu_string,BUF_SIZE,"CPU: 65816\n");
    }
    else if(cpu == CPU_4510) {
        snprintf(cpu_string,BUF_SIZE,"CPU: 4510\n");
    }
    else if(cpu == CPU_65SC02) {
        snprintf(cpu_string,BUF_SIZE,"CPU: 65SC02\n");
    }
    else if(cpu == CPU_65CE02) {
        snprintf(cpu_string,BUF_SIZE,"CPU: 65CE02\n");
    }
    else if(cpu == CPU_HUC6280) {
        snprintf(cpu_string,BUF_SIZE,"CPU: HUC6280\n");
    }
    else if(cpu == CPU_2A0x) {
        snprintf(cpu_string,BUF_SIZE,"CPU: 2A0x\n");
    }
    else if(cpu == CPU_45GS02) {
        snprintf(cpu_string,BUF_SIZE,"CPU: 45GS02\n");
    }
    else {
        snprintf(cpu_string,BUF_SIZE,"CPU: Unknown\n");
    }

    return cpu_string;
}

static char* get_os() {
    struct utsname info = {};
    char* info_string = malloc(BUF_SIZE);
    (void)uname(&info);
    if(strcmp(info_string,"cc65")) {
        snprintf(info_string,BUF_SIZE,"OS: Bare-metal\n");
    } else {
        snprintf(info_string,BUF_SIZE,"OS: %s\n",info.machine);
    }
    return info_string;
}

static char* get_host() {
    struct utsname info = {};
    char* info_string = malloc(BUF_SIZE);
    (void)uname(&info);
    snprintf(info_string,BUF_SIZE,"HOST: %s\n",info.machine);
    return info_string;
}

static char* get_memory() {
    char* memory = malloc(BUF_SIZE);
    unsigned short banks = get_numbanks();
    snprintf(memory,BUF_SIZE,"MEMORY BANKS: %d\n",banks);
    return memory;
}