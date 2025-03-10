// #include"BootSequenceList.hpp"
#include"NetworkTools.hpp"



void NetworkInit() {
    std::string getNetworkListErrBuf;
    if (
        !getNetworkList(networkList, getNetworkListErrBuf)
    ) {
        std::cout << getNetworkListErrBuf << "\n\n\n";
        return;
    }


    if (networkList.size() == 0) {
		std::cout << "Your computer is not connect to any network!\n"
			"Please check your network configuration!\n\n\n";
		return;
	}

    printNetworkList(networkList);
	std::cout << "There are " << networkList.size() << " networks in total.\n\n\n";
}