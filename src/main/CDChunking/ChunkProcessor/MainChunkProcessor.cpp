#include"CDChunking.hpp"
#include"ToolChain.hpp"

using CDChunking::MainChunkProcessor;



MainChunkProcessor::MainChunkProcessor(ActionMode actionMode) :
    _actionMode(actionMode)
{
    if (actionMode & ActionMode::PrintToConsole) {
        _processors.push_back(std::make_shared<ConsolePrinter>());
    }
    // if (actionMode & ActionMode::LogToFile) {
    //     _processors.push_back(std::make_shared<Logger>());
    // }
    if (actionMode & ActionMode::RecordToDataBase) {
        _processors.push_back(std::make_shared<DatabaseRecorder>());
    }
    if (actionMode & ActionMode::CompareWithDataBase) {
        _processors.push_back(std::make_shared<DatabaseComparer>());
    }
}

void 
MainChunkProcessor::operator() (std::shared_ptr<ChunkPackage> chunkPackage) {
    {std::lock_guard lkh(HashCalculator::_hashMutex);
        HashCalculator h;
        h(chunkPackage);
    }
    ThreadPool chunkActionPool(ToolChain::Builder::chunkProcessThreadNum);

    for (auto &  _processor : _processors) {
        chunkActionPool.enqueue_void(
            [processor = _processor, chunkPackage]() {
                (*processor)(chunkPackage);
            }
        );
    }
};