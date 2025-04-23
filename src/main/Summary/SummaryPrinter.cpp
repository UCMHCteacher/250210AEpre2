#include"Summary.hpp"
#include"ToolChain.hpp"

#include<fstream>


extern std::string Indents(uint32_t count);


void 
Summary::Printer() {
    std::fstream summaryFile {outputPath, std::ios::app|std::ios::out};


    /** "Efficiency" : [
     *      {
     *          "StreamNum" : <uint32_t>,
     *          "ChunkCount" : <uint32_t>,
     *          "TimeCost" : <double>
     *      },
     *      ...
     *  ]
     */
    {std::lock_guard lk{efficiencyDataMutex};
        summaryFile 
            << Indents(1) << "\"Efficiency\" : [\n";

        auto efficiencyIt = efficiencyData.begin();
        if (efficiencyIt != efficiencyData.end()) {
            summaryFile
                << Indents(2) << "{\n"
                << Indents(3) << "\"StreamNum\" : " << efficiencyIt->_streamNum << ",\n"
                << Indents(3) << "\"StreamSize\" : " << efficiencyIt->_streamSize << ",\n"
                << Indents(3) << "\"ChunkCount\" : " << efficiencyIt->_chunkCount << ",\n"
                << Indents(3) << "\"TimeCost\" : " << efficiencyIt->_duration.count() << "\n"
                << Indents(2) << "}";

            for (efficiencyIt++; efficiencyIt != efficiencyData.end(); efficiencyIt++) {
                summaryFile
                    << ",\n"
                    << Indents(2) << "{\n"
                    << Indents(3) << "\"StreamNum\" : " << efficiencyIt->_streamNum << ",\n"
                    << Indents(3) << "\"StreamSize\" : " << efficiencyIt->_streamSize << ",\n"
                    << Indents(3) << "\"ChunkCount\" : " << efficiencyIt->_chunkCount << ",\n"
                    << Indents(3) << "\"TimeCost\" : " << efficiencyIt->_duration.count() << "\n"
                    << Indents(2) << "}";
            }
        }

        summaryFile
            << "\n" << Indents(1) << "]";
    }



    /** "Correctness" : [
     *      {
     *          "FileID" : <uint32_t>,
     *          "Times" : <uint32_t>
     *      },
     *      ...
     *  ]
     */
    if (ToolChain::Builder::SourceType::Network == ToolChain::Builder::sourceType) {
        summaryFile << ",\n";


        std::lock_guard lk{correctnessDataMutex};
        summaryFile 
            << Indents(1) << "\"Correctness\" : [\n";

        auto correctnessIt = correctnessData.begin();
        if (correctnessIt != correctnessData.end()) {
            summaryFile
                << Indents(2) << "{\n"
                << Indents(3) << "\"FileID\" : " << correctnessIt->first << ",\n"
                << Indents(3) << "\"Times\" : " << correctnessIt->second << "\n"
                << Indents(2) << "}";

            for (correctnessIt++; correctnessIt != correctnessData.end(); correctnessIt++) {
                summaryFile
                    << ",\n"
                    << Indents(2) << "{\n"
                    << Indents(3) << "\"FileID\" : " << correctnessIt->first << ",\n"
                    << Indents(3) << "\"Times\" : " << correctnessIt->second << "\n"
                    << Indents(2) << "}";
            }
        }

        summaryFile
            << "\n" << Indents(1) << "]";
    }

    summaryFile << "\n}";
    summaryFile.close();


    std::exit(EXIT_SUCCESS);
}