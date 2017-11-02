/**
 * Core Paillier implementation
 *
 */

#include "paillier.h"
#include "utils.h"

#include <gmp.h>


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
  mpz_t g_to_lambda, L;
  mpz_inits(g_to_lambda, (mpz_ptr) 0);

  // mu = (L(g^lambda mod N^2))^-1 mod N
  mpz_powm(g_to_lambda, pub.g, lambda, pub.N2);
  // TODO: is mpz_legendre the right function ?!
  mpz_init_set_ui( L, mpz_legendre(g_to_lambda, pub.N) );

  if (mpz_invert(mu, L, pub.N) == 0)
    fatalError("No inverse found for L under N", 3);

  mpz_clears(g_to_lambda, L, (mpz_ptr) 0);
}


PaillierPrivateKey makePrivateKey(mpz_t lambda, const PaillierPublicKey pub) {
  PaillierPrivateKey priv;
  mpz_init_set(priv.lambda, lambda);

  mpz_init(priv.mu);
  getMu(priv.mu, lambda, pub);

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


void Encrypt(mpz_t ciphertext, const mpz_t message, const PaillierPublicKey pub,
             gmp_randstate_t rstate) {
  mpz_t r, gtom, rton;
  mpz_inits(r, gtom, rton, (mpz_ptr) 0);
  mpz_urandomm(r, rstate, pub.N);

  // c = (g^m * r^n) mod n2
  mpz_powm(gtom, pub.g, message, pub.N2);
  mpz_powm(rton, r,     pub.N,   pub.N2);
  mpz_mul(ciphertext, gtom, rton);

  mpz_clears(r, gtom, rton, (mpz_ptr) 0);
}
