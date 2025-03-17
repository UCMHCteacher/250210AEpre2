#pragma once

#include<iostream>
#include<memory>
#include<vector>
#include<mutex>

#include<openssl/sha.h>
#include<openssl/ssl.h>
#include<openssl/err.h>





namespace CDChunking {
    struct ChunkPackage {
        uint32_t _streamNum;
        uint32_t _chunkNum;

        std::vector<uint8_t> _data;
        std::vector<uint8_t> _datahash;

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
            std::size_t chunkEndPos
        );
        ChunkPackage(const ChunkPackage &);
        ChunkPackage(ChunkPackage &&);
    };





    struct ChunkProcessInterface {
    public:
        virtual void operator() (std::shared_ptr<ChunkPackage> chunkPackage) = 0;
    };





    // base class
    class Chunker
    {
    protected:
        uint32_t _streamCount;
        std::mutex _streamCountMutex;

    protected:
        std::shared_ptr<ChunkProcessInterface> _chunkProcessor;
    public:
        void SetChunkProcessor(const std::shared_ptr<ChunkProcessInterface> &);
        std::shared_ptr<ChunkProcessInterface> GetChunkProcessor();

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





    // struct NetworkSender :
    //     public ChunkProcessInterface
    // {
    // public:
    //     virtual void operator() (std::shared_ptr<ChunkPackage> chunkPackage) override;
    // };



    struct HashCalculator :
        public ChunkProcessInterface
    {
    public:
        inline static std::mutex _hashMutex{};
    protected:
        EVP_MD_CTX * _ctx;
        EVP_MD *  _mdAlgo;
    protected:
        bool _usable;

    public:
        virtual void operator() (std::shared_ptr<ChunkPackage> chunkPackage) override;

    public:
        HashCalculator();
        HashCalculator(std::string const &  algoType);
        ~HashCalculator();
    };



    struct ConsolePrinter :
        public ChunkProcessInterface
    {
    public:
        virtual void operator() (std::shared_ptr<ChunkPackage> chunkPackage) override;
    };



    struct DatabaseRecorder :
        public ChunkProcessInterface
    {
    public:
        virtual void operator() (std::shared_ptr<ChunkPackage> chunkPackage) override;
        ;
    };



    struct DatabaseComparer :
        public ChunkProcessInterface
    {
    public:
        virtual void operator() (std::shared_ptr<ChunkPackage> chunkPackage) override;
        ;
    };



    struct MainChunkProcessor :
        public ChunkProcessInterface
    {
    public:
        enum ActionMode : uint32_t {
            Nothing             = 0,
            PrintToConsole      = 1UL << 0,
            LogToFile           = 1UL << 1,
            RecordToDataBase    = 1UL << 2,
            CompareWithDataBase = 1UL << 3,
            // SendToNetwork       = 1UL << 4,
        };
    protected:
        ActionMode _actionMode;
        std::vector<std::shared_ptr<ChunkProcessInterface>> _processors;

    public:
        void operator() (std::shared_ptr<ChunkPackage> chunkPackage) override;

    public:
        MainChunkProcessor(ActionMode actionMode);
    };

} // namespace CDChunking
