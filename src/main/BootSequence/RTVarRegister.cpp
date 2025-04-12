#include"BootSequenceList.hpp"
#include"ArgumentHandler.hpp"
#include"ToolChain.hpp"
#include"DataBaseTools.hpp"

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

    // ToolChain Part
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
        "SourceFilePath",
        [](std::string & valueStr) {
            ToolChain::Builder::sourceFilePath = valueStr;
        },
        "<filepath(string_with_no_spaces)>",
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
            char* p_SubStr = new char[32];
            while (valueStream.getline(p_SubStr, 31, ',')) {
                std::string subStr(p_SubStr);
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
            delete[] p_SubStr;
            // std::cout << "ActionMode = " << ToolChain::Builder::chunkProcessorActionMode << '\n';
        },
        "<Nothing|PrintToConsole|LogToFile|RecordToDataBase|CompareWithDataBase>",
        ""
    );



    // Database Part
    ArgumentHandler::RTVar::Param::Register(
        "DBAddress",
        [](std::string & valueStr) {
            DataBase::address = std::string("tcp://") + valueStr;
        },
        "<ip>:<port>",
        ""
    );
    ArgumentHandler::RTVar::Param::Register(
        "DBUserName",
        [](std::string & valueStr) {
            DataBase::username = valueStr;
        },
        "<String>",
        ""
    );
    ArgumentHandler::RTVar::Param::Register(
        "DBPassword",
        [](std::string & valueStr) {
            DataBase::password = valueStr;
        },
        "<String>",
        ""
    );
    ArgumentHandler::RTVar::Param::Register(
        "DBName",
        [](std::string & valueStr) {
            DataBase::dbname = valueStr;
        },
        "<String>",
        ""
    );
}