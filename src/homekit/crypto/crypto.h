/*
 * crypto.h
 *
 *  Created on: Jun 25, 2015
 *      Author: tim
 */

#ifndef HOMEKIT_CRYPTO_H_
#define HOMEKIT_CRYPTO_H_

#include "tweetnacl-modified/tweetnacl.h"
#include "srp/srp.h"

typedef struct
{
  struct
  {
    // Public key is the last 32-bytes of the secret key
    union
    {
      uint8_t secret[64];
      struct
      {
        uint8_t __ignore__[32];
        uint8_t public[32];
      };
    };
  } sign;
  struct
  {
    uint8_t secret[32];
    uint8_t public[32];
  } verify;
  struct
  {
    uint8_t name[36];
    uint8_t ltpk[32];
  } client;
} crypto_keys_t;

extern crypto_keys_t crypto_keys;


extern void crypto_init(void);
extern void crypto_storeKeys(void);
extern uint8_t crypto_verifyAndDecrypt(const uint8_t* key, uint8_t* nonce, uint8_t* encrypted, uint8_t length, uint8_t* output_buf, uint8_t* mac);
extern void crypto_encryptAndSeal(const uint8_t* key, uint8_t* nonce, uint8_t* plain, uint16_t length, uint8_t* output_buf, uint8_t* output_mac);
extern void crypto_sha512hmac(uint8_t* hash, uint8_t* salt, uint8_t salt_length, uint8_t* data, uint8_t data_length);
extern void crypto_hkdf(uint8_t* target, uint8_t* salt, uint8_t salt_length, uint8_t* info, uint8_t info_length, uint8_t* ikm, uint8_t ikm_length);
extern void crypto_transportEncrypt(uint8_t* key, uint8_t* nonce, uint8_t* plaintext, uint16_t plength, uint8_t* ciphertext, uint16_t* clength);
extern uint8_t crypto_transportDecrypt(uint8_t* key, uint8_t* nonce, uint8_t* ciphertext, uint16_t clength, uint8_t* plaintext, uint16_t* plength);

#endif /* HOMEKIT_CRYPTO_H_ */