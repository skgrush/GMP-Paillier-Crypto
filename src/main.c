

#include "paillier.h"

#include <stdio.h>


int main(int argc, char *argv[]) {

  char *pqg_filename;
  FILE *pqg_file;
  char *lambdamu_filename;
  FILE *lambdamu_file;
  char *vectorU_filename;
  FILE *vectorU_file;
  char *encU_filename;
  FILE *encU_file;
  char *vectorV_filename;
  FILE *vectorV_file;
  char *encV_filename;
  FILE *encV_file;
  char *output_filename;
  FILE *output_file;

  printf("Enter the name of the file that contains p, q, and g: ");
  scanf("%s", &pqg_filename);
  printf("Enter the output file name to store LAMBDA and MU: ");
  scanf("%s", &lambdamu_filename);
  printf("Enter the name of the file that contains vector-u: ");
  scanf("%s", &vectorU_filename);
  printf("Enter the output file name to store E(u): ");
  scanf("%s", &encU_filename);
  printf("Enter the name of the file that contains vector-v: ");
  scanf("%s", &vectorV_filename);
  printf("Enter the output file name to store E(v): ");
  scanf("%s", &encV_filename);
  printf("Enter the output file name to store E(u.v) and u.v: ");
  scanf("%s", &output_filename);
}
