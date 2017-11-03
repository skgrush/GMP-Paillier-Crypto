/**
 * Header for secure multiplication and dot-product using Paillier
 *
 */

#ifndef SECURE_PRODUCT_H_
#define SECURE_PRODUCT_H_


#include "paillier.h"

#include <gmp.h>


/**
 * Generates a random value r_A and homomorphically adds it to encryptedA.
 *
 * Ap <- encryptedA * E(r_A) mod N
 *    <- E(A + r_A)
 *
 * Arguments:
 *  Ap          output A' (A prime)
 *  r_A         output random value for hiding A's value
 *  rstate      input GMP randstate structure
 *  encryptedA  input E(A)
 *  pub         public key
 */
void secureMult_P1_makeAp(mpz_t Ap, mpz_t r_A,
                          const mpz_t encryptedA,
                          const PaillierPublicKey pub);

void secureMult_P2_makeHp(mpz_t Hp,
                          const mpz_t Ap, const mpz_t Bp,
                          const PaillierPrivateKey sk,
                          const PaillierPublicKey pub);


#endif // SECURE_PRODUCT_H_
