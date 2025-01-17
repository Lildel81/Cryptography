#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static uint32_t rotl32(uint32_t x, int n) {
    return (x << n) | (x >> (32-n));
}

// ap - dp are references to four variables to be mixed.
// A good compiler will keep everything in registers, so even
// though it looks like we're reading memory, we probably aren't.
void mix(uint32_t *ap, uint32_t *bp, uint32_t *cp, uint32_t *dp) {
    // Receive the four words to be mixed
    uint32_t a = *ap;
    uint32_t b = *bp;
    uint32_t c = *cp;
    uint32_t d = *dp;
    //printf("is called");
    

    // Mix the four words

    a = a + b;
    d = d ^ a;
    d = rotl32(d, 16);
    c = c + d;
    b = b ^ c;
    b = rotl32(b, 12);
    a = a + b;
    d = d ^ a;
    d = rotl32(d, 8);
    c = c + d;
    b = b ^ c;
    b = rotl32(b, 7);
    

    

    // Update the caller's values
    *ap = a;
    *bp = b;
    *cp = c;
    *dp = d;   
}



void p152(void *in, void *out) {
   // uint32_t *b = (uint32_t *)in;
    uint32_t *b_out = (uint32_t *)out;
    uint32_t b_in[16];
    memcpy(b_in, in, 64);
    
    /*for (int i = 0; i < 16; i++){
        printf("%02x", &b_in[i]);
    }*/
    printf("%02x\n\n", b_in[0]);
    
    for (int i = 0; i < 10; i++){
        mix(&b_in[0], &b_in[4], &b_in[8], &b_in[12]);
        mix(&b_in[1], &b_in[5], &b_in[9], &b_in[13]);
        mix(&b_in[2], &b_in[6], &b_in[10], &b_in[14]);
        mix(&b_in[3], &b_in[7], &b_in[11], &b_in[15]);

        mix(&b_in[0], &b_in[5], &b_in[10], &b_in[15]);
        mix(&b_in[1], &b_in[6], &b_in[11], &b_in[12]);
        mix(&b_in[2], &b_in[7], &b_in[8], &b_in[13]);
        mix(&b_in[3], &b_in[4], &b_in[9], &b_in[14]);


    }
    
    for (int i = 0; i < 16; i++){
        b_out[i] = b_in[i];
    }
    
    
    

}

 // Set to 1 while testing and 0 for submission

#include <stdio.h>

int main() {
    unsigned char buf[64] = {1};  // Puts 1 in frist byte, rest get auto zeroed
    
    p152(buf, buf);
    // As a test, output the first 16 bytes of the output
    printf("\nIs       : ");
    for (int i=0; i<16; i++)
        printf("%02x", buf[i]);
    printf("\n");
    printf("Should be: 14627e9771052d97a8a025cc5531572f\n");
}

