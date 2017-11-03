/**
 * Header file for shared utilities
 *
 */

#ifndef UTILS_H_
#define UTILS_H_


#include <stdio.h>
#include <gmp.h>


#define MAX_PARAM_BITCNT 2048


gmp_randstate_t gpc_randstate;

size_t prompt(char const *prompt, char **inputptr);

unsigned short readFromFile(FILE *file, mpz_t **values);

void fatalError(char const *msg, unsigned char code);

void freeMPZArray(mpz_t **values, size_t len);

void initGlobalRandstate();

#endif // UTILS_H_
