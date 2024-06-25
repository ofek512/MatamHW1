#include <string>
#include <fstream>
#include <iostream>
#include "BlockChain.h"
#include "Transaction.h"
#include "Utilities.h"

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;


int main(int argc, char **argv) {
    std::ifstream file;
    if (argc < 4 || argc > 5) {
        std::cerr << getErrorMessage() << std::endl;
        return 1;
    }
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
        output.close();
        file.close();
    }
    return 0;
}
//yipee