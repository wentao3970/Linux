#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <ctype.h>
#include <stdlib.h>

int main (int argc, char **argv){
  int key = 0;
  char *string = NULL;
  int index;
  int c;

  opterr = 0;

  while ((c = getopt (argc, argv, "s:k:")) != -1)
    switch (c)
      {
      case 's':
        string = optarg;
        break;
      case 'k':
        key = atoi(optarg);
        break;
      case '?':
        if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
  //printf ("string = %s, key = %d\n", string, key);
  syscall(335, string, key);
  return 0;
}
