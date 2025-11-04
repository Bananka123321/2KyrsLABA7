#include "../include/Parser.h"

namespace bp = boost::program_options;

Parser::Console Parser::parse(int argc, char** argv){
    Parser::Console config;
    bp::variables_map vm;

    bp::options_description desc("Options");
    desc.add_options()
        ("help,h", "Show help message")
        ("dir,d", bp::value<std::vector<std::string>>()->multitoken())
        ("exclude,e", bp::value<std::vector<std::string>>()->multitoken())
        ("recursive,r", bp::value<int>()->default_value(1))
        ("block-size,s", bp::value<size_t>()->default_value(4096))
        ("mask,m", bp::value<std::vector<std::string>>()->multitoken())
        ("min-size", bp::value<size_t>()->default_value(0))
        ("alg,a", bp::value<int>()->default_value(1));

    try {
        bp::store(bp::parse_command_line(argc, argv, desc), vm);
        bp::notify(vm);
    } catch (const std::exception& ex) {
        std::cerr << "Error parsing command line: " << ex.what() << "\n";
        throw;
    }

    if (vm.count("help")) {
        std::cout << desc << "\n";
        throw std::runtime_error("help");
    }

    if (vm.count("dir"))
        config.include_dirs = vm["dir"].as<std::vector<std::string>>();

    if (vm.count("exclude"))
        config.exclude_dirs = vm["exclude"].as<std::vector<std::string>>();

    if (vm.count("mask"))
        config.masks = vm["mask"].as<std::vector<std::string>>();
    
    config.recursive = vm["recursive"].as<int>() != 0;
    config.block_size = vm["block-size"].as<size_t>();
    config.min_size = vm["min-size"].as<size_t>();

    switch (vm["alg"].as<int>()) {
        case 0: config.algorithm = HashAlgorithm::CRC32;
            break;
        case 1: config.algorithm = HashAlgorithm::MD5;
            break;
        default:
            throw std::invalid_argument("Invalid algorithm. Use 0 for CRC32, 1 for MD5.");
    }
    
    if (config.block_size == 0) {
        throw std::invalid_argument("block-size must be > 0");
    }

    return config;
}