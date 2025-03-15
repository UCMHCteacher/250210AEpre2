#include"CDChunking.hpp"
#include"ToolChain.hpp"



using namespace CDChunking;



void AE::chunk(std::shared_ptr<std::istream> stream) {
    uint32_t thisStreamNum;
    {
        std::lock_guard lk(_streamCountMutex);
        thisStreamNum = _streamCount;
        _streamCount++;
    }
    ThreadPool chunkProcessPool(ToolChain::Builder::chunkProcessThreadNum);


    std::size_t nowPos = -1;
    uint8_t nowData;
    
    uint32_t chunkNum = 0;
    std::vector<uint8_t> chunkData;
    std::size_t chunkBeginPos = 0;

    uint8_t maxValue = stream->peek();
    std::size_t maxPos = 0;

    while (nowData = stream->get(),!stream->eof()) {
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
            maxValue = stream->peek();
            maxPos = nowPos + 1;
            chunkBeginPos = nowPos + 1;
        }
        
        
        
        
        
    };

    if (chunkData.size() == 0) {
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
}



AE::AE(uint8_t intervalLength, uint16_t windowWidth): 
    _intervalLength(intervalLength),
    _windowWidth(windowWidth)
{
    _chunkProcessor = nullptr;
    _streamCount = 0;
}
AE::~AE() {}