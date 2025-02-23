#pragma once

#include<iostream>
#include<memory>
#include<vector>
#include<mutex>





namespace CDChunking {



    // base class
    class Chunker
    {
    protected:
        uint32_t _streamCount;
        std::mutex _streamCountMutex;

    public:
        virtual void chunk(std::shared_ptr<std::istream> stream) = 0;
    };



    class AE: 
        public Chunker
    {
    protected:
        uint8_t _intervalLength;
        uint16_t _windowWidth;

    public:
        virtual void chunk(std::shared_ptr<std::istream> stream) override;
    
    public:
        AE(uint8_t intervalLength, uint16_t windowWidth);
        ~AE();
    };



    class MaxP: 
        public Chunker 
    {
    public:
        virtual void chunk(std::shared_ptr<std::istream> stream) override;
    };





    struct ChunkPackage {
        uint32_t _streamNum;
        uint32_t _chunkNum;
        std::vector<uint8_t> _data;

        // data includes [beginPos, endPos].
        // so size = endPos - beginPos + 1;
        std::size_t _beginPos;
        std::size_t _endPos;
        std::size_t _chunkSize;


        ChunkPackage(
            uint32_t streamNum, 
            uint32_t chunkNum, 
            std::vector<uint8_t> && chunkData, 
            std::size_t chunkBeginPos,
            std::size_t chunkEndPos,
            std::size_t chunkSize
        );
        ChunkPackage(const ChunkPackage &);
        ChunkPackage(ChunkPackage &&);
    };





    struct ChunkProcessor {
    public:
        enum ActionMode : uint32_t {
            PrintToConsole = 1UL << 0,
            LogToFile = 1UL << 1,
            RecordIntoDataBase = 1UL << 2,
            SendToNetwork = 1UL << 3,
        };
    protected:
        ActionMode actionMode;

    
    public:
        void operator() (std::shared_ptr<ChunkPackage>);

        ChunkProcessor();
        ChunkProcessor();
    };

} // namespace CDChunking
