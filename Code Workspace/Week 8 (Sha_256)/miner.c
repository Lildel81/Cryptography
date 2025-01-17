// miner.c by Terry Weatherman. submitted for CSC 152 October 24, 2024
// used W3Schools and Geeks4Geeks to help with syntax
// Eric Brown troubleshooted a problem for me.

#include <openssl/evp.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int leading_zero_bits(const unsigned char *hash, int bits);

void hash_sha256(const unsigned char* data, size_t data_len, unsigned char* hash, unsigned int* hash_len){


	EVP_MD_CTX* ctx = EVP_MD_CTX_new();  //creating new instance of context

	EVP_DigestInit_ex(ctx, EVP_sha256(), NULL); //initiating the content for sha256

	EVP_DigestUpdate(ctx, data, data_len); //run the ctx through the hashing algorithm

	EVP_DigestFinal_ex(ctx, hash, hash_len); //finalize the hash

	EVP_MD_CTX_free(ctx);
}

int main(int argc, char*argv[]){
	
	if (argc > 2){
		printf("Usage: %s <integer>\n", argv[0]);
		exit(1);
	}
	int number_of_zeros = atoi(argv[1]);
	if (number_of_zeros%4 != 0){
	printf("Incorrect usage: argument must be multiple of 4");
	exit(1);
	}
	

 	const char CHAR_SET[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    	const int MAX_INPUT_LENGTH = 60;
	int char_set_len = strlen(CHAR_SET);
    	int arr_size = 60;
    	unsigned char input[61];  
    	int elements[60] = {0}; 
	uint8_t hash[EVP_MAX_MD_SIZE];
	unsigned int hash_len; 

    
    	
    	input[arr_size] = '\0';  
	    
    	while (1) {
       
		hash_sha256(input, MAX_INPUT_LENGTH, hash, &hash_len);
		int zeros = leading_zero_bits(hash, number_of_zeros);
		if (zeros == 1){
			printf("Found hash with %d leading 0s\n", number_of_zeros/4);
			for(int i = 0; i < 32; i++){
				printf("%02x", hash[i]);
			}
			printf("\nUsing input: %s\n", input);
			exit(0);
		}
        	int pos = 0;
        	while (pos < arr_size) {
            		if (elements[pos] < char_set_len - 1) {
               
                	elements[pos]++;
                	input[pos] = CHAR_SET[elements[pos]];
                	break;  
            	} else {
               
                	elements[pos] = 0;
                	input[pos] = CHAR_SET[0];
                	pos++;  
            	}
        	}

        
        	if (pos == arr_size) {
            		break;
        	}
    }
    return 0;
}

int leading_zero_bits(const unsigned char *hash, int num_bits){
	int bits = num_bits/8;
	int remaining_bits = num_bits % 8;

	for (int i = 0; i < bits; i++){
		if (hash[i] != 0x00){
			return 0;
		}
	}
	if (remaining_bits > 0){
		unsigned char mask = 0xF0 >> (4 - remaining_bits);
		if ((hash[bits] & mask) != 0x00){
			return 0;
		}
	}
	return 1;
}

	






