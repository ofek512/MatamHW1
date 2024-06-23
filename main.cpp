
#include <string>
#include <fstream>
#include "BlockChain.h"
#include "Transaction.h"

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;


int main(int argc , char** argv){
    //error handlings
    if (argc < 4) {
        std::cerr << getErrorMessage() << std::endl;
        return 1;
    }
    std::ifstream file(argv[2]);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open source file " << argv[2] << std::endl;
        return 1;
    }
    std::ofstream output(argv[3]);
    if (!output.is_open()) {
        std::cerr << "Error: Cannot open target file " << argv[3] << std::endl;
        return 1;
    }
    
    std::ifstream file;
    std::ofstream output;
    output.open(argv[3]);
    file.open(argv[2]);
    BlockChain blockChain = BlockChainLoad(file);
    if(std::string(argv[1]) == "compress"){
        BlockChainCompress(blockChain);
        BlockChainDump(blockChain, output);
    }
    else if(std::string(argv[1]) == "hash"){
        BlockChainDumpHashed(blockChain, output);
    }
    else if(std::string(argv[1]) == "format"){
        BlockChainDump(blockChain, output);
    }
    else if(std::string(argv[1]) == "verify"){
        if(BlockChainVerifyFile(blockChain, file))
            output << "Verification passed";
        else
            output << "Verification failed";
    }
    //there is some problems with main, check if u have koah
    output.close();
    file.close();
        return 0;
}
