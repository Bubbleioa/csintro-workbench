#include "hacking.h"

// put your globals here
char *pname;
int pid;

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Usage: hacking <process name>\n");
        return 0;
    }
    char buf[32];
    pname = argv[1];
    pid=init(argv[1]);

    // put your code here
}
