#include <iostream>
#include "../include/Parser.h"
#include "../include/FileScanner.h"
#include "../include/Duplicates.h"

int main(int argc, char** argv){
    try {
        Parser::Console config = Parser::parse(argc, argv);
        FileScanner Scaner(config);
        const auto& results = Scaner.scan();
        
        Duplicates duplicates(results, config);
        duplicates.find();

        duplicates.printDuplicates();
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what();
        return 0;
    }

}
