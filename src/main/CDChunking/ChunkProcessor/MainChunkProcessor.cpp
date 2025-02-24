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
    if (_actionMode & ActionMode::PrintToConsole) {
        ToolChain::chunkProcessPool.enqueue_void(
            [_consolePrinter = this->_consolePrinter, chunkPackage]() {
                (*_consolePrinter)(chunkPackage);
            }
        );
    };
};