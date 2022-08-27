#include "hacking.h"

typedef struct mem_t
{
    uint64_t start_addr;
    uint64_t ch_start_addr;
    uintptr_t size;
    unsigned char *mem;

} mem_t;
static mem_t mem_range[1024];
static signed mem_count = 0;
static uint64_t total_size = 0;
static char *pname;
static int n, fd, pid;

unsigned char *fetch_mem(uint64_t ch_addr, int length, int *read_btyes, bool is_first_scan)
{
    // read_btyes shows how many bytes have been read successfully
    // view memory as a chain
    // v_addr is the virtual address of the process
    // binary search for suitable position
    int l = 0, r = mem_count;
    while (l + 1 < r)
    {
        int mid = (l + r) >> 1;
        if (mem_range[mid].ch_start_addr <= ch_addr)
            l = mid;
        else
            r = mid;
    }
    int pos = l;
    if (is_first_scan)
    {
        // first scan
        *read_btyes = mem_range[pos].size - (ch_addr - mem_range[pos].ch_start_addr);
        return mem_range[pos].mem + (ch_addr - mem_range[pos].ch_start_addr);
    }
    unsigned char *ch = (unsigned char *)malloc(length);
    assert(lseek(fd, ch_addr - mem_range[pos].ch_start_addr + mem_range[pos].start_addr, SEEK_SET) != (off_t)-1);
    *read_btyes = read(fd, ch, length);
    return ch;
    assert(false && "No such address!");
}

void write_mem(uint64_t ch_addr, unsigned char *ch, int length)
{
    uint64_t v_addr = ch_addr;
    for (int i = 0; i < mem_count; i++)
    {
        if (mem_range[i].size > v_addr)
        {
            assert(lseek(fd, v_addr + mem_range[i].start_addr, SEEK_SET) != (off_t)-1);
            write(fd, ch, length);
            return;
        }
        else
        {
            v_addr -= mem_range[i].size;
        }
    }
    assert(false && "No such address!");
}

int init_scan()
{
    // record memory range
    uintptr_t start, kb;
    total_size = 0;
    n = 0;
    mem_count=0;
    char perm[16];
    char description[32];
    char command[128];
    sprintf(command, "pmap -x %d | tail -n +3", pid);
    FILE *fp = popen(command, "r");
    assert(fp);

    while (fscanf(fp, "%lx", &start) == 1 && (intptr_t)start > 0)
    {
        assert(fscanf(fp, "%ld%*ld%*ld%s%[^\n]s", &kb, perm, description) >= 1);
        if (perm[1] != 'w' || perm[2] == 'x' || strcmp(description + 1, pname) != 0 && strcmp(description + 1, "  [ stack ]") != 0 && strcmp(description + 1, "  [ anon ]") != 0)
            continue;

        uintptr_t size = kb * 1024;
        mem_range[mem_count].ch_start_addr = total_size;
        total_size += size;
        mem_range[mem_count].start_addr = start;
        mem_range[mem_count++].size = size;
        mem_range[mem_count - 1].mem = malloc(size);
        assert(lseek(fd, start, SEEK_SET) != (off_t)-1);
        assert(read(fd, mem_range[mem_count - 1].mem, size) == size);
    }
    return total_size;
}

int init(char *process_name)
{
    // initialize for pid and pd
    pname=process_name;
    char buf[32];
    char command[128];
    setbuf(stdout, NULL);
    sprintf(command, "pidof '%s'", pname);
    FILE *fp = popen(command, "r");
    assert(fscanf(fp, "%d", &pid) == 1);
    pclose(fp);
    sprintf(buf, "/proc/%d/mem", pid);
    fd = open(buf, O_RDWR);
    assert(fd > 0);
    return pid;
}