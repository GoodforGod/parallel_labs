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
        //printf("\nRandom: %d, Rand M1: %f", random, rand);
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
//        printf("\nRandom: %d, Rand M1: %f", random, rand);
        m2[i] = rand;
    }

    //printf("\nArray M2 filled.");
}

// 5
void map_pi_operation(Fw64f *arr, int size)
{
//    int i;
//    for(i=0;i<size;i++)
//        printf("\nM1: %d, BEFORE map pi operation: %f", i, arr[i]);

    fwsDivC_64f(arr, (Fw64f) M_PI, arr, size);
//    for(i=0;i<size;i++)
//        printf("\nM1: %d, AFTER DIV operation: %f", i, arr[i]);

    fwsPowx_64f_A50(arr, 3, arr, size);
//    for(i=0;i<size;i++)
//        printf("\nM1: %d, AFTER POW operation: %f", i, arr[i]);
}

// 3
void map_tang_module_operation(Fw64f *arr, Fw64f* shiftArr, int size)
{
//    int i;
//    for(i=0;i<size;i++)
//        printf("\nM2: %d, BEFORE ADD operation: %f", i, arr[i]);

    fwsAdd_64f(arr, shiftArr, arr, size);
//    for(i=0;i<size;i++)
//        printf("\nM2: %d, AFTER ADD operation: %f", i, arr[i]);

    fwsTan_64f_A50(arr, arr, size);
//    for(i=0;i<size;i++)
//        printf("\nM2: %d, AFTER TAN operation: %f", i, arr[i]);

    fwsAbs_64f_I(arr, size);
//    for(i=0;i<size;i++)
//        printf("\nM2: %d, AFTER ABS operation: %f", i, arr[i]);

//    printf("\nTang module map operation finished.");
}

// 1
void merge_power(Fw64f *m1, Fw64f *m2, int size)
{
//    int i;
//    for(i=0;i<size;i++)
//        printf("\nM1: %d, BEFORE POW MERGE operation: %f", i, m1[i]);
//    for(i=0;i<size;i++)
//        printf("\nM2: %d, BEFORE POW MERGE operation: %f", i, m2[i]);

    fwsPow_64f_A50(m1, m2, m2, size);

//    for(i=0;i<size;i++)
//        printf("\nM2: %d, AFTER POW MERGE operation: %f", i, m2[i]);
//    printf("\nMerge power finished.");
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

//    printf("\nArray sorted with first elem: %f and last: %f", m2[0], m2[size-1]);
}

Fw64f get_min(Fw64f *m2, int size)
{
    int i;
//    for(i=0;i<size;i++)
//        printf("\nM2: %d, AT SORT operation: %f", i, m2[i]);

    for(i=0;i<size;i++)
    {
        if(fabs(m2[i]) >= 0.000000000000001)
        {
//            printf("\nFound min: %f", m2[i]);
            return m2[i];
        }
    }


    return m2[0];
}

Fw64f reduce(Fw64f *m2, int size)
{
    Fw64f min = get_min(m2, size);
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
	int i,N,j, A = 300, total = 50, fw_threads = 1;
	struct timeval T1, T2;
	long delta_ms;
	N = atoi(argv[1]);
    int halfN = N/2;

	if(argc > 2)
	    fw_threads = atoi(argv[2]);

    fwSetNumThreads(fw_threads);
    printf("Framewave threads number: %d", fw_threads);

	Fw64f results[total];

    // MAP tang operation
    Fw64f* mapIncArr = malloc(N / 2 * sizeof(Fw64f));

	gettimeofday(&T1, NULL);
	for(i=1;i<=total;i++)
	{
        Fw64f m1[N], m2[halfN];
        unsigned int seed = (unsigned int) i;
        //printf("\nSeed: %d", seed);
		srand(seed);

		// Array init
		generate_m1(m1, N, A, &seed);
		generate_m2(m2, halfN, A, &seed);

        // Map M1
        map_pi_operation(m1, N);

        for(j=1;j<halfN;j++)
            mapIncArr[j] = m2[j - 1];
//        for(j=0;j<halfN;j++)
//            printf("\nM2 origin: %f", m2[j]);
//        for(j=0;j<halfN;j++)
//            printf("\nM2 shifted: %f", mapIncArr[j]);

        // Map M2
        //mapIncArr = memcpy(&mapIncArr[1], &m2[1], (halfN - 1) * sizeof(Fw64f));
        map_tang_module_operation(m2, mapIncArr, halfN);

        // Merge
        merge_power(m1, m2, halfN);

        // Sort
        sort_grome(m2, halfN);

        // Reduce
        Fw64f reduced = reduce(m2, halfN);

		results[i-1] = reduced;
        //printf("\nReduced number: %f for I: %d and N: %d\n", reduced, i, N);
	}
	gettimeofday(&T2, NULL);

    printf("\n%10c|%10c|%10c\n", 'R', 'I', 'N');
	for(i=0;i<total;i++)
        printf("%10f|%10d|%10d\n", results[i], i, N);

	delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
	printf("\nN=%d. Millie's passed: %ld\n", N, delta_ms);
	return 0;
}
