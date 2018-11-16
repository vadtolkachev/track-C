#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>

int main()
{
	FILE *file = fopen("2.txt", "r");
	if(errno != 0)
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	FILE *res = fopen("res.txt", "w");
	if(errno != 0)
	{
		fprintf(stderr, "failed to open res\n");
		exit(EXIT_FAILURE);
	}


	const int size = 5;
	char str[size];
	memset(str, 0, size + 1);
	int rs = fread(str, 1, size, file);
	if((rs < 1) || (errno != 0))
	{
		printf("read error\n");
		exit(EXIT_FAILURE);
	}

	printf("%s\n", str);
	printf("len = %ld\n", strlen(str));
	int ir = fwrite(str, size, 1, res);
	if((ir <= 0) || (errno != 0))
	{
		printf("write error\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}