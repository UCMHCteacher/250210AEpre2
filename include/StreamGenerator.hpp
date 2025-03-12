#pragma once

#include<iostream>
#include<memory>
#include<string>
#include<fstream>





namespace StreamGenerators
{
    class StreamGenerator {
    public:
        virtual std::shared_ptr<std::istream> getStream() = 0;
    };


    class FileStreamGenerator:
        public StreamGenerator
    {
    public:
        virtual std::shared_ptr<std::istream> getStream();

    protected:
        bool _used;

    protected:
        std::string _fileName;
    public:
        FileStreamGenerator(std::string fileName);
        virtual ~FileStreamGenerator();
    };


    class NetworkStreamGenerator:
        public StreamGenerator
    {
    public:
        virtual std::shared_ptr<std::istream> getStream();
    
    public:
        NetworkStreamGenerator(uint16_t networkNum);
        virtual ~NetworkStreamGenerator();
    };
} // namespace StreamGenerators
