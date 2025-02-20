#pragma once

#include<iostream>
#include<memory>




namespace CDChunking {



    // base class
    class Chunker
    {
    protected:
    public:
        virtual void chunk(std::unique_ptr<std::istream> stream) = 0;
    };



    class AE: 
        public Chunker
    {
    protected:
        uint8_t _intervalLength;
        uint16_t _windowWidth;

    public:
        virtual void chunk(std::unique_ptr<std::istream> stream) override;
    
    public:
        AE(uint8_t intervalLength, uint16_t windowWidth);
        ~AE();
    };



    class MaxP: 
        public Chunker 
    {
    public:
        virtual void chunk(std::unique_ptr<std::istream> stream) override;
    };



} // namespace CDChunking
