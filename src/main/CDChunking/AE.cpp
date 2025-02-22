#include"CDChunking.hpp"



using namespace CDChunking;



void AE::chunk(std::shared_ptr<std::istream> stream) { // TODO: renames
    std::size_t nowPos = -1;
    uint8_t data;
    
    int chunkNum = 0;
    std::vector<uint8_t> chunk;
    std::size_t chunkBeginPos = 0;

    uint8_t maxValue = stream->peek();
    std::size_t maxPos = 0;

    while (data = stream->get(),!stream->eof()) {
        nowPos++;
        chunk.push_back(data);

        if (data > maxValue) {
            maxValue = data;
            maxPos = nowPos;
            continue;
        }



        if (nowPos - maxPos == _windowWidth) {
            // cout<< "Chunk Number: " << chunkNum << " {\n"
            // << "\tBegin Position: " << chunkBeginPos << "\n"
            // << "\tEnd Posotion: " << nowPos << "\n"
            // << "\tChunk Length: " << chunk.size() << "\n"
            // << "}\n\n";
            // 

            // next chunk 
            chunk = {};
            chunkNum ++;
            maxValue = stream->peek();
            maxPos = nowPos + 1;
            chunkBeginPos = nowPos + 1;
        }
        
        
        
        
        
    };
    // cout<< "Chunk Number: " << chunkNum << " {\n"
    //     << "\tBegin Position: " << chunkBeginPos << "\n"
    //     << "\tEnd Posotion: " << nowPos << "\n"
    //     << "\tChunk Length: " << chunk.size() << "\n"
    //     << "}\n\n";
}



AE::AE(uint8_t intervalLength, uint16_t windowWidth): 
    _intervalLength(intervalLength),
    _windowWidth(windowWidth)
{}
AE::~AE() {}