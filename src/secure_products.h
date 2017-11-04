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
 * encProduct <- E(A)^B mod N^2
 *            <- E(A*B)
 *
 * Arguments:
 *  encProduct  output encrypted product of A*B (E(A*B))
 *  encA        input E(A)
 *  encB        input B
 *  pub         public key
 */
void homomorphicMult(mpz_t encProduct, const mpz_t A, const mpz_t B, 
                  const PaillierPublicKey pub);


/**
 * Adds two paillier encrypted values
 *
 * result <- E(A)*E(B) mod N^2
 *        <- E(A+B)
 *
 * Arguments:
 *  encSum      output encrypted sum of A+B (E(A+B))
 *  encA        input E(A)
 *  encB        input E(B)
 *  pub         public key
 */
void homomorphicAdd(mpz_t encSum, 
                    const mpz_t encA, const mpz_t encB, 
                    const PaillierPublicKey pub);

/**
 * Encrypted dot product of one encrypted and one plaintext vector
 *
 * Arguments:
 *  encDot      output encrypted dot product of u.v
 *  encU        input encrypted vector U
 *  V           input plaintext vector V
 *  LEN         input vector length
 *  pub         public key
 */
void dotProd(mpz_t encDot, const mpz_t *encU, const mpz_t *V, const int LEN, 
             const PaillierPublicKey pub);

#endif // SECURE_PRODUCT_H_
