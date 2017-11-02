/**
 * Shared utilities
 *
 */

#include "utils.h"

#include <string.h>
#include <stdlib.h>

size_t prompt(char const *prompt, char **inputptr) {
  size_t readlen = 0;
  size_t len;

  printf("%s", prompt);
  getline(inputptr, &readlen, stdin);
  len = strlen(*inputptr);
  if ((*inputptr)[len - 1] == '\n') {
    (*inputptr)[len - 1] = '\0';
    len--;
  }
  else
    printf("tlen = %ld\n", len);
  return (len);
}


/**
 * Read newline-separated numbers from a file.
 *
 *
 */
unsigned short readFromFile(FILE *file, mpz_t **values) {
  unsigned short count = 0;
  size_t num_bytes_read = 0;

  do {
    // increment `count` and extend `values`
    count++;
    printf("inloop\n");
    if(( *values = (mpz_t *) realloc(*values, sizeof(mpz_t) * count) ) == NULL)
      fatalError("Realloc failed in readFromFile", 2);
    printf("realloc'd\n");
    // initialize new mpz_t at index `count`, then try reading into it
    mpz_init( (*values)[count-1] );
    //mpz_init2( (*values)[count-1], MAX_PARAM_BITCNT );
    printf("init'd\n");
    num_bytes_read = mpz_inp_str( (*values)[count-1], file, 0 );
    printf("input'd, %ld\n", num_bytes_read);
    // continue loop if read was successful
  } while(num_bytes_read);

  count--;
  *values = (mpz_t *) realloc(*values, sizeof(mpz_t) * count);

  return count;
}

void fatalError(char const *msg, unsigned char code) {
  fprintf(stderr, "%s\n", msg);
  exit(code);
}

void clearMPZArray(mpz_t **values, size_t len) {

}
