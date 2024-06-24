#include <string>
#include <fstream>
#include <iostream>
#include "BlockChain.h"
#include "Transaction.h"

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;


int main(int argc, char **argv) {
    std::ifstream file;
    file.open(argv[2]);
    BlockChain blockChain = BlockChainLoad(file);
    if (std::string(argv[1]) == "verify") {
        std::ifstream target;
        target.open(argv[3]);
        if (BlockChainVerifyFile(blockChain, target))
            std::cout << "Verification passed" << std::endl;
        else
            std::cout << "Verification passed" << std::endl;
        target.close();
    } else {
        std::ofstream output;
        output.open(argv[3]);
        if (std::string(argv[1]) == "compress") {
            BlockChainCompress(blockChain);
            BlockChainDump(blockChain, output);
        }
        if (std::string(argv[1]) == "hash") {
            BlockChainDumpHashed(blockChain, output);
        }
        if (std::string(argv[1]) == "format") {
            BlockChainDump(blockChain, output);
        }
        //there is some problems with main, check if u have koah
        output.close();
        file.close();
    }
    return 0;
}