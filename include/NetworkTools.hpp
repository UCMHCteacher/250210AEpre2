#pragma once

#include<string>
#include<vector>
#include<iostream>


#include<pcap.h>


#ifdef __linux__
#include<arpa/inet.h>
#endif











typedef struct NetworkNode {
	in_addr networkAddr;
	in_addr networkMask;

	in_addr deviceIPAddr;

	std::string deviceName;
	std::string deviceDescription;


	NetworkNode();
	NetworkNode(const NetworkNode &);
}NetworkNode;
typedef std::vector<NetworkNode> NetworkList;


extern NetworkList networkList;

extern bool getNetworkList(NetworkList& networkList, std::string& errorbuf);

extern void PrintNetworkList(int indentCount);