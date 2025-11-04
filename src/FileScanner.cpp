#include "../include/FileScanner.h"

FileScanner::FileScanner(const Parser::Console& config) : config__(config) {}

bool FileScanner::bEx(const bf::path& dir){
    std::string path_str = dir.string();
    for (const auto& ex : config__.exclude_dirs) {
        if (path_str.find(ex) != std::string::npos)
            return true;
    }
    return false;
}

bool FileScanner::Mask(const bf::path& file) {
    if (config__.masks.empty())
        return true;
    std::string filename = file.filename().string();
    std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);

    for (const auto& mask : config__.masks) {
        std::string m = mask;
        std::transform(m.begin(), m.end(), m.begin(), ::tolower);

        std::string p;
        for (char c : m) {
            if (c == '*')
                p += ".*";
            else if (c == '?')
                p += ".";
            else
                p += c;
        }

        std::regex re(p);
        if (std::regex_match(filename, re))
            return true;
    }
    return false;
}

std::vector<bf::path> FileScanner::scan(){
    results__.clear();
    
    for (const auto& dir : config__.include_dirs) {
        bf::path path(dir);
        if (!bf::exists(path)) {
            std::cerr << "Directory " << dir << " -- doesn't exist\n";
            continue;
        }
        try {
            if (config__.recursive) {
                for (auto& p : bf::recursive_directory_iterator(path)) {
                    if (bf::is_directory(p) || bEx(p))
                        continue;
                    if (bf::is_regular_file(p) && bf::file_size(p) >= config__.min_size && Mask(p))
                        results__.push_back(p);
                }
            } else {
                for(auto& p : bf::directory_iterator(path)) {
                    if (bf::is_directory(p))
                        continue;
                    if (bf::is_regular_file(p) && bf::file_size(p) >= config__.min_size && Mask(p))
                        results__.push_back(p);
                }
            }
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
    return results__;
}