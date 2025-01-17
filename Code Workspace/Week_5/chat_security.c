#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>


#define NONCE_SIZE 12
#define KEY_SIZE 32
#define IV_SIZE 16

void chat_encrypt(void *k, void *pt, int ptlen, void *ct);
void chat_decrypt(void *k, void *ct, int ctlen, void *pt);



void chat_encrypt(void *k, void *pt, int ptlen, void *ct){

	unsigned char *key = (unsigned char *)k;
	unsigned char *plaintext = (unsigned char *)pt;
	unsigned char *ciphertext = (unsigned char *)ct;
	int len;
	unsigned char nonce[NONCE_SIZE];
	unsigned char iv[IV_SIZE];
	int ct_bytes_written = 0;

	RAND_bytes(nonce, NONCE_SIZE);
	memcpy(ciphertext, nonce, NONCE_SIZE);
	memcpy(iv, nonce, NONCE_SIZE);
	memset(iv + NONCE_SIZE, 0, 4);


	EVP_CIPHER_CTX *ctx;
	ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
	EVP_EncryptUpdate(ctx, ciphertext +  NONCE_SIZE,&len, plaintext, ptlen);
	ct_bytes_written = ct_bytes_written + len;
	EVP_EncryptFinal_ex(ctx, ciphertext + NONCE_SIZE+ len, &len);
	ct_bytes_written = ct_bytes_written + len;
	EVP_CIPHER_CTX_free(ctx);

}

void chat_decrypt(void *k, void *ct, int ctlen, void *pt){

	unsigned char *key = (unsigned char *)k;
	unsigned char *plaintext = (unsigned char *)pt;
	unsigned char *ciphertext = (unsigned char *)ct;
	int len = 0;
	unsigned char nonce[NONCE_SIZE];
	unsigned char iv[IV_SIZE];
	int pt_bytes_written = 0;

	memcpy(nonce, ciphertext, NONCE_SIZE);

	memcpy(iv, nonce, NONCE_SIZE);
	memset(iv + NONCE_SIZE, 0, 4);
	EVP_CIPHER_CTX *ctx;
	ctx = EVP_CIPHER_CTX_new();
	EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
	EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext + NONCE_SIZE, ctlen - NONCE_SIZE);
	pt_bytes_written = pt_bytes_written + len;
	EVP_DecryptFinal_ex(ctx, plaintext + pt_bytes_written, &len);
	pt_bytes_written = pt_bytes_written + len;

	EVP_CIPHER_CTX_free(ctx);

}



	
