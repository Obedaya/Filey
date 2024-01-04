#include "../include/hasher.h"

Hasher::Hasher() {
    OpenSSL_add_all_algorithms();
}

// Funktion die eine Datei und ihren Inhalt hasht
const unsigned char* Hasher::getHashFile(const char *path) {
    // Datei öffnen
    FILE *file = fopen(path, "rb");
    if (!file) {
        std::cerr << "Fehler beim öffnen der Datei!" << std::endl;
        return nullptr;
    }

    // Initialisiert neuen Envelope Message Digest Context um Informationen zur Hash Operation zu speichern
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        std::cerr << "Fehler beim erstellen des EVPs!" << std::endl;
        fclose(file);
        return nullptr;
    }
    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        std::cerr << "Fehler beim initialisieren des EVPs" << std::endl;
        fclose(file);
        EVP_MD_CTX_free(mdctx);
        return nullptr;
    }

    // Teilt Datei in 1024-Byte große Teile auf
    unsigned char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, 1024, file)) != 0) {
        // Updated den Hash mit neuem Teil
        if (1 != EVP_DigestUpdate(mdctx, buffer, bytes_read)) {
            std::cerr << "Fehler beim Updaten des Hashes!" << std::endl;
            fclose(file);
            EVP_MD_CTX_free(mdctx);
            return nullptr;
        }
    }

    // Beendet die Hash Funktion und gibt den Finalen Hash zurück
    unsigned char* md_value = new unsigned char[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    if (1 != EVP_DigestFinal_ex(mdctx, md_value, &md_len)) {
        std::cerr << "Fehler beim Finalisieren des Hashes!" << std::endl;
        fclose(file);
        EVP_MD_CTX_free(mdctx);
        delete[] md_value;
        return nullptr;
    }

    // Datei schließen
    fclose(file);
    EVP_MD_CTX_free(mdctx);

    return md_value;
}

// Funktion zum Hashen von 2 Hashes
const unsigned char* Hasher::hashTwoHashes(const unsigned char* hash1, const unsigned char* hash2){
    unsigned char combined[64];
    std::memcpy(combined, hash1, 32);
    std::memcpy(combined + 32, hash2, 32);

    // Initialisiert neuen Envelope Message Digest Context um Informationen zur Hash Operation zu speichern
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        std::cerr << "Fehler beim erstellen des EVPs!" << std::endl;
        return nullptr;
    }
    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        std::cerr << "Fehler beim initialisieren des EVPs" << std::endl;
        EVP_MD_CTX_free(mdctx);
        return nullptr;
    }

    // Hasht die beiden Hashes
    if (1 != EVP_DigestUpdate(mdctx, combined, 64)) {
        std::cerr << "Fehler beim Updaten des Hashes!" << std::endl;
        EVP_MD_CTX_free(mdctx);
        return nullptr;
    }

    // Beendet die Hash Funktion und gibt den Finalen Hash zurück
    unsigned char* md_value = new unsigned char[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    if (1 != EVP_DigestFinal_ex(mdctx, md_value, &md_len)) {
        std::cerr << "Fehler beim Finalisieren des Hashes!" << std::endl;
        EVP_MD_CTX_free(mdctx);
        delete[] md_value;
        return nullptr;
    }

    EVP_MD_CTX_free(mdctx);
    return md_value;
}

// Funktion die einen binären Hash zu einem String konvertiert
std::string Hasher::binaryToHex(const unsigned char* data, size_t length) {
    std::stringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; ++i) {
        hexStream << std::setw(2) << static_cast<int>(data[i]);
    }
    return hexStream.str();
};