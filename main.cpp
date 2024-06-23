
#include <string>
#include <fstream>
#include "BlockChain.h"
#include "Transaction.h"

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;


int main(int argc , char** argv){
    std::ifstream file;
    std::ofstream output;
    output.open(argv[3]);
    file.open(argv[2]);
    BlockChain blockChain = BlockChainLoad(file);
    if(std::string(argv[1]) == "compress"){
        BlockChainCompress(blockChain);
        BlockChainDump(blockChain, output);
    }
    if(std::string(argv[1]) == "hash"){
        BlockChainDumpHashed(blockChain, output);
    }
    if(std::string(argv[1]) == "format"){
        BlockChainDump(blockChain, output);
    }
    /*if(std::string(argv[1]) == "verify"){
        std::ifstream target;
        target.open(argv[2]);
        if(BlockChainVerifyFile(blockChain, target))
            output << "Verification passed";
        else
            output << "Verification failed";
        target.close();
    }*/
    //there is some problems with main, check if u have koah
    output.close();
    file.close();
        return 0;
}