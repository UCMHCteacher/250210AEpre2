#include"StreamGenerator.hpp"





bool
StreamGenerators::FileStreamGenerator::isAlive() {
    return this->_alive;
}



StreamGenerators::FileStreamGenerator::FileStreamGenerator(std::string fileName) {
    this->_alive = true;
    this->_stream = std::make_unique<std::ifstream>(fileName, std::ios::in | std::ios::binary);
    if (!dynamic_cast<std::ifstream &>(*_stream).is_open()) {
        this->_alive = false;
    }
}

StreamGenerators::FileStreamGenerator::~FileStreamGenerator() {
    ;
}



std::unique_ptr<std::istream>
StreamGenerators::FileStreamGenerator::getStream() {
    return std::move(_stream);
}