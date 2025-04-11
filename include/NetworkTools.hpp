#pragma once

#include<string>
#include<vector>
#include<iostream>


#include<pcap.h>














typedef struct NetworkNode {
	in_addr networkAddr;
	in_addr networkMask;

	in_addr deviceIPAddr;

	char* deviceName;
	char* deviceDescription;


	NetworkNode();
	NetworkNode(const NetworkNode &);
}NetworkNode;
typedef std::vector<NetworkNode> NetworkList;


extern NetworkList networkList;

extern bool getNetworkList(NetworkList& networkList, std::string& errorbuf);

extern void PrintNetworkList(int indentCount);