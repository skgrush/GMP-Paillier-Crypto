/**
 * Shared utilities
 *
 */

#include "utils.h"

#include <stdlib.h>

size_t prompt(char const *prompt, char **inputptr) {
  size_t len = 0;
  printf("%s", prompt);
  getline(inputptr, &len, stdin);
  return len;
}


/**
 * Read newline-separated numbers from a file.
 *
 * 
 */
unsigned short readFromFile(FILE *file, mpz_t *values) {
  unsigned short count = 0;
  size_t num_bytes_read = 0;


  do {
    // increment `count` and extend `values`
    count++;
    values = (mpz_t *) realloc(values, sizeof(mpz_t) * count);
    // initialize new mpz_t at index `count`, then try reading into it
    mpz_init( values[count] );
    num_bytes_read = mpz_inp_str( values[count], file, 0 );
    // continue loop if read was successful
  } while(num_bytes_read);

  // count is one too large
  count--;
  return count;
}
