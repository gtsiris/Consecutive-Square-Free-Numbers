/* File: consnsqf.c */
#include <stdio.h>                                                                                                /* Header file for standard I/O library */
#define K       9                                                                                                           /* Number of consecutive NSQF */
#define FALSE   0
#define TRUE    (!FALSE)


int main(void) {
  register unsigned int num, prime, quotient;                                          /* This is the most efficient variable type for speed optimization */
  register unsigned int /* short */ max, div;                                          /* This is the most efficient variable type for speed optimization */
  register unsigned int /* char */ k, is_prime, is_nsqf;                               /* This is the most efficient variable type for speed optimization */

  /* The seeking loop checks every K number as long as no NSQF is found */
  for (num = K, k = 0; k < K; num = num + K) {                                                        /* Initialize num as K and increment by K each loop */

    /* Calculate maximum prime value */
    for (max = 2; max*max <= num; max++);                          /* A prime bigger than the square root of num cannot appear twice as divisor of a NSQF */
    max--;                                                                     /* The loop exits with the 1st invalid value for max, so decrease max by 1 */
    /*********************************/

    /* Prime numbers generator */
    for (prime = 2, is_nsqf = FALSE; is_nsqf == FALSE && prime <= max; prime++) {          /* Repeat prime seeking until figure out if num is NSQF or not */
      is_prime = TRUE;                                                                                                         /* Flag for prime checking */
      if (prime != 2 && prime != 3 && prime != 5) {                                                        /* Check if the potential prime is 2 or 3 or 5 */
        if (prime % 2 == 0 || prime % 3 == 0 || prime % 5 == 0) {                        /* Check if 2 or 3 or 5 can perfectly divide the potential prime */
          is_prime = FALSE;                                                                                             /* If yes, then it is not a prime */
        }
        div = 7;                                                  /* Set the divisor as the first number which cannot be perfectly devided by 2 or 3 or 5 */
        while (is_prime == TRUE && div*div <= prime) {  /* Repeat as long as there is no divisor of potential prime less than or equal to its square root */
          if (prime % div == 0 || prime % (div + 4) == 0 || prime % (div + 6) == 0 || prime % (div + 10) == 0 || prime % (div + 12) == 0 || \
          prime % (div + 16) == 0 || prime % (div + 22) == 0 || prime % (div + 24) == 0) {          /* Check if the next 2x3x5=30 numbers (including div),
		   which cannot be perfectly devided by 2 or 3 or 5, can perfectly devide the potential prime */
            is_prime = FALSE;                                                                                           /* If yes, then it is not a prime */
          }
          div = div + 30;                                                /* Increase divisor by 2x3x5=30, in order to skip the 30 already checked numbers */
        }
      }

      /* If prime, then check number for NSQF */
      if (is_prime == TRUE) {
        if (num % (prime * prime) == 0) {                                                    /* Check if the square of the prime can perfectly devide num */
          is_nsqf = TRUE;                                                                                     /* If yes, then num is NSQF (by definition) */
          k++;                                                                                  /* After a succesfull NSQF check, increase k counter by 1 */
          num = num - (K + 1);                                               /* After a succesfull NSQF check, need to check the previous number (num - 1).
                                                                        Because at the loop entry the num is increased by K, here is decreased by (K + 1) */
        }
      }
      /****************************************/
    }

    /* If not NSQF, then reset k counter */
    if (is_nsqf == FALSE) {
      k = 0;
    }
    /*************************************/

  }
  /* The printing loop for the K consecutive NSQF */
  while (k--) {
    num ++;
    printf("%d = ",num);                                                                                                                /* Print the NSQF */
    /* Prime numbers generator */
    for (prime = 2, quotient = num; quotient > 1; prime++) {                                                                       /* Prime factorization */
      is_prime = TRUE;                                                                                                         /* Flag for prime checking */
      if (prime != 2 && prime != 3 && prime != 5) {                                                        /* Check if the potential prime is 2 or 3 or 5 */
        if (prime % 2 == 0 || prime % 3 == 0 || prime % 5 == 0) {                        /* Check if 2 or 3 or 5 can perfectly divide the potential prime */
          is_prime = FALSE;                                                                                             /* If yes, then it is not a prime */
        }
        div = 7;                                                  /* Set the divisor as the first number which cannot be perfectly devided by 2 or 3 or 5 */
        while (is_prime == TRUE && div*div <= prime) {  /* Repeat as long as there is no divisor of potential prime less than or equal to its square root */
          if (prime % div == 0 || prime % (div + 4) == 0 || prime % (div + 6) == 0 || prime % (div + 10) == 0 || prime % (div + 12) == 0 || \
          prime % (div + 16) == 0 || prime % (div + 22) == 0 || prime % (div + 24) == 0) {          /* Check if the next 2x3x5=30 numbers (including div),
		   which cannot be perfectly devided by 2 or 3 or 5, can perfectly devide the potential prime */

            is_prime = FALSE;                                                                                           /* If yes, then it is not a prime */
          }
          div = div + 30;                                                /* Increase divisor by 2x3x5=30, in order to skip the 30 already checked numbers */
        }
      }

      /* If prime, then include it in prime factorization as many times as it can perfectly devide quotient */
      if (is_prime == TRUE) {                                                                                                           /* Check if prime */
        while (quotient % prime == 0) {                                                          /* Repeat as long as prime can perfectly devide quotient */
          printf("%d", prime);                                                                                                             /* Print prime */
          quotient = quotient / prime;                                                                                                /* Refresh quotient */
          if (quotient > 1) {                                                                    /* Check if quotient can be perfectly devided more times */
            printf(" x ");                                                      /* If yes, then print " x " as the multiplication sign for the next prime */
          }
        }
      }
      /******************************************************************************************************/
    }

    /* The prime factorization of the current NSQF is done */
    printf("\n");                                                                   /* Change line for the next NSQF analysis (or the end of the program) */
    /*******************************************************/
  }
  return 0;
}
