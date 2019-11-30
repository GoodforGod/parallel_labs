#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

void generate_m1(double *m1, int max, int A, unsigned int *cycle)
{
    for(int i=0;i<max;i++)
    {
        double rand = ((double)rand_r(cycle) / RAND_MAX) * A + 1;
        //printf("\nRand M1: %f", rand);
        m1[i] = rand;
    }

    //printf("\nArray M1 filled.");
}

void generate_m2(double *m2, int max, int A, unsigned int *cycle)
{
    for(int i=0;i<max;i++)
    {
        double rand = ((double)rand_r(cycle) / RAND_MAX) * A * 9 + A;
        //printf("\nRand M2: %f", rand);
        m2[i] = rand;
    }

    //printf("\nArray M2 filled.");
}

// 5
void map_pi_operation(double *arr, int size)
{
    for(int i=0;i<size;i++)
    {
        arr[i] = pow(((double)arr[i] / M_PI), 3);
    }
    //printf("\nPI map operation finished.");
}

// 3
void map_tang_module_operation(double *arr, int size)
{
    arr[0] = fabs(tan(arr[0]));
    for(int i=1;i<size;i++)
    {
        arr[i] = fabs(tan(arr[i-1] + arr[i]));
    }
    //printf("\nTang module map operation finished.");
}

// 1
void merge_power(double *m1, double *m2, int size)
{
    for(int i=0;i<size;i++)
    {
        m2[i] = pow(m1[i], m2[i]);
    }

    //printf("\nMerge power finished.");
}

// 5
void sort_grome(double *m2, int size)
{
    int i, tmp;
    for(i=1;i<size;)
    {
        if(m2[i-1] <= m2[i])
        {
            ++i;
        }
        else
        {
            tmp = m2[i];
            m2[i] = m2[i-1];
            m2[i-1] = tmp;
            --i;

            if(i == 0)
            {
                i = 1;
            }
        }
    }

    //printf("\nArray sorted with first elem: %f and last: %f", m2[0], m2[size-1]);
}

double find_min(double *m2, int size) {
    double min = m2[0];

    for(int i=1;i<size;i++)
    {
        if(min == 0 && m2[i] != 0)
        {
            min = m2[i];
        }

        if (m2[i] < min && m2[i] != 0)
        {
              min = m2[i];
        }
    }

    //printf("\nMin number: %f", min);

    return min;
}

double reduce(double *m2, int size)
{
    double min = find_min(m2, size);
    double sum = 0;

    for(int i=0;i<size;i++)
    {
        int temp = (int) (m2[i] / min);
        if (temp%2 == 0)
        {
            sum += sin(m2[i]);
            //printf("\nMatch for %d.", temp);
        }
    }

    //printf("\nArray reduced.");

    return sum;
}

int main(int argc, char *argv[])
{
	int i,N, A = 300;
	struct timeval T1, T2;
	long delta_ms;
	N = atoi(argv[1]);
	gettimeofday(&T1, NULL);

	double results[50];

	for(i=1;i<=50;i++)
	{
		srand(i);
        double m1[N], m2[N / 2];
        unsigned int seed = i;

		// Array init
		generate_m1(m1, N, A, &seed);
		generate_m2(m2, N/2, A, &seed);

        // Map
        map_pi_operation(m1, N);
        map_tang_module_operation(m2, N/2);

        // Merge
        merge_power(m1, m2, N/2);

        // Sort
        sort_grome(m2, N/2);

        // Reduce
        double reduced = reduce(m2, N/2);

		results[i-1] = reduced;
        //printf("\nReduced number: %f for I: %d and N: %d\n", reduced, i, N);
	}
	
    printf("R\t|\tI\t|\tN\n");
	for(i=0;i<50;i++)
	{
        printf("%10f|%10d|%10d\n", results[i], i, N);
	}

	gettimeofday(&T2, NULL);
	delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
	printf("\nN=%d. Millie's passed: %ld\n", N, delta_ms);
	return 0;
}
