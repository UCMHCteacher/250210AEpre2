#include"Summary.hpp"




bool
Summary::needed {false};

std::filesystem::path
Summary::outputPath {"./Summary.txt"};

std::filesystem::path
Summary::terminateSymbol {"./DaCoda"};




std::vector<Summary::EfficiencyRecord>
Summary::efficiencyData{};

std::mutex
Summary::efficiencyDataMutex{};




std::map<Summary::FileID_t,Summary::FileTime_t>
Summary::correctnessData{};

std::mutex
Summary::correctnessDataMutex{};