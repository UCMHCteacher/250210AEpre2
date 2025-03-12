#include"StreamGenerator.hpp"








StreamGenerators::FileStreamGenerator::FileStreamGenerator(std::string fileName) :
    _fileName(fileName),
    _used(false)
{}

StreamGenerators::FileStreamGenerator::~FileStreamGenerator() {}



std::shared_ptr<std::istream>
StreamGenerators::FileStreamGenerator::getStream() {
    if (_used) return nullptr;

    std::shared_ptr<std::istream> stream = std::make_shared<std::ifstream>(_fileName, std::ios::in | std::ios::binary);
    _used = true;
    return stream ? stream : nullptr;
}