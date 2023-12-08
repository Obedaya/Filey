#include <iostream>
#include <fstream>
#include <openssl/evp.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream file(filename, std::ifstream::binary);


    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if(mdctx == nullptr) {
        std::cerr << "Failed to create MD context." << std::endl;
        return 1;
    }

    if(EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr) != 1) {
        std::cerr << "Failed to initialize digest." << std::endl;
        return 1;
    }

    char buffer[8192];
    while (file.read(buffer, sizeof(buffer))) {
        if(EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
            std::cerr << "Failed to update digest." << std::endl;
            return 1;
        }
    }
    if(file.gcount() > 0) {
        if(EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
            std::cerr << "Failed to update digest." << std::endl;
            return 1;
        }
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;

    if(EVP_DigestFinal_ex(mdctx, hash, &lengthOfHash) != 1) {
        std::cerr << "Failed to finalize digest." << std::endl;
        return 1;
    }

    EVP_MD_CTX_free(mdctx);
    file.close();

    // Output the hash in hexadecimal
    for(unsigned int i = 0; i < lengthOfHash; i++) {
        std::cout << std::hex << (int)hash[i];
    }
    std::cout << std::endl;

    return 0;
}
