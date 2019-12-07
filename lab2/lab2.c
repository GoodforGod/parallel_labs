#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include "framewave/fwSignal.h"

void generate_m1(Fw64f *m1, int max, int A, unsigned int *cycle)
{
    int i;
    for(i=0;i<max;i++)
    {
        int random = rand_r(cycle);
        Fw64f rand = ((Fw64f)random / RAND_MAX) * A + 1;
        //printf("\nRandom: %d, Rand M1: %Lf", random, rand);
        m1[i] = rand;
    }

    //printf("\nArray M1 filled.");
}

void generate_m2(Fw64f *m2, int max, int A, unsigned int *cycle)
{
    int i;
    for(i=0;i<max;i++)
    {
        int random = rand_r(cycle);
        Fw64f rand = ((Fw64f)random / RAND_MAX) * A * 9 + A;
        //printf("\nRandom: %d, Rand M1: %Lf", random, rand);
        m2[i] = rand;
    }

    //printf("\nArray M2 filled.");
}

// 5
//void map_pi_operation(Fw64f *arr, int size)
//{
//    int i;
//    for(i=0;i<size;i++)
//    {
//        Fw64f* res = NULL;
//        const Fw64f arg1 = (Fw64f) arr[i];
//        const Fw64f arg2 = 3;
//        fwsPow_64f_A50(&arg1, &arg2, res, 1);
//        arr[i] = pow((Fw64f)arr[i] / (Fw64f)M_PI, 3);
//    }
//    //printf("\nPI map operation finished.");
//}


// 5
void map_pi_operation_amd(Fw64f *arr, Fw64f *divArg, Fw64f *powArg, int size)
{
//    int i;
//    for(i=0;i<size;i++)
//    {
//        printf("\nM1: %d, BEFORE map pi operation: %f", i, arr[i]);
//    }

    fwsDiv_64f_A50(arr, divArg, arr, size);
//    for(i=0;i<size;i++)
//    {
//        printf("\nM1: %d, AFTER DIV operation: %f", i, arr[i]);
//    }

    fwsPow_64f_A50(arr, powArg, arr, size);
//    for(i=0;i<size;i++)
//        printf("\nM1: %d, AFTER POW operation: %f", i, arr[i]);
}

// 3
void map_tang_module_operation(Fw64f *arr, Fw64f* shiftArr, int size)
{
    arr[0] = fabs(tan(arr[0]));
    int i;
    for(i=1;i<size;i++)
    {
        arr[i] = fabs((Fw64f)tan((Fw64f)arr[i-1] + arr[i]));
    }
    //printf("\nTang module map operation finished.");
}

// 1
void merge_power(Fw64f *m1, Fw64f *m2, int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        //printf("\nBefore merge M1: %Lf, M2: %Lf", m1[i], m2[i]);
        m2[i] = (Fw64f) pow(m1[i], m2[i]);
        //printf("\nAfter merge M2: %Lf", m2[i]);
    }

    //printf("\nMerge power finished.");
}

// 5
void sort_grome(Fw64f *m2, int size)
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

double find_min(Fw64f *m2, int size) {
    Fw64f min = m2[0];

    int i;
    for(i=1;i<size;i++)
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

Fw64f reduce(Fw64f *m2, int size)
{
    Fw64f min = find_min(m2, size);
    Fw64f sum = 0;

    int i;
    for(i=0;i<size;i++)
    {
        long temp = ((long)m2[i] / (long)min);
        if (temp % 2 == 0)
        {
            Fw64f value = sin(m2[i]);
//            printf("\nMatch for I: %d with reduced for M2: %f: %f", i, value, m2[i]);
            if(!isnan(value))
            {
                sum += (Fw64f) value;
//                printf("\nREDUCED SUM: %f", sum);
            }
//            else
//            {
//                printf("\nValue is invalid: %f", value);
//            }
        }
//        else
//        {
//            printf("\nDivide value is NOT EVEN for M2: %ld and MIN: %ld", (long) m2[i], (long) min);
//        }
    }

    //printf("\nArray reduced with value: %Lf", sum);

    return sum;
}

int main(int argc, char *argv[])
{
	int i,N,j, A = 300, total = 5;
	struct timeval T1, T2;
	long delta_ms;
	N = atoi(argv[1]);
    int halfN = N/2;
	gettimeofday(&T1, NULL);

	Fw64f results[total];

    // MAP pi operation
    Fw64f* mapDivArg = malloc(N * sizeof(Fw64f));
    Fw64f* mapPowArg = malloc(N * sizeof(Fw64f));
    for(i=0;i<N;i++)
    {
        mapDivArg[i] = M_PI;
        mapPowArg[i] = 3;
    }

    // MAP tang operation
    Fw64f* mapIncArr = malloc(N / 2 * sizeof(Fw64f));

	for(i=1;i<=total;i++)
	{
        Fw64f m1[N], m2[halfN];
        unsigned int seed = (unsigned int) i;
        //printf("\nSeed: %d", seed);
		srand(seed);

		// Array init
		generate_m1(m1, N, A, &seed);
		generate_m2(m2, halfN, A, &seed);

        // Map
        map_pi_operation_amd(m1, mapDivArg, mapPowArg, N);

        for(j=1;j<halfN;j++)
            mapIncArr[j] = m2[j - 1];
//        for(j=0;j<halfN;j++)
//        {
//            printf("\nM2 origin: %f", m2[j]);
//        }
//        for(j=0;j<halfN;j++)
//        {
//            printf("\nM2 shifted: %f", mapIncArr[j]);
//        }

        //mapIncArr = memcpy(&mapIncArr[1], &m2[1], (halfN - 1) * sizeof(Fw64f));
        map_tang_module_operation(m2, mapIncArr, N/2);

        // Merge
        merge_power(m1, m2, N/2);

        // Sort
        sort_grome(m2, N/2);

        // Reduce
        Fw64f reduced = reduce(m2, N/2);

		results[i-1] = reduced;
        //printf("\nReduced number: %f for I: %d and N: %d\n", reduced, i, N);
	}
	
    printf("\n%10c|%10c|%10c\n", 'R', 'I', 'N');
	for(i=0;i<total;i++)
	{
        printf("%10f|%10d|%10d\n", results[i], i, N);
	}

	gettimeofday(&T2, NULL);
	delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
	printf("\nN=%d. Millie's passed: %ld\n", N, delta_ms);
	return 0;
}
