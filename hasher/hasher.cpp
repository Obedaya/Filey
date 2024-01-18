#include "../include/hasher.h"

Hasher::Hasher(Logger& logger) : logger(logger){
    OpenSSL_add_all_algorithms();
}

// Funktion zum hashen von Inhalt mit Dateinamen
const unsigned char* Hasher::getHashFile(const char *path) {
    const unsigned char* hashed_file_content = Hasher::hashFileContent(path);
    const unsigned char* hashed_file_path = Hasher::hashFilePath(path);

    return Hasher::hashTwoHashes(hashed_file_path, hashed_file_content);
}

// Funktion zum hashen von Dateinamen
const unsigned char* Hasher::hashFilePath(const char *path) {
    std::string path_string = std::string(path);

    // Initialisiert neuen Envelope Message Digest Context um Informationen zur Hash Operation zu speichern
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        logger.printAndLog("Fehler beim erstellen des EVPs!", true);
        return nullptr;
    }
    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr)) {
        logger.printAndLog("Fehler beim initialisieren des EVPs", true);
        EVP_MD_CTX_free(mdctx);
        return nullptr;
    }

    // Hasht den String
    if (1 != EVP_DigestUpdate(mdctx, path_string.c_str(), path_string.length())) {
        logger.printAndLog("Fehler beim erstellen des Hashes" , true);
        EVP_MD_CTX_free(mdctx);
        return nullptr;
    }

    // Beendet die Hash Funktion und gibt den Finalen Hash zurück
    auto* md_value = new unsigned char[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    if (1 != EVP_DigestFinal_ex(mdctx, md_value, &md_len)) {
        logger.printAndLog("Fehler beim Finalisieren des Hashes!" , true);
        EVP_MD_CTX_free(mdctx);
        delete[] md_value;
        return nullptr;
    }

    EVP_MD_CTX_free(mdctx);

    return md_value;
}

// Funktion die einen Datei Inhalt hasht
const unsigned char* Hasher::hashFileContent(const char *path) {
    // Datei öffnen
    FILE *file = fopen(path, "rb");
    if (!file) {
        logger.printAndLog("Fehler beim öffnen der Datei!" , true);
        return nullptr;
    }

    // Initialisiert neuen Envelope Message Digest Context um Informationen zur Hash Operation zu speichern
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        logger.printAndLog("Fehler beim erstellen des EVPs!", true);
        fclose(file);
        return nullptr;
    }
    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr)) {
        logger.printAndLog( "Fehler beim initialisieren des EVPs", true);
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
            logger.printAndLog("Fehler beim Updaten des Hashes!", true);
            fclose(file);
            EVP_MD_CTX_free(mdctx);
            return nullptr;
        }
    }

    // Beendet die Hash Funktion und gibt den Finalen Hash zurück
    auto* md_value = new unsigned char[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    if (1 != EVP_DigestFinal_ex(mdctx, md_value, &md_len)) {
        logger.printAndLog("Fehler beim Finalisieren des Hashes!" , true);
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
    unsigned char combined[HASH_SIZE * 2];
    std::memcpy(combined, hash1, HASH_SIZE);
    std::memcpy(combined + HASH_SIZE, hash2, HASH_SIZE);

    // Initialisiert neuen Envelope Message Digest Context um Informationen zur Hash Operation zu speichern
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        logger.printAndLog("Fehler beim erstellen des EVPs!", true);
        return nullptr;
    }
    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr)) {
        logger.printAndLog("Fehler beim initialisieren des EVPs", true);
        EVP_MD_CTX_free(mdctx);
        return nullptr;
    }

    // Hasht die beiden Hashes
    if (1 != EVP_DigestUpdate(mdctx, combined, 64)) {
        logger.printAndLog("Fehler beim Updaten des Hashes!", true);
        EVP_MD_CTX_free(mdctx);
        return nullptr;
    }

    // Beendet die Hash Funktion und gibt den Finalen Hash zurück
    auto* md_value = new unsigned char[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    if (1 != EVP_DigestFinal_ex(mdctx, md_value, &md_len)) {
        logger.printAndLog("Fehler beim Finalisieren des Hashes!" , true);
        EVP_MD_CTX_free(mdctx);
        delete[] md_value;
        return nullptr;
    }

    EVP_MD_CTX_free(mdctx);
    return md_value;
}

// Funktion die einen binären Hash zu einem String konvertiert
std::string Hasher::binaryToHex(const unsigned char* data, size_t length) {
    std::stringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; ++i) {
        hex_stream << std::setw(2) << static_cast<int>(data[i]);
    }
    return hex_stream.str();
}

