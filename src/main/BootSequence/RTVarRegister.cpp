#include"BootSequenceList.hpp"
#include"ArgumentHandler.hpp"
#include"ToolChain.hpp"

#include<sstream>


using namespace ArgumentHandler;


void RTVarRegister() {
    // ArgumentHandler::RTVar::Param::Register(
    //     "Test",
    //     [](std::string & valueStr) {
    //         std::cout << valueStr << '\n';
    //     },
    //     "<String>",
    //     "Just A Test"
    // );

    ArgumentHandler::RTVar::Param::Register(
        "SourceType",
        [](std::string & valueStr) {
            if (
                ArgStringHash(valueStr) ==
                ArgStringHash("File")
            ) {
                ToolChain::Builder::sourceType =
                    ToolChain::Builder::SourceType::File;
            }
            else if (
                ArgStringHash(valueStr) == 
                ArgStringHash("Network")
            ) {
                ToolChain::Builder::sourceType =
                    ToolChain::Builder::SourceType::Network;
                ToolChain::Builder::chunkProcessorActionMode = 
                    static_cast<CDChunking::MainChunkProcessor::ActionMode>(
                    ToolChain::Builder::chunkProcessorActionMode &
                    (~CDChunking::MainChunkProcessor::ActionMode::RecordToDataBase));
            }
            else {
                std::cout << "There's no SourceType called " << valueStr << "\n";
            }
        },
        "<File|Network>",
        "Contorls Data Source Type"
    );

    ArgumentHandler::RTVar::Param::Register(
        "SourceFileName",
        [](std::string & valueStr) {
            ToolChain::Builder::sourceFileName = valueStr;
        },
        "<filename(string_with_no_spaces)>",
        ""
    );

    ArgumentHandler::RTVar::Param::Register(
        "NetworkNum",
        [](std::string & valueStr) {
            ToolChain::Builder::networkNum =
                atoi(valueStr.c_str());
        },
        "<networkNum(int)>",
        ""
    );

    ArgumentHandler::RTVar::Param::Register(
        "ChunkerType",
        [](std::string & valueStr) {
            if (
                ArgStringHash(valueStr) ==
                ArgStringHash("AE")
            ) {
                ToolChain::Builder::chunkerType =
                    ToolChain::Builder::ChunkerType::AE;
            }
            else {
                std::cout << "There's no ChunkerType called " << valueStr << "\n";
            }
        },
        "<AE>",
        ""
    );

    ArgumentHandler::RTVar::Param::Register(
        "ChunkerIntervalLength",
        [](std::string & valueStr) {
            int value = atoi(valueStr.c_str());
            if (value == 0) {
                std::cout << "ChunkIntervalLength cannot be 0 or not number.\n";
                return;
            }

            ToolChain::Builder::chunkerIntervalLength = value;
        },
        "<uint8>",
        "Still not functioning now :("
    );

    ArgumentHandler::RTVar::Param::Register(
        "ChunkerWindowWidth",
        [](std::string & valueStr) {
            int value = atoi(valueStr.c_str());
            if (value == 0) {
                std::cout << "ChunkerWindowWidth cannot be 0 or not number.\n";
                return;
            }

            ToolChain::Builder::chunkerWindowWidth = value;
        },
        "<uint16>",
        ""
    );
    ArgumentHandler::RTVar::Param::Register(
        "ChunkerThreadnum",
        [](std::string & valueStr) {
            int value = atoi(valueStr.c_str());
            if (value == 0) {
                std::cout << "ChunkerThreadnum cannot be 0 or not number.\n";
                return;
            }

            ToolChain::Builder::chunkerThreadnum = value;
        },
        "<uint8>",
        ""
    );
    ArgumentHandler::RTVar::Param::Register(
        "ChunkProcessorActionMode",
        [](std::string & valueStr) {
            ToolChain::Builder::chunkProcessorActionMode =
                CDChunking::MainChunkProcessor::ActionMode::Nothing;
            
            std::stringstream valueStream(valueStr);
            std::unique_ptr<char> p_SubStr = std::make_unique<char>(32);
            while (valueStream.getline(p_SubStr.get(), 31, '|')) {
                std::string subStr(p_SubStr.get());
                if (
                    ArgStringHash(subStr) ==
                    ArgStringHash("PrintToConsole")
                ) {
                    ToolChain::Builder::chunkProcessorActionMode = 
                        static_cast<CDChunking::MainChunkProcessor::ActionMode>(
                        ToolChain::Builder::chunkProcessorActionMode |
                        CDChunking::MainChunkProcessor::ActionMode::PrintToConsole);
                }
                else if (
                    ArgStringHash(subStr) ==
                    ArgStringHash("LogToFile")
                ) {
                    ToolChain::Builder::chunkProcessorActionMode = 
                        static_cast<CDChunking::MainChunkProcessor::ActionMode>(
                        ToolChain::Builder::chunkProcessorActionMode |
                        CDChunking::MainChunkProcessor::ActionMode::LogToFile);
                }
                else if (
                    ArgStringHash(subStr) ==
                    ArgStringHash("RecordToDataBase")
                    && 
                    ToolChain::Builder::sourceType !=
                    ToolChain::Builder::SourceType::Network
                ) {
                    ToolChain::Builder::chunkProcessorActionMode = 
                        static_cast<CDChunking::MainChunkProcessor::ActionMode>(
                        ToolChain::Builder::chunkProcessorActionMode |
                        CDChunking::MainChunkProcessor::ActionMode::RecordToDataBase);
                }
                else if (
                    ArgStringHash(subStr) ==
                    ArgStringHash("CompareWithDataBase")
                ) {
                    ToolChain::Builder::chunkProcessorActionMode = 
                        static_cast<CDChunking::MainChunkProcessor::ActionMode>(
                        ToolChain::Builder::chunkProcessorActionMode |
                        CDChunking::MainChunkProcessor::ActionMode::CompareWithDataBase);
                }
                else {
                    std::cout << "There's no ActionMode called " << valueStr << "\n";
                }

                // else if (
                //     ArgStringHash(subStr) ==
                //     ArgStringHash("SendToNetwork")
                // ) {
                //     ToolChain::Builder::chunkProcessorActionMode = 
                //     static_cast<CDChunking::MainChunkProcessor::ActionMode>(
                //         ToolChain::Builder::chunkProcessorActionMode |
                //         CDChunking::MainChunkProcessor::ActionMode::SendToNetwork) ;
                // }
                // else if (
                //     ArgStringHash(subStr) ==
                //     ArgStringHash("")
                // ) {
                //     ToolChain::Builder::chunkProcessorActionMode = 
                //         static_cast<CDChunking::MainChunkProcessor::ActionMode>(
                //         ToolChain::Builder::chunkProcessorActionMode |
                //         CDChunking::MainChunkProcessor::ActionMode::);
                // }
            }
            ;
        },
        "<Nothing|PrintToConsole|LogToFile|RecordToDataBase|CompareWithDataBase>",
        ""
    );
}