#include <stdio.h>
#include <string.h>
#include "../../main/hashing/sha256.h"

char* data[] = {
    "",
    " ",
    "abc",
    "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
    "The quick brown fox jumps over the lazy dog",
    "The quick brown fox jumps over the lazy cog",
    "The quick brown fox jumps over the lazy doG",
    "bhn5bjmoniertqea40wro2upyflkydsibsk8ylkmgbvwi420t44cq034eou1szc1k0mk46oeb7ktzmlxqkbte2sy"
};

char* hash[] = {
    "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
    "36a9e7f1c95b82ffb99743e0c5c4ce95d83c9a430aac59f84ef3cbfab6145068",
    "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
    "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1",
    "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592",
    "e4c4d8f3bf76b692de791a173e05321150f7a345b46484fe427f6acc7ecc81be",
    "caa7ba01dcc2d625c26af46b9bbab56c066689192a7517f6b49f8ee3fe0cdbda",
    "9085df2f02e0cc455928d0f51b27b4bf1d9cd260a66ed1fda11b0a3ff5756d99"
};

int main() {
    size_t numOfTests = sizeof(data) / sizeof(data[0]);

    for (int i = 0; i < numOfTests; i++) {
        printf("Test %d: ", i);

        uint8_t result[SHA256_SIZE_BYTES];
        sha256(data[i], strlen(data[i]), result);

        char output[SHA256_SIZE_BYTES * 2 + 1];
        for (int j = 0; j < SHA256_SIZE_BYTES; j++) {
            sprintf(output + j * 2, "%02x", result[j]);
        }

        printf("%s\n", hash[i]);
        printf("        %8s", output);

        if (strncmp(output, hash[i], strlen(output)) == 0) {
            printf("     Success\n");
        } else {
            printf("     Failed\n");
        }
        printf("\n");
    }
    return 0;
}