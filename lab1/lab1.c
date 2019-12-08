#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

void generate_m1(double *m1, int max, int A, unsigned int *cycle)
{
    int i;
    for(i=0;i<max;i++)
    {
        int random = rand_r(cycle);
        double rand = ((double)random / RAND_MAX) * A + 1;
        //printf("\nRandom: %d, Rand M1: %f", random, rand);
        m1[i] = rand;
    }

    //printf("\nArray M1 filled.");
}

void generate_m2(double *m2, int max, int A, unsigned int *cycle)
{
    int i;
    for(i=0;i<max;i++)
    {
        int random = rand_r(cycle);
        double rand = ((double)random / RAND_MAX) * A * 9 + A;
//        printf("\nRandom: %d, Rand M1: %f", random, rand);
        m2[i] = rand;
    }

//    printf("\nArray M2 filled.");
}

// 5
void map_pi_operation(double *arr, int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        arr[i] = pow((double)arr[i] / (double)M_PI, 3);
//        printf("\nM1: %d, AFTER POW operation: %f", i, arr[i]);
    }
//    printf("\nPI map operation finished.");
}

// 3
void map_tang_module_operation(double *arr, int size)
{
    int i;
//    for(i=0;i<size;i++)
//        printf("\nM2: %d, BEFORE ADD operation: %f", i, arr[i]);

    for(i=size;i>0;i--)
        arr[i] = fabs(tan((double) arr[i-1] + arr[i]));
    arr[0] = fabs(tan(arr[0]));

//    for(i=0;i<size;i++)
//        printf("\nM2: %d, AFTER ABS TAN operation: %f", i, arr[i]);
//    printf("\nTang module map operation finished.");
}

// 1
void merge_power(double *m1, double *m2, int size)
{
    int i;
    for(i=0;i<size;i++)
    {
//        printf("\nBefore merge M1: %f, M2: %f", m1[i], m2[i]);
        m2[i] = (double) pow(m1[i], m2[i]);
//        printf("\nM2: %d, AFTER POW MERGE operation: %f", i, m2[i]);
    }

//    printf("\nMerge power finished.");
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

//    printf("\nArray sorted with first elem: %f and last: %f", m2[0], m2[size-1]);
}

//double find_min(double *m2, int size) {
//    double min = m2[0];
//
//    int i;
//    for(i=1;i<size;i++)
//    {
//        if(min == 0 && m2[i] != 0)
//        {
//            min = m2[i];
//        }
//
//        if (m2[i] < min && m2[i] != 0)
//        {
//              min = m2[i];
//        }
//    }
//
//    printf("\nMin number: %f", min);
//
//    return min;
//}

double reduce(double *m2, int size)
{
    double min = m2[0];
    double sum = 0;

    int i;
    for(i=0;i<size;i++)
    {
        long temp = (long) ((long)m2[i] / (long)min);
        if (temp % 2 == 0)
        {
            double value = sin(m2[i]);
            //printf("\nMatch for I: %d with reduced for M2: %f: %f", i, value, m2[i]);
            if(!isnan(value))
            {
                sum += (double) value;
//                printf("\nTemp reduced sum: %f", sum);
            }
//            else
//            {
//                printf("\nValue is invalid: %f", value);
//            }
        }
    }

    //printf("\nArray reduced with value: %f", sum);

    return sum;
}

int main(int argc, char *argv[])
{
	int i,N, A = 300, total = 5;
	struct timeval T1, T2;
	long delta_ms;
	N = atoi(argv[1]);
	gettimeofday(&T1, NULL);

	double results[total];

	for(i=1;i<=total;i++)
	{
        double m1[N], m2[N / 2];
        unsigned int seed = (unsigned int) i;
        //printf("\nSeed: %d", seed);
		srand(seed);

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
	
    printf("\n%10c|%10c|%10c\n", 'R', 'I', 'N');
	for(i=0;i<total;i++)
        printf("%10f|%10d|%10d\n", results[i], i, N);

	gettimeofday(&T2, NULL);
	delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
	printf("\nN=%d. Millie's passed: %ld\n", N, delta_ms);
	return 0;
}
