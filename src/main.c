/**
 * Main user interface.
 *
 */

#include "paillier.h"

#include <stdio.h>

size_t prompt(char const *prompt, char **inputptr);


int main(int argc, char *argv[]) {

  char *pqg_filename = NULL;
  FILE *pqg_file;
  char *lambdamu_filename = NULL;
  FILE *lambdamu_file;
  char *vectorU_filename = NULL;
  FILE *vectorU_file;
  char *encU_filename = NULL;
  FILE *encU_file;
  char *vectorV_filename = NULL;
  FILE *vectorV_file;
  char *encV_filename = NULL;
  FILE *encV_file;
  char *output_filename = NULL;
  FILE *output_file;

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

  printf("\n%s%s%s%s%s%s%s", pqg_filename, lambdamu_filename,
         vectorU_filename, encU_filename, vectorV_filename, encV_filename,
         output_filename);

  // TODO: 1. read p,q,g from `pqg_filename`

  // TODO: generate n, lambda, and mu
  // TODO: 2. output lambda and mu to `lambdamu_filename`

  // TODO: 3. read in arbitrary-length-N vector U from `vectorU_filename`

  // TODO: encrypt vector U
  // TODO: 4. output encrypted U to `encU_filename`

  // TODO: 5. read in arbitrary-length-N2 vector V from `vectorV_filename`
  // TODO: check N==N2, even though Wei said we don't need to

  // TODO: encrypt vector V
  // TODO: 6. output encrypted V to `encV_filename`

  // TODO: compute E(u.v)
  // TODO: decrypt to u.v
  // TODO: 7. output E(u.v) and u.v to `output_filename`

  printf("Farewells and Valedictions!\n");
}

size_t prompt(char const *prompt, char **inputptr) {
  size_t len = 0;
  printf("%s", prompt);
  getline(inputptr, &len, stdin);
  return len;
}
