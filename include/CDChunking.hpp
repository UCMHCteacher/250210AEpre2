#pragma once

#include<iostream>




namespace CDChunking {



    // base class
    class Chunker
    {
    protected:
    public:
        virtual void chunk() = 0;
    };



    class AE: 
        public Chunker
    {
    public:
        virtual void chunk() override;
    };



    class MaxP: 
        public Chunker 
    {
        public:
        virtual void chunk() override;
    };



} // namespace CDChunking
