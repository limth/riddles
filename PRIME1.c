#include "stdio.h"
#include "stdlib.h"
#include "math.h"

const int MAX_NUM = 1000000000;

int max_factor;

void calculate_max_factor(int *result)
{
    *result = ceil(sqrt(MAX_NUM));
}

void initiate_sieve(int *sieve, int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        if(i == 0 || i == 1)
        {
            *sieve = -1;
        }
        else
        {
            *sieve = i;
        }

        sieve++;
    }
}

void initiate_secondary_sieve(int *sieve, int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        *sieve = 1;
        sieve++;
    }
}

void filter_sieve(int sieve[], int *primes, int *primes_count, int len)
{
    int i;
    int checked_num;

    for(i = 0; i < len; i++)
    {
        if(sieve[i] == -1)
        {
            continue;
        }

        *primes = sieve[i];
        primes++;
        (*primes_count)++;

        int multiplier = 2;
        while(multiplier * i < len)
        {
            checked_num = sieve[multiplier * i];
            sieve[multiplier * i] = -1;
            multiplier++;
        }
    }
}

void find_in_primary_sieve(
        int intersect,
        int intersect_end,
        int *primes,
        int *found_primes)
{
    int i;
    int **sentinel = &primes;

    if(intersect <= 1)
    {
        intersect = 2;
    }

    for(i = intersect; i <= intersect_end; i++)
    {
        primes = *sentinel;
        while(*primes <= i)
        {
            if(*primes == i)
            {
                printf("%d\n", i);
                sentinel = &primes;
                (*found_primes)++;
            }

            primes++;
        }
    }
}

void primality_test(
        int start,
        int end,
        int *primes,
        int len,
        int *found_primes)
{
    int range = end - start + 1;
    int test[range];

    initiate_secondary_sieve(test, range);
    
    int i;
    for(i = 0; i < len; i++)
    {
        int currently_tested = start;
        int remainder = start % *primes;
        int addition = 0;

        if(remainder)
        {
            addition = *primes - remainder;
            currently_tested += addition;
        }

        while(currently_tested <= end)
        {
            int index = currently_tested - start;

            test[index] = 0;
            currently_tested += *primes;
        }

        primes++;
    }

    int j;
    for(j = 0; j < range; j++)
    {
        if(test[j])
        {
            printf("%d\n", j + start);
            (*found_primes)++;
        }
    }
}

int main()
{
    int test_num;
    int n;
    int primes_count = 0;

    calculate_max_factor(&max_factor);

    int sieve[max_factor];
    int primes[max_factor];

    initiate_sieve(sieve, max_factor);

    filter_sieve(sieve, primes, &primes_count, max_factor);

    scanf("%d", &test_num);

    int cases[test_num * 2];

    int k;
    for(k = 0; k < test_num * 2; k+=2)
    {
        int interval_start, interval_end;

        scanf("%d %d", &interval_start, &interval_end);
        cases[k] = interval_start;
        cases[k + 1] = interval_end;
    }

    int j;
    for(j = 0; j < test_num * 2; j+=2)
    {
        int interval_start = cases[j];
        int interval_end = cases[j + 1];
        int found_primes = 0;

        if(interval_start < max_factor)
        {
            int intersect_end = interval_end;

            if(interval_end > max_factor)
                intersect_end = max_factor;

            find_in_primary_sieve(interval_start, intersect_end, primes, &found_primes);
            if(interval_end > max_factor)
            {
                primality_test(max_factor, interval_end, primes, primes_count, &found_primes);
            }
        }

        if(interval_start >= max_factor)
        {
            primality_test(interval_start, interval_end, primes, primes_count, &found_primes);
        }

        if(found_primes == 0)
            printf("\n");

        printf("\n");
    }

    return 0;
}

