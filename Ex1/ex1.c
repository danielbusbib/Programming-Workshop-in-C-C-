//
// Created by bsbdaniel1234 on 24/10/2021.
//
#ifndef BONUS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cipher.h"
//global values:
#define ENCODE "encode"
#define DECODE "decode"
#define ERROR_NUM_ARGS_MSG "Usage: cipher <encode|decode>"\
" <k> <source path file> <output path file>\n"
#define ERROR_SHIFT_NUM_MSG "The given shifts value is invalid\n"
#define ERROR_COMMAND_MSG "The given command is invalid\n"
#define ERROR_INVALIDE_FILE_MSG "The given file is invalid\n"
#define NUM_ARGS 5
#define TEN 10
#define INPUT_SIZE 40
#define MAX_CHARS 100001
/**
 * This function check if k consist only digits (or '-' in start neg num)
 * @param k string
 * @return 1 if k is not a  num else 0
 */
int check (const char *k)
{
    int l = strlen (k);
    for (int i = 0; i < l; ++i)
    {
        if (i == 0 && k[i] == '-' && i + 1 < l )
        {
            continue;
        }
        if (!(k[i] >= '0' && k[i] <= '9'))
        {
            return 1;
        }
    }
    return 0;
}
/**
 * main function -> check arguments, print error msg if needed,
 * open input file, encode/decode the file to output file.
 * @param argc
 * @param argv
 * @return 1 in failure else 0
 */
int main (int argc, const char *argv[])
{
    // checking arguments characteristic:
    if (argc != NUM_ARGS)
    {
        fprintf (stderr, ERROR_NUM_ARGS_MSG);
        //close file!!!!!!!!
        return EXIT_FAILURE;
    }
    if (check (argv[2]) == 1)
    {
        fprintf (stderr, ERROR_SHIFT_NUM_MSG);
        return EXIT_FAILURE;
    }
    if (strcmp (argv[1], ENCODE) != 0 && strcmp (argv[1], DECODE) != 0)
    {
        fprintf (stderr, ERROR_COMMAND_MSG);
        return EXIT_FAILURE;
    }
    int k = (int) strtol (argv[2], NULL, TEN );
    // trying open input file:
    FILE *f = fopen (argv[3], "r");
    if (f == NULL)
    {
        fprintf (stderr, ERROR_INVALIDE_FILE_MSG);
        return EXIT_FAILURE;
    }

    FILE *out_file = fopen (argv[4], "w");
    char buffer[MAX_CHARS];
    char input[INPUT_SIZE];
    // get into buffer all text from input file
    while (fgets (input, INPUT_SIZE, f))
    {
        strcat (buffer, input);
    }
     // do encode/decode:
    if (strcmp(argv[1], ENCODE) == 0)
    {
        encode (buffer, k);
    }
    else
    {
        decode (buffer, k);
    }

    //write to output file
    fprintf (out_file, "%s", buffer);
    fclose (out_file);
    fclose (f);
    return 0;
}

#endif