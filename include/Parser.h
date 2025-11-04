#pragma once
#include <iostream>
#include <vector>
#include <boost/program_options.hpp>

class Parser{
public:
    enum class HashAlgorithm {
        CRC32,
        MD5
    };

    struct Console{
        std::vector<std::string> include_dirs;
        std::vector<std::string> exclude_dirs;
        std::vector<std::string> masks;
        size_t block_size;
        size_t min_size;
        bool recursive;
        HashAlgorithm algorithm;
    };

    static Console parse(int argc, char** argv);
};