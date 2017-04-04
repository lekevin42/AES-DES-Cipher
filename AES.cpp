#include "AES.h"

/**
 * Sets the key to use
 * @param key - the first byte of this represents whether
 * to encrypt or to decrypt. 00 means encrypt and any other
 * value to decrypt.  Then come the bytes of the 128-bit key
 * (should be 16 of them).
 * @return - True if the key is valid and False otherwise
 */
bool AES::setKey(const unsigned char* keyArray)
{
	if (strlen((char*)(keyArray)) != 17) {
		return false;
	}
	
	char* key = new char[16];
	
	strncpy(key, ((char*)(keyArray)) + 1, strlen((char*)keyArray) - 1);
		
	if (keyArray[0] == '0'){
		AES_set_encrypt_key((const unsigned char *)key, 128, &enc_key);
		delete key;
		return true;
	}
	
	else{
		AES_set_decrypt_key((const unsigned char *)key, 128, &dec_key);
		delete key;
		return true;
	}
	
	return false;
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
unsigned char* AES::encrypt(const unsigned char* plainText)
{
	unsigned char* enc_out = new unsigned char[17];
	
	memset(enc_out, 0, 17);
	

	AES_ecb_encrypt(plainText, enc_out, &enc_key, AES_ENCRYPT);
	

	return enc_out;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
unsigned char* AES::decrypt(const unsigned char* cipherText)
{
	unsigned char* dec_out = new unsigned char[17];
	
	memset(dec_out, 0, 17);
	
	AES_ecb_encrypt(cipherText, dec_out, &dec_key, AES_DECRYPT);
		
	return dec_out;
}