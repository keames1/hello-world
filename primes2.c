/*
  A super optimized prime number generator using my own implementation of the sieve of Eratosthenes.
*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main ()
{
    int max;
    printf("Please enter the maximum to which you would like to see all primes listed: "
      ); scanf("%i", &max);
    
    /*
      Primes and their multiples will be stored until the next multiple of the prime is larger than max.
      That prime and its corresponding multiple will then be replaced with a new prime and its corresponding
      multiple.
    */
    int PRIMES_MAX_SIZE = (int)sqrt(max) + 1;
    int primes[PRIMES_MAX_SIZE];
    int multiples[PRIMES_MAX_SIZE];
    primes[0] = 2;
    multiples[0] = 0;
    int nextIdx = 1;

    int startConsecCount = 0;
    bool isComposite;
    
    printf("All prime numbers in the range 0 to %i:\n\n", max);
    // Iterate from i = 2 to i = max and test each i for primality.
    for (int i = 2; i <= max; i++)
    {
        isComposite = false;
        /*
          Check whether the current i is prime by first performing a modulus check with all previous
          prime numbers, then all consecutive integers up to the square root of max
        */
        for (int k = 0; k < (int)sqrt(i) + 1; k++)
        {
            // Look through all the primes so far and see if the current i is divisible by them,
            // then check for primes whose next multiple is larger than sqrt(max) and discard them.
            if (k < nextIdx)
            {
                if (multiples[k] < i)
                {
                    multiples[k] = primes[k] * (int)(i / primes[k]);
                    if (multiples[k] < i) multiples[k] += primes[k];
                }
                if (multiples[k] == i && i != 2 && i != 3 && i != 5)
                {
                    isComposite = true;
                    break;
                }
                /*
                  Update the variable that holds to point at which to begin the modulus testing of consecutive
                  integers.
                */
                startConsecCount = primes[k] + 1;
            
            /*
              Handle the testing of consecutive integers after the prime testing is complete. 
            */
            } else
            {
                if (startConsecCount != 0)
                {
                    k = startConsecCount;
                    startConsecCount = 0;
                }
                if (i % k == 0 && i != 2 && i != 3)
                {
                    isComposite = true;
                    break;
                }
            }
        }
        // Print out the prime numbers and store them for later use in primality testing.
        if (!isComposite)
        {
            printf("Prime number: %d\n", i);
            
            if (nextIdx < PRIMES_MAX_SIZE)
            {
                primes[nextIdx] = i;
                multiples[nextIdx] = 0;
                nextIdx++;
            }
        }
    }

    return 0;
}
