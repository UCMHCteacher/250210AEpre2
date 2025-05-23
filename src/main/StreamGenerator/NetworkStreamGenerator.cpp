#include<sstream>


#include"StreamGenerator.hpp"

#include"NetworkTools.hpp"

#include"Summary.hpp"
#include"ToolChain.hpp"
using ToolChain::_coutMutex;




StreamGenerators::NetworkStreamGenerator::NetworkStreamGenerator(std::string networkDeviceIP) :
    _deviceHandle(nullptr),
    _enabled(false)
{
    NetworkNode networkToOpen;
    std::hash<std::string> ipHash{};
    for (auto &  networkNode : networkList) {
        if (ipHash(networkDeviceIP) == ipHash(std::string(inet_ntoa(networkNode.deviceIPAddr)))) {
            networkToOpen = networkNode;
            break;
        }
    }

    if (networkToOpen.deviceName.length() == 0) {
        std::cout << "Cannot find network " << networkDeviceIP << '\n';
        return;
    }


    char errBuf[PCAP_ERRBUF_SIZE];

    _deviceHandle = pcap_create(networkToOpen.deviceName.c_str(), errBuf);


    if (_deviceHandle == nullptr) {
        std::lock_guard lk(_coutMutex);
        std::cout 
            << "Failed in creating deviceHandle!\n"
            << "ErrBuf: " << errBuf << "\n";
        return;
    }

    if (0 != 
        pcap_set_snaplen(
            _deviceHandle,
            65536
        )
    ) {
        std::lock_guard lk(_coutMutex);
        std::cout 
            << "Failed in setting snapshot length!\n"
            << "ErrBuf: " << errBuf << "\n";
        return;
    }

    if (0 != 
        pcap_set_promisc(
            _deviceHandle,
            PCAP_OPENFLAG_PROMISCUOUS
        )
    ) {
        std::lock_guard lk(_coutMutex);
        std::cout 
            << "Failed in setting promiscuous mode!\n"
            << "ErrBuf: " << errBuf << "\n";
        return;
    }

    if (0 != 
        pcap_set_timeout(
            _deviceHandle,
            1000
        )
    ) {
        std::lock_guard lk(_coutMutex);
        std::cout 
            << "Failed in setting timeout!\n"
            << "ErrBuf: " << errBuf << "\n";
        return;
    }

    int activateRes = pcap_activate(_deviceHandle);
    if (0 != activateRes) {
        std::lock_guard lk(_coutMutex);
        std::cout 
            << "Failed in activating!\n"
            << "ErrCode: " << activateRes << "\n";
        return;
    }



    _enabled = true;
}



StreamGenerators::NetworkStreamGenerator::~NetworkStreamGenerator() {
    pcap_close(_deviceHandle);
}



std::shared_ptr<StreamPackage>
StreamGenerators::NetworkStreamGenerator::getStream() {
    if (!_enabled)
        return nullptr;


    u_char const * _data = nullptr;
    pcap_pkthdr * _hdr = nullptr;
    int retVal = 0;

    do {
        Summary::Entry();

        retVal = pcap_next_ex(_deviceHandle, &_hdr, &_data);

        if (retVal == 1) {
            return std::make_shared<StreamPackage>(
                    std::make_shared<std::istringstream>(
                        std::string(
                            reinterpret_cast<char*>(const_cast<u_char*>(_data)), 
                            _hdr->caplen)
                    )
                );
        }

        if (retVal < 0) {
            std::lock_guard lk(_coutMutex);
            std::cout 
                << "An error occurred while reading the packet.\n"
                << "Error Code: " << retVal << '\n'
                << "Errmsg: " << pcap_geterr(_deviceHandle) << '\n';
            return nullptr;
        }

    } while(retVal == 0);

    return nullptr;
}