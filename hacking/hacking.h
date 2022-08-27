#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

extern unsigned char *fetch_mem(uint64_t ch_addr, int length, int *read_btyes, bool is_first_scan);

extern void write_mem(uint64_t ch_addr, unsigned char *ch, int length);

int init_scan();

int init(char *process_name);