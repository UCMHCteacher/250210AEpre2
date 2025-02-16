#pragma once

#include"CDChunking.hpp"





enum class ChunkerType {
    AE,
    MaxP
};

extern void ToolChainBuilder();

extern CDChunking::Chunker *  chunker;