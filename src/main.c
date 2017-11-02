/**
 * Main user interface.
 *
 */

#include "utils.h"
#include "paillier.h"

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>


int main(int argc, char *argv[]) {

  char *pqg_filename = NULL;
  char *lambdamu_filename = NULL;
  char *vectorU_filename = NULL;
  char *encU_filename = NULL;
  char *vectorV_filename = NULL;
  char *encV_filename = NULL;
  char *output_filename = NULL;
  mpz_t p;
  mpz_t q;
  mpz_t g;
  mpz_t N;
  mpz_t lambda;
  mpz_t mu;

  // FILE *pqg_file;
  // FILE *lambdamu_file;
  // FILE *vectorU_file;
  // FILE *encU_file;
  // FILE *vectorV_file;
  // FILE *encV_file;
  // FILE *output_file;

  // variables for reuse
  unsigned int readcount;
  FILE *file;
  mpz_t *mpz_array = NULL;


  printf("Greetings and Salutations!\n\n");

  prompt("Enter the name of the file that contains p, q, and g: ",
          &pqg_filename);
  prompt("Enter the output file name to store λ and µ: ", &lambdamu_filename);
  prompt("Enter the name of the file that contains vector-u: ",
          &vectorU_filename);
  prompt("Enter the output file name to store E(u): ", &encU_filename);
  prompt("Enter the name of the file that contains vector-v: ",
          &vectorV_filename);
  prompt("Enter the output file name to store E(v): ", &encV_filename);
  prompt("Enter the output file name to store E(u.v) and u.v: ",
          &output_filename);

  printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", pqg_filename, lambdamu_filename,
         vectorU_filename, encU_filename, vectorV_filename, encV_filename,
         output_filename);


  // 1. read p,q,g from `pqg_filename`
  file = fopen(pqg_filename, "r");
  if (file == NULL)
    fatalError("Failed to open pqg file", 1);
  else
    printf("Successfully opened pqg file, attempting read.\n");

  readcount = readFromFile(file, &mpz_array);
  fclose(file);

  if (readcount != 3)
    fatalError("pqg file contains wrong number of values", 1);
  else
    printf("Correctly found 3 values in pqg file\n");

  mpz_init_set(p, mpz_array[0]);
  mpz_init_set(q, mpz_array[1]);
  mpz_init_set(g, mpz_array[2]);
  freeMPZArray(&mpz_array, 3);

  gmp_printf("p = %Zd\nq = %Zd\ng = %Zd\n", p, q, g);


  // generate n, lambda, and mu
  mpz_inits(N, lambda, mu, (mpz_ptr) 0);
  mpz_mul(N, p, q);
  getLambda(lambda, p, q);
  getMu(mu, lambda, g, N);

  gmp_printf("N = %Zd\nλ = %Zd\nµ = %Zd\n", N, lambda, mu);

  // 2. output lambda and mu to `lambdamu_filename`
  file = fopen(lambdamu_filename, "w");
  if (file == NULL)
    fatalError("Failed to open λµ file", 1);
  else
    printf("Successfully opened λµ file, attempting to write.\n");

  readcount = mpz_out_str(file, 10, lambda);
  if (readcount == 0)
    fatalError("Failed to write to λµ file", 1);
  fprintf(file, "\n");
  readcount = mpz_out_str(file, 10, mu);
  if (readcount == 0)
    fatalError("Failed to write to λµ file", 1);
  else
    printf("Successfully wrote to λµ file\n");
  fclose(file);


  // TODO: 3. read in arbitrary-length-Ulen vector U from `vectorU_filename`

  // TODO: encrypt vector U
  // TODO: 4. output encrypted U to `encU_filename`

  // TODO: 5. read in arbitrary-length-Vlen vector V from `vectorV_filename`
  // TODO: check Ulen==Vlen, even though Wei said we don't need to

  // TODO: encrypt vector V
  // TODO: 6. output encrypted V to `encV_filename`

  // TODO: compute E(u.v)
  // TODO: decrypt to u.v
  // TODO: 7. output E(u.v) and u.v to `output_filename`

  printf("Farewells and Valedictions!\n");
}
