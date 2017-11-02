/**
 * Header file for core Paillier implementation
 *
 */

#ifndef PAILLIER_H_
#define PAILLIER_H_


#include <gmp.h>


typedef struct PaillierPublicKey {
  mpz_t N;
  mpz_t g;
} PaillierPublicKey;

typedef struct PaillierPrivateKey {
  mpz_t lambda;
  mpz_t mu;
} PaillierPrivateKey;


void getLambda(mpz_t lambda, const mpz_t p, const mpz_t q);

void getMu(mpz_t mu, const mpz_t lambda, const mpz_t g, const mpz_t N);







#endif // PAILLIER_H_
