/**
 * Shared utilities
 *
 */

#include "utils.h"

#include <string.h>
#include <stdlib.h>

gmp_randstate_t gpc_randstate;

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
    if(( *values = (mpz_t *) realloc(*values, sizeof(mpz_t) * count) ) == NULL)
      fatalError("Realloc failed in readFromFile", 2);
    // initialize new mpz_t at index `count`, then try reading into it
    mpz_init( (*values)[count-1] );
    //mpz_init2( (*values)[count-1], MAX_PARAM_BITCNT );
    num_bytes_read = mpz_inp_str( (*values)[count-1], file, 0 );
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

void freeMPZArray(mpz_t **values, size_t len) {
  size_t itr;
  for (itr = 0; itr < len; itr++)
    mpz_clear( (*values)[itr] );
  free(*values);
}

void initGlobalRandstate() {
  char seed[10];
  unsigned long numseed;
  FILE *file;
  gmp_randinit_default(gpc_randstate);

  file = fopen("/dev/urandom", "r");
  if (file == NULL)
    fatalError("Failed to read from urandom", 1);
  if (fread(seed, 10, 1, file) < 1) {
    printf("%s\n", seed);
    fatalError("Failed to read adequately from urandom", 1);
  }
  fclose(file);

  numseed = seed[0] | (seed[1] << 8) | (seed[2] << 16) | (seed[3] << 24);

  gmp_randseed_ui(gpc_randstate, numseed);
}
