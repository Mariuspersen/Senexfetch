#include "main.h"
#include <stdio.h>

int main(void) {
    size_t i;
    char* value;
    char* label;
    for (i = 0; i < sizeof(config) / sizeof(config[0]); i++) {
        value = config[i].function();
        label = config[i].label;

        printf("%s%s\n",label,value);
        free(value);
    }
    return 0;
}

static char *get_bar() {
  size_t i;
  char *bar = calloc(BUF_SIZE, sizeof(char));
  char *host = get_host();
  size_t length = strlen(host);
  free(host);
  for (i = 0; i < length; i++) {
    bar[i] = '-';
  }
  bar[i] = '\n';
  return bar;
}

static char *get_cpu() {
  unsigned char cpu = getcpu();
  char *cpu_string = malloc(BUF_SIZE);

  if (cpu == CPU_6502) {
    snprintf(cpu_string, BUF_SIZE, "6502");
  } else if (cpu == CPU_65C02) {
    snprintf(cpu_string, BUF_SIZE, "65C02");
  } else if (cpu == CPU_65816) {
    snprintf(cpu_string, BUF_SIZE, "65816");
  } else if (cpu == CPU_4510) {
    snprintf(cpu_string, BUF_SIZE, "4510");
  } else if (cpu == CPU_65SC02) {
    snprintf(cpu_string, BUF_SIZE, "65SC02");
  } else if (cpu == CPU_65CE02) {
    snprintf(cpu_string, BUF_SIZE, "65CE02");
  } else if (cpu == CPU_HUC6280) {
    snprintf(cpu_string, BUF_SIZE, "HUC6280");
  } else if (cpu == CPU_2A0x) {
    snprintf(cpu_string, BUF_SIZE, "2A0x");
  } else if (cpu == CPU_45GS02) {
    snprintf(cpu_string, BUF_SIZE, "45GS02");
  } else {
    snprintf(cpu_string, BUF_SIZE, "Unknown");
  }

  return cpu_string;
}

static char *get_os() {
  struct utsname info = {};
  char *info_string = malloc(BUF_SIZE);
  (void)uname(&info);
  if (strcmp(info_string, "cc65")) {
    snprintf(info_string, BUF_SIZE, "unknown");
  } else {
    snprintf(info_string, BUF_SIZE, "%s", info.machine);
  }
  return info_string;
}

static char *get_host() {
  struct utsname info = {};
  char *info_string = malloc(BUF_SIZE);
  (void)uname(&info);
  snprintf(info_string, BUF_SIZE, "%s", info.machine);
  return info_string;
}

static char *get_memory() {
  char *memory = malloc(BUF_SIZE);
  unsigned short banks = get_numbanks();
  snprintf(memory, BUF_SIZE, "%d KiB", banks * 8);
  return memory;
}

static char *get_tv_mode() {
  unsigned char tv = get_tv();
  char *tv_buf = malloc(BUF_SIZE);
  switch (tv) {
  case TV_NONE: {
    snprintf(tv_buf, BUF_SIZE, "NONE");
    break;
  }
  case TV_VGA: {
    snprintf(tv_buf, BUF_SIZE, "VGA");
    break;
  }
  case TV_NTSC_COLOR: {
    snprintf(tv_buf, BUF_SIZE, "NTSC_COLOR");
    break;
  }
  case TV_RGB: {
    snprintf(tv_buf, BUF_SIZE, "RGB");
    break;
  }
  case TV_NONE2: {
    snprintf(tv_buf, BUF_SIZE, "NONE2");
    break;
  }
  case TV_VGA2: {
    snprintf(tv_buf, BUF_SIZE, "VGA2");
    break;
  }
  case TV_NTSC_MONO: {
    snprintf(tv_buf, BUF_SIZE, "NTSC_MONO");
    break;
  }
  case TV_RGB2: {
    snprintf(tv_buf, BUF_SIZE, "RGB2");
    break;
  }
  }
  return tv_buf;
}

static char *get_kernel() {
    struct utsname info = {};
    volatile char version = (*(volatile char*)0xff80);
    char* kernel = malloc(BUF_SIZE);
    (void)uname(&info);
    if (version == (char)-1) {
        snprintf(kernel, BUF_SIZE, "%s KERNEL Custom",info.machine);
    }
    else if (version < 0) {
        snprintf(kernel, BUF_SIZE, "%s KERNEL Prelease V%d",info.machine,version - 0x100 - 2);
    }
    else {
        snprintf(kernel, BUF_SIZE, "%s KERNEL Release V%d",info.machine,version);
    }
    return kernel;
}

static char* get_resolution() {
    char* resolution = malloc(BUF_SIZE);
    char row;
    char col;
    __asm__("jsr %w", SCREEN);
    __asm__("ldy #%o", row);
    __asm__("txa");
    __asm__("sta (sp),y");
    __asm__("jsr %w", SCREEN);
    __asm__("tya");
    __asm__("ldy #%o", col);
    __asm__("sta (sp),y");     
    snprintf(resolution, BUF_SIZE, "%dx%d",row*8,col*8);
    return resolution;
}

