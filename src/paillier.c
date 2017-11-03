/**
 * Core Paillier implementation
 *
 */

#include "paillier.h"
#include "utils.h"

#include <gmp.h>


/**
 * L(x) = (x-1)//n
 */
void L(mpz_t out, const mpz_t x, const mpz_t N) {
  mpz_t val;
  mpz_init(val);

  mpz_sub_ui(val, x, 1);
  mpz_tdiv_q(out, val, N);

  mpz_clear(val);
}


void getLambda(mpz_t lambda, const mpz_t p, const mpz_t q) {
  mpz_t p_1, q_1;
  mpz_inits(p_1, q_1, (mpz_ptr) 0);

  mpz_sub_ui(p_1, p, 1);
  mpz_sub_ui(q_1, q, 1);

  // λ = lcm(p-1, q-1)
  mpz_lcm(lambda, p_1, q_1);

  mpz_clears(p_1, q_1, (mpz_ptr) 0);
}


void getMu(mpz_t mu, const mpz_t lambda, const PaillierPublicKey pub) {
  // µ = ( L(g^λ mod N^2) )^-1 mod N
  mpz_powm(mu, pub.g, lambda, pub.N2);
  L(mu, mu, pub.N);
  if (mpz_invert(mu, mu, pub.N) == 0)
    fatalError("No inverse found for L under N", 3);
}


PaillierPrivateKey makePrivateKey(mpz_t lambda, const PaillierPublicKey pub) {
  PaillierPrivateKey priv;
  mpz_init_set(priv.lambda, lambda);

  mpz_init(priv.mu);
  getMu(priv.mu, lambda, pub);

  mpz_init_set(priv.N, pub.N);
  mpz_init_set(priv.N2, pub.N2);

  return priv;
}


PaillierPublicKey makePublicKey(mpz_t N, mpz_t g) {
  PaillierPublicKey pub;
  mpz_init_set(pub.N, N);
  mpz_init_set(pub.g, g);

  mpz_init(pub.N2);
  mpz_pow_ui(pub.N2, N, 2);

  return pub;
}


void Encrypt(mpz_t ciphertext, const mpz_t message,
             const PaillierPublicKey pub) {
  mpz_t r, gtom, rton;
  mpz_inits(r, gtom, rton, (mpz_ptr) 0);
  mpz_urandomm(r, gpc_randstate, pub.N);

  // c = (g^m * r^n) mod n2
  mpz_powm(gtom, pub.g, message, pub.N2);
  mpz_powm(rton, r,     pub.N,   pub.N2);
  mpz_mul(ciphertext, gtom, rton);

  mpz_clears(r, gtom, rton, (mpz_ptr) 0);
}


void EncryptArray(mpz_t cipher[], const mpz_t plain[], unsigned int len,
                  const PaillierPublicKey pub) {
  unsigned int itr;
  for (itr = 0; itr < len; itr++) {
    Encrypt(cipher[itr], plain[itr], pub);
  }
}


/* D(c) = L(c^λ mod N^2) * µ mod N */
void Decrypt(mpz_t message, const mpz_t ciphertext,
             const PaillierPrivateKey sk) {
  mpz_t val;
  mpz_init(val);

  mpz_powm(val, ciphertext, sk.lambda, sk.N2);
  L(val, val, sk.N);
  mpz_mul(val, val, sk.mu);

  mpz_mod(message, val, sk.N);
}
