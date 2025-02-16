#pragma once

#include<iostream>




namespace CDChunking {



    // base class
    class Chunker
    {
    protected:
    public:
        virtual void operator() () = 0;
    };



    class AE: 
        public Chunker
    {
    public:
        virtual void operator() () override;
    };



    class MaxP: 
        public Chunker 
    {
        public:
        virtual void operator() () override;
    };



} // namespace CDChunking
