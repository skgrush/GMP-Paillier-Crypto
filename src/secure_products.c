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
