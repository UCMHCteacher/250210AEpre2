#pragma once

#include<iostream>
#include<memory>
#include<string>
#include<fstream>
#include<chrono>

#include<pcap.h>




struct StreamPackage {
public:
    std::chrono::time_point<std::chrono::steady_clock>  _start;
    std::shared_ptr<std::istream>  _stream;
    uint32_t  _chunkCount;
    std::size_t  _streamSize;
    uint32_t  _streamNum;

public:
    StreamPackage() = delete;
    StreamPackage(StreamPackage const &) = default;
    StreamPackage(StreamPackage &&) = default;
    StreamPackage(std::shared_ptr<std::istream> other);
    ~StreamPackage();

public:
    void Setup();
};



namespace StreamGenerators
{
    class StreamGenerator {
    public:
        virtual std::shared_ptr<StreamPackage> getStream() = 0;
    };



    class FileStreamGenerator:
        public StreamGenerator
    {
    public:
        virtual std::shared_ptr<StreamPackage> getStream();

    protected:
        bool _used;

    protected:
        std::string _filePath;
    public:
        FileStreamGenerator(std::string filePath);
        virtual ~FileStreamGenerator();
    };



    class NetworkStreamGenerator:
        public StreamGenerator
    {
    public:
        virtual std::shared_ptr<StreamPackage> getStream();
    
    protected:
        pcap_t * _deviceHandle;
        bool _enabled;
    public:
        NetworkStreamGenerator(uint16_t networkNum);
        virtual ~NetworkStreamGenerator();
    };
} // namespace StreamGenerators
