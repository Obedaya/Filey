#include "../include/hasher.h"

Hasher::Hasher() {
    OpenSSL_add_all_algorithms();
}

std::string Hasher::getHashFile(const char *path) {
    // Open file
    FILE *file = fopen(path, "rb");
    if (!file) {
        std::cerr << "Fehler beim Öffnen der Log-Datei!" << std::endl;
        return "";
    }

    // Initialize new Envelope Message Digest Context to store information for the hashing operation
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        std::cerr << "Fehler beim erstellen des EVPs" << std::endl;
        fclose(file);
        return "";
    }
    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        std::cerr << "Fehler beim initialisieren des EVPs" << std::endl;
        fclose(file);
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    // Splits file into 1024-byte chunks and reads them
    unsigned char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, 1024, file)) != 0) {
        // Updates the hash with the new bytes
        if (1 != EVP_DigestUpdate(mdctx, buffer, bytes_read)) {
            std::cerr << "Fehler beim hashen der Datei" << std::endl;
            fclose(file);
            EVP_MD_CTX_free(mdctx);
            return "";
        }
    }

    // Completes the hash function and returns the final hash
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    if (1 != EVP_DigestFinal_ex(mdctx, md_value, &md_len)) {
        std::cerr << "Fehler bei der Finalisierung" << std::endl;
        fclose(file);
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    // Closes the file
    fclose(file);
    EVP_MD_CTX_free(mdctx);

    // Convert the hash to a hexadecimal string
    std::stringstream ss;
    for (unsigned int i = 0; i < md_len; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)md_value[i];
    }

    return ss.str();
}
