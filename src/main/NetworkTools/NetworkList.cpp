#include"NetworkTools.hpp"





NetworkList networkList;




NetworkNode::NetworkNode() {
	networkAddr.S_un.S_addr=0;
	networkMask.S_un.S_addr=0;

	deviceIPAddr.S_un.S_addr=0;
	memset(deviceMACAddr, 0, MACAddrLen);

	deviceName=nullptr;
	deviceDescription=nullptr;

	// open=false;
	deviceHandle=nullptr;
}

NetworkNode::NetworkNode(const NetworkNode& rNode) {
	networkAddr.S_un.S_addr = rNode.networkAddr.S_un.S_addr;
	networkMask.S_un.S_addr = rNode.networkMask.S_un.S_addr;

	deviceIPAddr.S_un.S_addr = rNode.deviceIPAddr.S_un.S_addr;
	memcpy(deviceMACAddr, rNode.deviceMACAddr, MACAddrLen);

	deviceName = new char[strlen(rNode.deviceName) + 1];
		strcpy(deviceName, rNode.deviceName);
	deviceDescription = new char[strlen(rNode.deviceDescription) + 1];
		strcpy(deviceDescription, rNode.deviceDescription);

	// open = rNode.open;
	deviceHandle = rNode.deviceHandle;
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
		) == -1
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
					// networktoWrite.open = false;

					networktoWrite.deviceIPAddr = ((sockaddr_in*)(deviceAddr->addr))->sin_addr;

					networktoWrite.networkMask = ((sockaddr_in*)(deviceAddr->netmask))->sin_addr;
					networktoWrite.networkAddr.S_un.S_addr =
						networktoWrite.deviceIPAddr.S_un.S_addr &
						networktoWrite.networkMask.S_un.S_addr;

					networktoWrite.deviceName = new char[strlen(device->name)+1];
						strcpy(networktoWrite.deviceName, device->name);
					networktoWrite.deviceDescription=new char[strlen(device->description) + 1];
						strcpy(networktoWrite.deviceDescription, device->description);
					networktoWrite.deviceHandle = nullptr;
					std::string getMACErrorBuf;
					if (!getMacFromPcapDeviceName(
						device->name,
						networktoWrite.deviceMACAddr,
						getMACErrorBuf)) {
						std::cout << "Error occured in getting mac address of network \"" << inet_ntoa(networktoWrite.networkAddr) << "\".\n"
							<< "Error: " << getMACErrorBuf << "\n\n";
					}


					networkList.push_back(networktoWrite);
			}
		}
	}


	pcap_freealldevs(deviceList);

	return true;
}








void printNetworkList(NetworkList& networkList) {
	std::cout << "NetworkList: {\n";


	for (int i = 0; i < networkList.size();i++) {
		std::cout << "\tNetwork" << i << ": {\n";
		std::cout << "\t\tNetwork Address: \"" << inet_ntoa(networkList[i].networkAddr) << "\"\n";
		std::cout << "\t\tNetwork Mask: \"" << inet_ntoa(networkList[i].networkMask) << "\"\n";
		std::cout << "\t\tDevice IP Address: \"" << inet_ntoa(networkList[i].deviceIPAddr) << "\"\n"
			<< "\t\tDevice MAC Address: \"" << macAddrtoString(networkList[i].deviceMACAddr) << "\"\n"
			<< "\t\tDevice Name: \"" << networkList[i].deviceName << "\"\n"
			<< "\t\tDevice Description: \"" << networkList[i].deviceDescription << "\"\n"
			<< "\t},\n\n";
	}

	std::cout << "}\n\n\n";
}