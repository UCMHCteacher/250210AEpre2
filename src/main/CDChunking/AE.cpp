#include"CDChunking.hpp"
#include"ToolChain.hpp"
#include"StreamGenerator.hpp"



using namespace CDChunking;



void AE::chunk(std::shared_ptr<StreamPackage> streamPackage) {
    uint32_t thisStreamNum = streamPackage->_streamNum;

    ThreadPool chunkProcessPool(ToolChain::Builder::chunkProcessThreadNum);

    std::istream &  stream{*(streamPackage->_stream)};


    std::size_t nowPos = -1;
    uint8_t nowData;
    
    uint32_t chunkNum = 0;
    std::vector<uint8_t> chunkData;
    std::size_t chunkBeginPos = 0;

    uint8_t maxValue = stream.peek();
    std::size_t maxPos = 0;

    while (nowData = stream.get(),!stream.eof()) {
        nowPos++;
        chunkData.push_back(nowData);

        if (nowData > maxValue) {
            maxValue = nowData;
            maxPos = nowPos;
            continue;
        }



        if (nowPos - maxPos == _windowWidth) {
            std::shared_ptr<ChunkPackage> package = std::make_shared<ChunkPackage>(
                thisStreamNum,
                chunkNum,
                std::move(chunkData),
                chunkBeginPos,
                nowPos
            );
            chunkProcessPool.enqueue_void(
                [chunkProcessor = this->_chunkProcessor, package]() {
                    (*chunkProcessor)(package);
                }
            );

            // next chunk 
            chunkData = {};
            chunkNum ++;
            maxValue = stream.peek();
            maxPos = nowPos + 1;
            chunkBeginPos = nowPos + 1;
        }
        
        
        
        
        
    };
    streamPackage->_streamSize = nowPos + 1;

    if (chunkData.size() == 0) {
        streamPackage->_chunkCount = chunkNum;
        return;
    }
    std::shared_ptr<ChunkPackage> package = std::make_shared<ChunkPackage>(
        thisStreamNum,
        chunkNum,
        std::move(chunkData),
        chunkBeginPos,
        nowPos
    );
    chunkProcessPool.enqueue_void(
        [chunkProcessor = this->_chunkProcessor, package]() {
            (*chunkProcessor)(package);
        }
    );
    streamPackage->_chunkCount = chunkNum + 1;
}



AE::AE(uint8_t intervalLength, uint16_t windowWidth): 
    _intervalLength(intervalLength),
    _windowWidth(windowWidth)
{
    _chunkProcessor = nullptr;
}
AE::~AE() {}