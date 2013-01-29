#include <stdio.h>
#include <stddef.h>
#include <string.h>
int main(void)
  {
	char str[] = "c++";
	char *pstart = str;
	char *pend = str + strlen(str);
	ptrdiff_t difp = pend - pstart;
	printf("%d\n", sizeof(str));
	return 0;
  }