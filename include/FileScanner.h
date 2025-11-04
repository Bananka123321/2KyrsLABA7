#pragma once
#include <boost/filesystem.hpp>
#include "Parser.h"
#include <regex>

namespace bf = boost::filesystem;

class FileScanner{
public:
    FileScanner(const Parser::Console& config);
    std::vector<bf::path> scan();

private:
    const Parser::Console& config__;
    std::vector<bf::path> results__;
    
    bool Mask(const bf::path& file);
    bool bEx(const bf::path& dir);
};