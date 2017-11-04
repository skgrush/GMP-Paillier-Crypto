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



/**
 * Multiplies using ciphertext-by-plaintext approach
 *
 */
void homomorphicMult(mpz_t encProduct, const mpz_t A, const mpz_t B, 
                  const PaillierPublicKey pub);

void homomorphicAdd(mpz_t result, 
                    const mpz_t A, const mpz_t B, 
                    const PaillierPublicKey pub);

void dotProd(mpz_t UdotV, const mpz_t *U, const mpz_t *V, const int LEN, 
             const PaillierPublicKey pub);

#endif // SECURE_PRODUCT_H_
