#pragma once

#include"CDChunking.hpp"










namespace ToolChain {
    // extern streamGenerator
    extern CDChunking::Chunker *  chunker;
    // extern chunkProcessor





    namespace Builder {
        enum class ChunkerType {
            AE,
            MaxP
        };
        extern ChunkerType chunkerType;



        extern void Start();
    } // namespace Builder



    extern void StartProcess();
} // namespace ToolChain



