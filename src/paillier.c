/**
 * Core Paillier implementation
 *
 */

#include "paillier.h"
#include "utils.h"

#include <gmp.h>


void L(mpz_t out, const mpz_t x, const mpz_t N);
char check_pq(const mpz_t p, const mpz_t q, const char checkPrimality);


void keygen(PaillierPublicKey *pub, PaillierPrivateKey *sk,
            const unsigned short k) {
  mpz_t p, q, g, N, N2, lambda, mu;
  unsigned short pq_len = k/2;
  mpz_inits(p, q, g, N, N2, lambda, mu, (mpz_ptr) 0);

  do {
    mpz_urandomb(p, gpc_randstate, pq_len);
    mpz_urandomb(q, gpc_randstate, pq_len);
    mpz_nextprime(p, p);
    mpz_nextprime(q, q);
    gmp_printf("Testing (p, q) = (%Zd, %Zd)\n", p, q);
    // p and q are adequately random and prime
  } while(check_pq(p, q, 0));
  printf("Good p and q!\n");

  mpz_mul(N, p, q);
  mpz_mul_ui(N2, N, 2);
  getLambda(lambda, p, q);

  do {
    mpz_urandomb(g, gpc_randstate, 2*k);
    gmp_printf("Testing g = %Zd\n", g);
  } while(getMu(mu, lambda, g, N, N2) == 0);
  printf("Good g!\n");

  mpz_init_set(pub->N, N);
  mpz_init_set(pub->g, g);
  mpz_init_set(pub->N2, N2);
  mpz_init_set(sk->lambda, lambda);
  mpz_init_set(sk->mu, mu);
  mpz_init_set(sk->N, N);
  mpz_init_set(sk->N2, N2);

  mpz_clears(p, q, g, N, N2, lambda, mu, (mpz_ptr) 0);
}


char check_pq(const mpz_t p, const mpz_t q, const char checkPrimality) {
  mpz_t tmp, tmp2;

  if (checkPrimality) {
    if(!mpz_probab_prime_p(p, MILLER_RABIN_ROUNDS)
       || !mpz_probab_prime_p(q, MILLER_RABIN_ROUNDS))
      return 0;
  }

  if (mpz_sizeinbase(p, 2) == mpz_sizeinbase(q, 2))
    // Same bit-length; Wikipedia says this is okay
    return 1;

  mpz_inits(tmp, tmp2, (mpz_ptr) 0);
  mpz_sub_ui(tmp, p, 1);
  mpz_sub_ui(tmp2, q, 1);
  mpz_mul(tmp, tmp, tmp2); // tmp = (p-1)(q-1)
  mpz_mul(tmp2, p, q); // tmp2 = p*q
  mpz_gcd(tmp, tmp, tmp2); // tmp = gcd(pq, (p-1)(q-1))

  if(mpz_cmp_ui(tmp, 1) == 0) // gcd(pq, (p-1)(q-1)) == 1
    return 1;
  return 0;
}


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


// returns 1 if successful, else 0
int getMu(mpz_t mu, const mpz_t lambda, const mpz_t g, const mpz_t N,
          const mpz_t N2) {
  // µ = ( L(g^λ mod N^2) )^-1 mod N
  mpz_powm(mu, g, lambda, N2);
  L(mu, mu, N);
  return mpz_invert(mu, mu, N);
}


PaillierPrivateKey makePrivateKey(mpz_t lambda, const PaillierPublicKey pub) {
  PaillierPrivateKey priv;
  mpz_init_set(priv.lambda, lambda);

  mpz_init(priv.mu);
  if (!getMu(priv.mu, lambda, pub.g, pub.N, pub.N2))
    fatalError("No inverse found for L under N", 3);

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
