/**
 * Header file for shared utilities
 *
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <gmp.h>


size_t prompt(char const *prompt, char **inputptr);

unsigned short readFromFile(FILE *file, mpz_t *values);

#endif // UTILS_H_
