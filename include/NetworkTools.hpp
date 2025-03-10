#pragma once

#include<string>
#include<vector>
#include<iostream>

#include<WinSock2.h>
#include<conio.h>
#include<ntddndis.h>

#include<pcap.h>






constexpr int MACAddrLen = 6;
typedef BYTE mac_addr[MACAddrLen];
typedef BYTE MAC_ADDR[MACAddrLen];


constexpr int MACAddrStringLen = 18;

extern const char* const macAddrtoString(const mac_addr& macAddr);


extern bool getMacFromPcapDeviceName(const char* const name, mac_addr& mac, std::string& errorbuf);







typedef struct NetworkNode {
	in_addr networkAddr;
	in_addr networkMask;

	in_addr deviceIPAddr;
	mac_addr deviceMACAddr;

	char* deviceName;
	char* deviceDescription;

	// bool open;
	pcap_t * deviceHandle;

	NetworkNode();
	NetworkNode(const NetworkNode &);
}NetworkNode;
typedef std::vector<NetworkNode> NetworkList;


extern NetworkList networkList;

extern bool getNetworkList(NetworkList& networkList, std::string& errorbuf);

extern void printNetworkList(NetworkList& networkList);