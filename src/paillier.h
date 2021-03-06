/**
 * Header file for core Paillier implementation
 *
 */

#ifndef PAILLIER_H_
#define PAILLIER_H_


#include <gmp.h>


#define MILLER_RABIN_ROUNDS 30


typedef struct PaillierPublicKey {
  mpz_t N;
  mpz_t g;
  mpz_t N2;
} PaillierPublicKey;

typedef struct PaillierPrivateKey {
  mpz_t lambda;
  mpz_t mu;
  mpz_t N;
  mpz_t N2;
} PaillierPrivateKey;


void keygen(PaillierPublicKey *pub, PaillierPrivateKey *sk,
            const unsigned short k);

void getLambda(mpz_t lambda, const mpz_t p, const mpz_t q);

int getMu(mpz_t mu, const mpz_t lambda, const mpz_t g, const mpz_t N,
          const mpz_t N2);

PaillierPrivateKey makePrivateKey(mpz_t lambda, const PaillierPublicKey pub);

PaillierPublicKey makePublicKey(mpz_t N, mpz_t g);

void Encrypt(mpz_t ciphertext, const mpz_t message,
             const PaillierPublicKey pub);

void EncryptArray(mpz_t cipher[], const mpz_t plain[], unsigned int len, const PaillierPublicKey pub);

void Decrypt(mpz_t message, const mpz_t ciphertext, const PaillierPrivateKey sk);


#endif // PAILLIER_H_
