#include "../include/FileHash.h"

FileHash::FileHash(Parser::HashAlgorithm alg) : algorithm__(alg) {}

std::size_t FileHash::hashBlockCRC32(const std::vector<char>& buffer, std::streamsize bytes_read) {
    return crc32(0L, reinterpret_cast<const unsigned char*>(buffer.data()), static_cast<uInt>(bytes_read));
}

std::size_t FileHash::hashBlockMD5(const std::vector<char>& buffer, std::streamsize bytes_read) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(buffer.data()), static_cast<size_t>(bytes_read), digest);

    std::size_t hash_val = 0;
    for (int i = 0; i < 8 && i < MD5_DIGEST_LENGTH; ++i)
        hash_val = (hash_val << 8) | digest[i];

    return hash_val;
}
