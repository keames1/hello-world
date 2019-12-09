// can compute all the primes up to 0x3FE977 (4_188_535). Largest prime 4_188_533

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main ()
{
    int max;
    printf("Please enter the maximum number up to which you would like to see all primes listed: "
      );   scanf("%i", &max);

    // The algorithm proper doesn't print 2.
    printf("All prime numbers in the range 0 to %i:\nPrime number: 2\n", max);


    bool isComposite;
    // primesSoFar is a memory hog. It'd be nice to reduce its size in proportion to max. The frequency
    // of primes diminishes at higher numerical ranges. A formula for calculating the number of primes for
    // a given numerical range would be nice. Sadly, it's not linear.
    int PRIMES_MAX_SIZE = (max >> 1) + 1;
    int primesSoFar[PRIMES_MAX_SIZE];
    primesSoFar[0] = 2;
    int nextIdx = 1;
    int startConsecCount = 0;

    for (int i = 2; i <= max; i++)
    {
        isComposite = false; // Assume the current number isn't composite.
        for (int k = 2; k <= (int)sqrt(i) + 1; k++)
        {
            if (k - 2 < nextIdx) // Check it against all primes found so far.
            {
                if (i % primesSoFar[k - 2] == 0)
                {
                    // If i is divisible by a previous prime number, break.
                    isComposite = true;
                    break;
                }else
                {
                    // Prepare to start counting consecutive integers at the largest prime + 1. if i 
                    // isn't divisible by any of the primes found so far.
                    startConsecCount = primesSoFar[k - 2] + 1;
                }
            }else
            {
                if (startConsecCount != 0) // Begin counting consecutively at the largest prime + 1.
                {
                    k = startConsecCount;
                    startConsecCount = 0;
                }
                
                if (i % k == 0)
                {
                    // If i is divisible by some value of k, break.
                    isComposite = true;
                    break;
                }
            }

        }
        if (!isComposite)
        {
            printf("Prime number: %i\n", i);
            
            if (nextIdx < PRIMES_MAX_SIZE)
            {
                // If the memory allocated for the array is sufficient to store an additional prime, do so.
                primesSoFar[nextIdx] = i;
                nextIdx++;
            }

        }

    }
    
    // I'm using this to get data with which I can find a way to compute a smaller size for primesSoFar.
    double primeRatio = (double)(nextIdx + 1) / (double)(max);
    printf("The ratio of prime numbers to composites in range 0 to %d is %lf\n", max, primeRatio);

    return 0;
}
