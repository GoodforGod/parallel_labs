#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
	int i,N;
	struct timeval T1, T2;
	long delta_ms;
	N = atoi(argv[1]);
	gettimeofday(&T1, NULL);

	double m1[N], m2[N / 2];

	for(i=0;i<50;i++)
	{
		// Array init
		double half = N / 2;
		for(i=0;i<N;i++)
		{
			if(i <= half)
			{

			}


		}
		srand(i);

	}

	gettimeofday(&T2, NULL);
	delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
	printf("\nN=%d. Millies passed: %ld\n", N, delta_ms);
	return 0;
}


void generate_m1(double[] *m1)
{

}

void generate_m2(double[] *m2)
{

}

// 5
double map_pi_operation(double *elem)
{

}

// 3
double tang_module(double *elem)
{

}

// 1
void merge_power(double[] *m1, double[] *m2)
{

}

// 5
void sort_grome(double[] *m2)
{

}

double reduce(double[] *m2)
{

}
