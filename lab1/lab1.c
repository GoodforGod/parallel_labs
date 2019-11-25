#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int i,N, A = 300;
	struct timeval T1, T2;
	long delta_ms;
	N = atoi(argv[1]);
	gettimeofday(&T1, NULL);

	double m1[N], m2[N / 2];

	for(i=0;i<50;i++)
	{
		srand(i);

		// Array init
		generate_m1(m1, N);
		generate_m2(m2, N/2)

        // Map
        map_pi_operation(m1, N);
        map_tang_module_operation(m2, N/2);

        // Merge
        merge_power(m1, m2, N/2);

        // Sort
        sort_grome(m2, N/2);

        // Reduce
        double reduced = reduce(m2, N/2);

        printf("\nReduced number - %ld for I - %d and N - %d", reduced, i, N);
	}

	gettimeofday(&T2, NULL);
	delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
	printf("\nN=%d. Millie's passed: %ld", N, delta_ms);
	return 0;
}

void generate_m1(double *m1, int max)
{
    for(i=0;i<max;i++)
    {
        unsigned int seed = time(NULL) ^ getpid() ^ pthread_self();
        double rand = ((double)rand_r(&m1seed) / RAND_MAX) * A + 1;
        m1[i] = rand;
    }

    printf("\nArray M1 filled.");
}

void generate_m2(double[] *m2, int max)
{
    for(i=0;i<max;i++)
    {
        unsigned int seed = time(NULL) ^ getpid() ^ pthread_self();
        double rand = ((double)rand_r(&m2seed) / RAND_MAX) * 10 + A;
        m2[i] = rand;
    }

    printf("\nArray M2 filled.");
}

// 5
double map_pi_operation(double *arr, int size)
{
    for(i=0;i<size;i++)
    {
        arr[i] = pow(arr[i] / M_PI, 3)
    }
    printf("\nPI map operation finished.");
}

// 3
double map_tang_module_operation(double *arr, int size)
{
    int prev = 0
    for(i=1;i<size;i++)
    {
        arr[i] = fabs(tan(arr[i-1] + arr[i]))
    }
    printf("\nTang module map operation finished.");
}

// 1
void merge_power(double *m1, double *m2, int size)
{
    for(i=0;i<size;i++)
    {
        m2[i] = pow(m1[i], m2[i])
    }

    printf("\nMerge power finished.");
}

// 5
void sort_grome(double *m2, int size)
{
    int i, tmp;
    for(i=1;i<size;)
    {
        if(array[i-1] <= array[i])
        {
            ++i;
        }
        else
        {
            tmp = array[i];
            array[i] = array[i-1];
            array[i-1] = tmp;
            --i;

            if(i == 0)
            {
                i = 1;
            }
        }
    }
    printf("\nArray sorted.");
}

double reduce(double *m2, int size)
{
    double min = find_min(m2, size)
    double sum = 0;

    for(i=0;i<size;i++)
    {
        int temp = (int) (m2[i] / min);
        if (n%2 == 0)
        {
            sum = sin(m2[i]);
        }
    }

    printf("\nArray reduced.");

    return sum;
}

double find_min(double *m2, int size) {
    double min = m2[0];

    for(i=1;i<size;i++)
    {
        if (m2[i] < min && m2[i] != 0)
        {
              min = m2[i];
        }
    }

    return min;
}
