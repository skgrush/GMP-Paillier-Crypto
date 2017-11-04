/**
 * Secure multiplication and dot-product using Paillier
 *
 */


#include "secure_products.h"

#include "paillier.h"
#include "utils.h"


void secureMult_P1_makeAp(mpz_t Ap, mpz_t r_A,
                          const mpz_t encryptedA,
                          const PaillierPublicKey pub) {
  mpz_t encrypted_r_A;
  mpz_init(encrypted_r_A);

  mpz_urandomm(r_A, gpc_randstate, pub.N);
  Encrypt(encrypted_r_A, r_A, pub);

  mpz_mul(Ap, encryptedA, encrypted_r_A);
  mpz_mod(Ap, Ap, pub.N);

  mpz_clear(encrypted_r_A);
}

void secureMult_P2_makeHp(mpz_t Hp,
                          const mpz_t Ap, const mpz_t Bp,
                          const PaillierPrivateKey sk,
                          const PaillierPublicKey pub) {
  mpz_t H_A, H_B;
  mpz_inits(H_A, H_B, (mpz_ptr) 0);

  Decrypt(H_A, Ap, sk);
  Decrypt(H_B, Bp, sk);

  mpz_mul(Hp, H_A, H_B);
  mpz_mod(Hp, Hp, sk.N);

  Encrypt(Hp, Hp, pub);
}

void secureMult_P1_HpToProduct(mpz_t encProduct,
                               const mpz_t Hp, const mpz_t r_A, const mpz_t r_B,
                               const mpz_t encryptedA, const mpz_t encryptedB,
                               const PaillierPublicKey pub) {
  mpz_t S, Sp, N_1;
  mpz_inits(S, Sp, N_1, (mpz_ptr) 0);

  // s  <-  h' * E(a)^(N-r_b)
  mpz_sub(S, pub.N, r_B);
  mpz_powm(S, encryptedA, S, pub.N);
  mpz_mul(S, Hp, S);
  mpz_mod(S, S, pub.N);

  // s'  <-  s * E(b)^(N-r_a)
  mpz_sub(Sp, pub.N, r_A);
  mpz_powm(Sp, encryptedB, Sp, pub.N);
  mpz_mul(Sp, S, Sp);
  mpz_mod(Sp, Sp, pub.N);

  mpz_init_set_ui(N_1, 1);
  mpz_sub(N_1, pub.N, N_1);

  // E(a*b)  <-  s' * E(r_a * r_b)^(N-1)
  mpz_mul(encProduct, r_A, r_B);
  Encrypt(encProduct, encProduct, pub);
  mpz_powm(encProduct, encProduct, N_1, pub.N);
  mpz_mul(encProduct, Sp, encProduct);
}

void homomorphicMult(mpz_t encProduct, 
                  const mpz_t encA, const mpz_t B, 
                  const PaillierPublicKey pub) {
  // E(A*B) <- E(A)^B % N^2
  mpz_powm(encProduct, encA, B, pub.N2);
}

void homomorphicAdd(mpz_t encSum, 
                    const mpz_t encA, const mpz_t encB, 
                    const PaillierPublicKey pub) {
  // E(A+B) <- E(A)*E(B) % N^2
  mpz_mul(encSum, encA, encB);
  mpz_mod(encSum, encSum, pub.N2);
}

void dotProd(mpz_t encDot, const mpz_t *encU, const mpz_t *V, const int LEN, 
             const PaillierPublicKey pub) {
  mpz_t encUV;
   
  for (int i = 0; i < LEN; i++) {
    mpz_init(encUV);
    // multiply corresponding elements
    homomorphicMult(encUV, encU[i], V[i], pub);
    // add to dot product sum
    homomorphicAdd(encDot, encUV, encDot, pub);
    mpz_clear(encUV);
  }
}
