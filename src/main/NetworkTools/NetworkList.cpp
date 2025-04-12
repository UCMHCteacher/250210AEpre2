#include"NetworkTools.hpp"

#include<cstring>





NetworkList networkList;




NetworkNode::NetworkNode() :
	deviceName{},
	deviceDescription{}
{
#ifdef _WIN32
	networkAddr.S_un.S_addr=0;
	networkMask.S_un.S_addr=0;
	deviceIPAddr.S_un.S_addr=0;
#elif __linux__
	networkAddr.s_addr = 0;
	networkMask.s_addr = 0;
	deviceIPAddr.s_addr = 0;
#endif
}

NetworkNode::NetworkNode(const NetworkNode& rNode) {
	networkAddr = rNode.networkAddr;
	networkMask = rNode.networkMask;
	deviceIPAddr = rNode.deviceIPAddr;

	deviceName = rNode.deviceName;
	deviceDescription = rNode.deviceDescription;
}






bool getNetworkList(NetworkList& networkList, std::string& errorbuf) {
	pcap_if_t* deviceList;
	char pcapErrorBuffer[PCAP_ERRBUF_SIZE + 1];

	/*
	 * For listing local capture devices, it's just a wrapper around
	 * pcap_findalldevs(); code using pcap_findalldevs() will work on more
	 * platforms than code using pcap_findalldevs_ex().
	 */
	if (
		pcap_findalldevs(
			&deviceList,
			pcapErrorBuffer
		) == PCAP_ERROR
		) {
		errorbuf = "Failed in finding devices!\n" 
				   "Error message: ";
		errorbuf.append(pcapErrorBuffer);
		return false;
	}




	// add to network list if a device connected to a IPv4 network
	for (auto device = deviceList; device; device = device->next) {
		for (auto deviceAddr = device->addresses; deviceAddr; deviceAddr = deviceAddr->next) {
			if (deviceAddr->addr->sa_family == AF_INET) {
				NetworkNode networktoWrite;

					networktoWrite.deviceIPAddr = ((sockaddr_in*)(deviceAddr->addr))->sin_addr;
					networktoWrite.networkMask = ((sockaddr_in*)(deviceAddr->netmask))->sin_addr;

#ifdef _WIN32
					networktoWrite.networkAddr.S_un.S_addr =
						networktoWrite.deviceIPAddr.S_un.S_addr &
						networktoWrite.networkMask.S_un.S_addr;
#elif __linux__
					networktoWrite.networkAddr.s_addr =
						networktoWrite.deviceIPAddr.s_addr &
						networktoWrite.networkMask.s_addr;
#endif

					networktoWrite.deviceName = std::string(device->name);
					networktoWrite.deviceDescription = std::string(device->description);

					networkList.push_back(networktoWrite);
			}
		}
	}


	pcap_freealldevs(deviceList);

	return true;
}






extern std::string Indents(uint32_t count);
void PrintNetworkList(int indentCount) {
    std::cout << Indents(indentCount) << "NetworkList: {\n";
    
    
    for (int i = 0; i < networkList.size(); i++) {
        NetworkNode const & network = networkList[i];
        std::cout 
            << Indents(indentCount+1) << "Network" << i << ": {\n"
            << Indents(indentCount+2) << "Network Address: \"" << inet_ntoa(network.networkAddr) << "\"\n"
            << Indents(indentCount+2) << "Network Mask: \"" << inet_ntoa(network.networkMask) << "\"\n"
            << Indents(indentCount+2) << "Device IP Address: \"" << inet_ntoa(network.deviceIPAddr) << "\"\n"
            << Indents(indentCount+2) << "Device Name: \"" << network.deviceName << "\"\n"
            << Indents(indentCount+2) << "Device Description: \"" << network.deviceDescription << "\"\n"
            << Indents(indentCount+1) << "},\n";
    }

    std::cout << Indents(indentCount) << "}\n";
	std::cout << Indents(indentCount) << "There are " << networkList.size() << " networks in total.\n\n\n";
}