#include"CDChunking.hpp"
#include"ToolChain.hpp"

using CDChunking::MainChunkProcessor;



MainChunkProcessor::MainChunkProcessor(ActionMode actionMode) :
    _actionMode(actionMode)
{
    if (actionMode & ActionMode::PrintToConsole) {
        _consolePrinter = std::make_shared<ConsolePrinter>();
    }
    else {
        _consolePrinter = nullptr;
    }
}

void 
MainChunkProcessor::operator() (std::shared_ptr<ChunkPackage> chunkPackage) {
    // {std::lock_guard lkh(HashCalculator::_hashMutex);
    //     HashCalculator h;
    //     h(chunkPackage);
    // }
    ThreadPool chunkActionPool(ToolChain::Builder::chunkProcessThreadNum);

    if (_actionMode & ActionMode::PrintToConsole) {
        chunkActionPool.enqueue_void(
            [_consolePrinter = this->_consolePrinter, chunkPackage]() {
                (*_consolePrinter)(chunkPackage);
            }
        );
    };
};