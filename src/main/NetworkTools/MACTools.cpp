#include<Packet32.h>

#include"NetworkTools.hpp"



const char* const macAddrtoString(const mac_addr& macAddr) {
	static char macAddrStr[MACAddrStringLen];
	sprintf_s(
		macAddrStr,
		"%02x-%02x-%02x-%02x-%02x-%02x",
		macAddr[0],
		macAddr[1],
		macAddr[2],
		macAddr[3],
		macAddr[4],
		macAddr[5]
	);
	return macAddrStr;
}



bool getMacFromPcapDeviceName(const char *const name, mac_addr& mac, std::string& errorbuf) {
    LPADAPTER	lpAdapter = 0;
    PPACKET_OID_DATA  OidData=nullptr;
    BOOLEAN     Status;



    lpAdapter = PacketOpenAdapter(name);
    if (!lpAdapter || (lpAdapter->hFile == INVALID_HANDLE_VALUE)) {
        errorbuf = "Failed in opening adapter!";
        return false;
    }



    // Allocate a buffer to get the MAC adress
    OidData = (PPACKET_OID_DATA)malloc(MACAddrLen + sizeof(PACKET_OID_DATA));
    if (OidData == nullptr) {
        errorbuf = "Memory allocation for OidData failed!";

        PacketCloseAdapter(lpAdapter);
        //free(OidData);
        return false;
    }


    // Retrieve the adapter MAC querying the NIC driver
    OidData->Oid = OID_802_3_CURRENT_ADDRESS;
    OidData->Length = MACAddrLen;
    ZeroMemory(OidData->Data, MACAddrLen);

    Status = PacketRequest(lpAdapter, FALSE, OidData);
    if (!Status) {
        errorbuf = "Failed in getting MAC Address!";

        PacketCloseAdapter(lpAdapter);
        free(OidData);
        return false;
    }
    memcpy(mac, OidData->Data, 6);


    PacketCloseAdapter(lpAdapter);
    free(OidData);
    return true;
}