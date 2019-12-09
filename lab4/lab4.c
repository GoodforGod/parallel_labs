#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <omp.h>

void generate_m1(double *m1, int max, int A, unsigned int *cycle)
{
    int i;

    #pragma omp parallel for default(none) private(i) shared(m1, max, A, cycle) ordered schedule(dynamic)
    for(i=0;i<max;i++)
    {
        int random;
        #pragma omp ordered
        {
            random = rand_r(cycle);
        }
        double rand = ((double)random / RAND_MAX) * A + 1;
//        printf("\nRandom: %d, Rand M1: %f", random, rand);
        m1[i] = rand;
    }

//    printf("\nArray M1 filled.");
}

void generate_m2(double *m2, int max, int A, unsigned int *cycle)
{
    int i;

    #pragma omp parallel for default(none) private(i) shared(m2, max, A, cycle) ordered schedule(dynamic)
    for(i=0;i<max;i++)
    {
        int random;
        #pragma omp ordered
        {
            random = rand_r(cycle);
        }
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
    #pragma omp parallel for default(none) private(i) shared(arr, size)
    for(i=0;i<size;i++)
    {
        arr[i] = pow((double)arr[i] / (double)M_PI, 3);
//        printf("\nM1: %d, AFTER POW operation: %f", i, arr[i]);
    }
//    printf("\nPI map operation finished.");
}

// 3
void map_tang_module_operation(double *input, double *res, int size)
{
    int i;
//    for(i=0;i<size;i++)
//        printf("\nM2: %d, BEFORE ADD operation: %f", i, arr[i]);

    #pragma omp parallel for default(none) private(i) shared(input, res, size)
    for(i=size;i>0;i--)
        res[i] = fabs(tan((double) input[i-1] + input[i]));
    res[0] = fabs(tan(input[0]));

//    for(i=0;i<size;i++)
//        printf("\nM2: %d, AFTER ABS TAN operation: %f", i, arr[i]);
//    printf("\nTang module map operation finished.");
}

// 1
void merge_power(double *m1, double *m2, int size)
{
    int i;
    #pragma omp parallel for default(none) private(i) shared(m1, m2, size)
    for(i=0;i<size;i++)
    {
//        printf("\nBefore merge M1: %f, M2: %f", m1[i], m2[i]);
        m2[i] = (double) pow(m1[i], m2[i]);
//        printf("\nM2: %d, AFTER POW MERGE operation: %f", i, m2[i]);
    }

//    printf("\nMerge power finished.");
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(double *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    double L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 5
void sort_grome(double *m2, int from, int to)
{
    int i, tmp;
//    #pragma omp parallel for default(none) private(i, tmp) shared(m2, size)
    for(i=from+1;i<to;)
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

void sort(double *m2, int size)
{
    int l = 0, m = size / 2, r = size;
    #pragma omp parallel default(none) shared(m2, size, l, m, r)
    {
        #pragma omp sections // divides the team into sections
        {
            #pragma omp section
            {
                sort_grome(m2, l, m);
            }
            #pragma omp section
            {
                sort_grome(m2, m, r);
            }
        }
    }

    merge(m2, l, m, r);
}


double get_min(double *m2, int size)
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

double reduce(double *m2, int size)
{
    double sum = 0;
    double min = get_min(m2, size);

    int i;
    #pragma omp parallel for default(none) private(i) shared(m2, size, min) reduction(+:sum)
    for(i=0;i<size;i++)
    {
        long temp = (long) ((long)m2[i] / (long)min);
        if (temp % 2 == 0)
        {
            double value = sin(m2[i]);
            //printf("\nMatch for I: %d with reduced for M2: %f: %f", i, value, m2[i]);
            if(!isnan(value))
            {
                sum += value;
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
	int i,N, A = 300, total = 50;
	struct timeval T1, T2;
	double T_1, T_2, t_delta;
	N = atoi(argv[1]);

	double results[total];

    T_1 = omp_get_wtime();
	gettimeofday(&T1, NULL);

    #pragma omp parallel for default(none) private(i) shared(A, N, total, results)
	for(i=1;i<=total;i++)
	{
        double m1[N], m2[N / 2], m2_init[N / 2];
        unsigned int seed = (unsigned int) i;
        //printf("\nSeed: %d", seed);
		srand(seed);

		// Array init
		generate_m1(m1, N, A, &seed);
		generate_m2(m2_init, N/2, A, &seed);

        // Map
        map_pi_operation(m1, N);
        map_tang_module_operation(m2_init, m2, N/2);

        // Merge
        merge_power(m1, m2, N/2);

        // Sort
        sort(m2, N/2);

        // Reduce
        double reduced = reduce(m2, N/2);

		results[i-1] = reduced;
        //printf("\nReduced number: %f for I: %d and N: %d\n", reduced, i, N);
	}
    T_2 = omp_get_wtime();
	gettimeofday(&T2, NULL);

    printf("\n%10c|%10c|%10c\n", 'R', 'I', 'N');
	for(i=0;i<total;i++)
        printf("%10f|%10d|%10d\n", results[i], i, N);

	t_delta = (T_2 - T_1) * 1000;

	printf("\nN=%d. Millie's passed: %ld\n", N, (long) t_delta);
	return 0;
}
