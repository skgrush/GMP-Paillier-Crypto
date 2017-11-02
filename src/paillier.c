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


void getMu(mpz_t mu, const mpz_t lambda, const mpz_t g, const mpz_t N) {
  mpz_t N2, g_to_lambda, L;
  mpz_inits(N2, g_to_lambda, (mpz_ptr) 0);

  // mu = (L(g^lambda mod N^2))^-1 mod N
  mpz_pow_ui(N2, N, 2);
  mpz_powm(g_to_lambda, g, lambda, N2);
  // TODO: is mpz_legendre the right function ?!
  mpz_init_set_ui( L, mpz_legendre(g_to_lambda, N) );

  if (mpz_invert(mu, L, N) == 0)
    fatalError("No inverse found for L under N", 3);

  mpz_clears(N2, g_to_lambda, L, (mpz_ptr) 0);
}
