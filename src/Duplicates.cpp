#include "../include/Duplicates.h"
#include <fstream>
#include <boost/functional/hash.hpp>

Duplicates::Duplicates(const std::vector<bf::path>& files, const Parser::Console& config) : files__(files), config__(config) {}

bool Duplicates::bEqual(const bf::path& file1, const bf::path& file2) {
    if (bf::file_size(file1) != bf::file_size(file2))
        return false;

    std::ifstream f1(file1.string(), std::ios::binary);
    std::ifstream f2(file2.string(), std::ios::binary);

    std::vector<char> buffer1(config__.block_size, 0);
    std::vector<char> buffer2(config__.block_size, 0);

    FileHash hasher(config__.algorithm);

    while (true) {
        f1.read(buffer1.data(), static_cast<std::streamsize>(buffer1.size()));
        f2.read(buffer2.data(), static_cast<std::streamsize>(buffer2.size()));

        std::streamsize bytes_read1 = f1.gcount();
        std::streamsize bytes_read2 = f2.gcount();

        if (bytes_read1 != bytes_read2)
            return false;

        if (bytes_read1 == 0)
            break;

            std::size_t hash1;
            std::size_t hash2;

            if (config__.algorithm == Parser::HashAlgorithm::MD5) {
                hash1 = hasher.hashBlockMD5(buffer1, bytes_read1);
                hash2 = hasher.hashBlockMD5(buffer2, bytes_read2);
            }

            hash1 = hasher.hashBlockCRC32(buffer1, bytes_read1);
            hash2 = hasher.hashBlockCRC32(buffer2, bytes_read2);

        if (hash1 != hash2)
            return false;
    }

    return true;
}


void Duplicates::find() {
    duplicates__.clear();

    std::unordered_map<uintmax_t, std::vector<bf::path>> size_map;
    for (const auto& f : files__)
        size_map[bf::file_size(f)].push_back(f);

    for (const auto& [size, group] : size_map) {
        if (group.size() < 2) continue;

        std::vector<bool> checked(group.size(), false);

        for (size_t i = 0; i < group.size(); ++i) {
            std::vector<bf::path> dup_group{group[i]};
            for (size_t j = i + 1; j < group.size(); ++j) {
                if (checked[j]) continue;

                if (bEqual(group[i], group[j])) {
                    dup_group.push_back(group[j]);
                    checked[j] = true;
                }
            }

            if (dup_group.size() > 1)
                duplicates__.push_back(dup_group);
        }
    }
}

void Duplicates::printDuplicates() const {
    if (duplicates__.empty()) {
        std::cout << "No duplicates found.\n";
        return;
    }

    std::cout << "Found duplicates:\n";
    for (const auto& group : duplicates__) {
        std::cout << "Group:\n";
        for (const auto& file : group)
            std::cout << "  " << file.string() << "\n";
        std::cout << "\n";
    }
}