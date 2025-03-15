#include"CDChunking.hpp"
#include"ToolChain.hpp"
#include<iomanip>
#include<algorithm>
#include<iterator>


CDChunking::HashCalculator::HashCalculator(std::string const &  algoType) {
    _ctx = EVP_MD_CTX_new();
    _mdAlgo = EVP_MD_fetch(nullptr, algoType.c_str(), nullptr);
    _usable = true;
    if ((_ctx == nullptr) || (_mdAlgo == nullptr)) {
        std::lock_guard lk(ToolChain::_coutMutex);
        std::cout << "Hash calculator init failed.\n";
        _usable = false;
    } 
}
CDChunking::HashCalculator::HashCalculator() :
    HashCalculator("SHA256")
{}



CDChunking::HashCalculator::~HashCalculator() {
    // EVP_MD_free(_mdAlgo);
    // EVP_MD_CTX_free(_ctx);
}




void
CDChunking::HashCalculator::operator() (std::shared_ptr<ChunkPackage> chunkPackage) {
    if (!_usable) return;


    if (!EVP_DigestInit_ex(_ctx, _mdAlgo, nullptr)) {
        std::lock_guard lk(ToolChain::_coutMutex);
        std::cout << "DigestInit Failed.\n";
        return;
    }


    if (!EVP_DigestUpdate(_ctx, chunkPackage->_data.data(), chunkPackage->_data.size())) {
        std::lock_guard lk(ToolChain::_coutMutex);
        std::cout << "DigestUpdate Failed.\n";
        return;
    }


    uint32_t len = 0;
    uint8_t *  output = static_cast<uint8_t*>(OPENSSL_malloc(EVP_MD_get_size(_mdAlgo)));
    if (!EVP_DigestFinal_ex(_ctx, output, &len)) {
        std::lock_guard lk(ToolChain::_coutMutex);
        std::cout << "Hash calculate Failed.\n";
        return;
    }


    chunkPackage->_datahash.assign(output, output+len);

    // OPENSSL_free(output);
}