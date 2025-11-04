#pragma once
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <zlib.h>
#include <openssl/evp.h>
#include "Parser.h"

namespace bf = boost::filesystem;

class FileHash {
public:
    explicit FileHash(Parser::HashAlgorithm alg);

    std::size_t hashBlockCRC32(const std::vector<char>& buffer, std::streamsize bytes_read);
    std::size_t hashBlockMD5(const std::vector<char>& buffer, std::streamsize bytes_read);

private:
    Parser::HashAlgorithm algorithm__;

};
