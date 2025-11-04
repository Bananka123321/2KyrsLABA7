#include "../include/FileHash.h"

FileHash::FileHash(Parser::HashAlgorithm alg) : algorithm__(alg) {}

std::size_t FileHash::hashBlockCRC32(const std::vector<char>& buffer, std::streamsize bytes_read) {
    return crc32(0L, reinterpret_cast<const unsigned char*>(buffer.data()), static_cast<uInt>(bytes_read));
}

std::size_t FileHash::hashBlockMD5(const std::vector<char>& buffer, std::streamsize bytes_read) {
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len;
    
    EVP_DigestInit_ex(context, EVP_md5(), nullptr);
    EVP_DigestUpdate(context, buffer.data(), bytes_read);
    EVP_DigestFinal_ex(context, digest, &digest_len);
    EVP_MD_CTX_free(context);

    std::size_t hash_val = 0;
    for (unsigned int i = 0; i < sizeof(std::size_t) && i < digest_len; ++i) {
        hash_val = (hash_val << 8) | digest[i];
    }

    return hash_val;
}