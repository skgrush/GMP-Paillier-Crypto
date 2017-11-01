

#include "paillier.h"

#include <stdio.h>


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

  size_t len = 0;
  printf("Enter the name of the file that contains p, q, and g: ");
  getline(&pqg_filename, &len, stdin);
  printf("Enter the output file name to store LAMBDA and MU: ");
  getline(&lambdamu_filename, &len, stdin);
  printf("\nEnter the name of the file that contains vector-u: ");
  getline(&vectorU_filename, &len, stdin);
  printf("Enter the output file name to store E(u): ");
  getline(&encU_filename, &len, stdin);
  printf("Enter the name of the file that contains vector-v: ");
  getline(&vectorV_filename, &len, stdin);
  printf("Enter the output file name to store E(v): ");
  getline(&encV_filename, &len, stdin);
  printf("Enter the output file name to store E(u.v) and u.v: ");
  getline(&output_filename, &len, stdin);

  printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n", pqg_filename, lambdamu_filename,
         vectorU_filename, encU_filename, vectorV_filename, encV_filename,
         output_filename);
}
