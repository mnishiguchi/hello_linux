// who1.c
// * opens and reads the UTMP file, then shows results.
// * based on sample code in the book Understanding UNIX/LINUX Programming
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST /* inculde remote machine on output */

// displays contents of the utmp struct in human readable form
void show_info(struct utmp *record_p)
{
  printf("%-8.8s", record_p->ut_name);
  printf(" ");
  printf("%-8.8s", record_p->ut_line);
  printf(" ");
  printf("%10ld", record_p->ut_time);
  printf(" ");
#ifdef SHOWHOST
  printf("%s", record_p->ut_host);
#endif
  printf("\n");
}

int main()
{
  struct utmp current_record;
  int utmp_fd;
  int record_len = sizeof(current_record);

  utmp_fd = open(_PATH_UTMP, O_RDONLY);

  if (-1 == utmp_fd)
  {
    perror(_PATH_UTMP);
    exit(1);
  }

  while (record_len == read(utmp_fd, &current_record, record_len))
  {
    show_info(&current_record);
  }

  close(utmp_fd);

  return 0;
}
