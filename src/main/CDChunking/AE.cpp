#include"CDChunking.hpp"



using namespace CDChunking;



void AE::chunk(std::shared_ptr<std::istream> stream) {
    ; // TODO: AE Algo
}



AE::AE(uint8_t intervalLength, uint16_t windowWidth): 
    _intervalLength(intervalLength),
    _windowWidth(windowWidth)
{}
AE::~AE() {}