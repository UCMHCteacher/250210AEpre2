#pragma once

#include<iostream>
#include<memory>
#include<string>
#include<fstream>





namespace StreamGenerators
{
    class StreamGenerator {
    public:
        virtual bool isAlive() = 0;
    protected:
        bool _alive;

    public:
        virtual std::shared_ptr<std::istream> getStream() = 0;
    protected:
        std::shared_ptr<std::istream> _stream;
    };


    class FileStreamGenerator:
        public StreamGenerator
    {
    public:
        virtual bool isAlive();
        virtual std::shared_ptr<std::istream> getStream();

    public:
        FileStreamGenerator(std::string fileName);
        virtual ~FileStreamGenerator();
    };
} // namespace StreamGenerators
