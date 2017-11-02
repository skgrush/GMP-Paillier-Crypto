/**
 * Header file for shared utilities
 *
 */

#ifndef UTILS_H_
#define UTILS_H_


#include <stdio.h>
#include <gmp.h>


#define MAX_PARAM_BITCNT 2048


size_t prompt(char const *prompt, char **inputptr);

unsigned short readFromFile(FILE *file, mpz_t **values);

void fatalError(char const *msg, unsigned char code);

void freeMPZArray(mpz_t **values, size_t len);


#endif // UTILS_H_
