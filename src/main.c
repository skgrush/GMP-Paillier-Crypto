/**
 * Main user interface.
 *
 */

#include "utils.h"
#include "paillier.h"



int main(int argc, char *argv[]) {

  char *pqg_filename = NULL;
  char *lambdamu_filename = NULL;
  char *vectorU_filename = NULL;
  char *encU_filename = NULL;
  char *vectorV_filename = NULL;
  char *encV_filename = NULL;
  char *output_filename = NULL;

  // FILE *pqg_file;
  // FILE *lambdamu_file;
  // FILE *vectorU_file;
  // FILE *encU_file;
  // FILE *vectorV_file;
  // FILE *encV_file;
  // FILE *output_file;
  FILE *file;


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
