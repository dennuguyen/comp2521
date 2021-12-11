// unsort.c ... make a sequence of numbers not sorted
// Usage: unsort [FileName]
// If no file name supplied, unsorts stdin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

static int rand_int(int n)
{
	srand(time(NULL));
	int limit = RAND_MAX - RAND_MAX % n;
	int rnd;

	do
	{
		rnd = rand();
	} while (rnd >= limit);
	return rnd % n;
}

void shuffle(int *array, int n)
{
	int i, j, tmp;

	for (i = n - 1; i > 0; i--)
	{
		j = rand_int(i + 1);
		tmp = array[j];
		array[j] = array[i];
		array[i] = tmp;
	}
}

void read_array(int *array, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d\n", array[i]);
}

int main(int argc, char *argv[])
{
	FILE *in;

	if (argc == 1)
		in = stdin;
	else if ((in = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Can't open file '%s'\n", argv[1]);
		exit(1);
	}

	int array[MAX] = {0};
	int val = 0, i = 0;
	for (; fscanf(in, "%d", &val) != EOF && i < MAX; i++)
		array[i] = val;
	int n = i + 1;
	shuffle(array, 10);
	read_array(array, 10);

	return 0;
}
