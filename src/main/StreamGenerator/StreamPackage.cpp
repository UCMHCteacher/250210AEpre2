#include"StreamGenerator.hpp"
#include"ToolChain.hpp"
#include"Summary.hpp"

#include<utility>


StreamPackage::StreamPackage(std::shared_ptr<std::istream> other): 
    _start{},
    _stream{other},
    _chunkCount{0},
    _streamSize{0},
    _streamNum{0}
{};




StreamPackage::~StreamPackage() {
    auto const  _finish = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> _duration = _finish - _start;
    // {std::lock_guard lk{ToolChain::_coutMutex};
    //     std::cout 
    //         << "Survived for " << _duration.count() << "ms.\n"
    //         << "ChunkCount: " << _chunkCount << "\n"
    //         << "StreamSize: " << _streamSize << "\n\n";
    // }

    if (Summary::needed) {
        std::lock_guard lk{Summary::efficiencyDataMutex};
        Summary::efficiencyData.emplace_back(
            Summary::EfficiencyRecord{
                this->_streamNum,
                this->_streamSize,
                this->_chunkCount,
                _duration
            }
        );
    }
}



void
StreamPackage::Setup() {
    _start = std::chrono::steady_clock::now();
    _streamNum = ToolChain::streamCount;
    ToolChain::streamCount++;
}