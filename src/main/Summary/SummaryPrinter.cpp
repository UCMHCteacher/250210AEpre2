#include"Summary.hpp"

#include<fstream>



void 
Summary::Printer() {
    std::fstream summaryFile {outputPath, std::ios::app|std::ios::out};
    summaryFile << "Yesssss!\n";


    std::exit(EXIT_SUCCESS);
}