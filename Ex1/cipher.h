#ifndef CIPHER
#define CIPHER
#include <stdio.h>
#include <string.h>
#define FIRST_UPPER_CASE_LETTER 'A'
#define LAST_UPPER_CASE_LETTER 'Z'
#define FIRST_LOWER_CASE_LETTER 'a'
#define LAST_LOWER_CASE_LETTER 'z'
#define NUM_OF_LETTERS 26
/**
 * helper function -> do encode with k shiftt on p
 * @param p string to encode/decode
 * @param k integer - num of shifts
 */
void helper_cipher (char *p, int k)
{
    int l = strlen (p);
    char first, last;
    for (int i = 0; i < l; ++i)
    {
      if (!(p[i] >= FIRST_UPPER_CASE_LETTER && p[i] <= LAST_UPPER_CASE_LETTER)
      && !(p[i] >= FIRST_LOWER_CASE_LETTER && p[i] <= LAST_LOWER_CASE_LETTER))
        {
            continue;
        }
        //uppercase letter
        if (p[i] >= FIRST_UPPER_CASE_LETTER && p[i] <= LAST_UPPER_CASE_LETTER)
        {
            first = FIRST_UPPER_CASE_LETTER;
            last = LAST_UPPER_CASE_LETTER;

        }
        else
        {
            first = FIRST_LOWER_CASE_LETTER;
            last = LAST_LOWER_CASE_LETTER;

        }
        //lowercase letter
        if (k >= 0)
        {
            int n = ((*(p + i) + k) - first) % NUM_OF_LETTERS;
            *(p + i) = first + n;
        }
        else
        {
            int n = (last - (*(p + i) + k)) % NUM_OF_LETTERS;
            *(p + i) = last - n;
        }
    }
}
/**
 * Encode function -> use helper_cipher function
 * @param p string to encode
 * @param k num of shifts
 */
void encode (char *p, int k)
{
    helper_cipher (p, k);
}
/**
 * Decode function -> use helper_cipher function with -k
 * shifts (decode(k)= encode(-k))
 * @param p string to decode
 * @param k num of shifts
 */
void decode (char *p, int k)
{
    helper_cipher (p, -k);
}

#endif
