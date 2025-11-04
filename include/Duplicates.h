#pragma once
#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>
#include "Parser.h"
#include "FileHash.h"

namespace bf = boost::filesystem;

class Duplicates {
private:
    Parser::Console config__;
    std::vector<bf::path> files__;
    std::vector<std::vector<bf::path>> duplicates__;

    bool bEqual(const bf::path& file1, const bf::path& file2);

public:
    Duplicates(const std::vector<bf::path>& files, const Parser::Console& config);

    void find();
    void printDuplicates() const;
};