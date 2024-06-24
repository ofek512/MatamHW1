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
    if (argc < 4) {
        std::cerr << "Usage: ./mtm_blockchain <command> <source> <target> [<output>]" << std::endl;
        return 1;
    }

    ifstream file(argv[2]);
    if (!file.is_open()) {
        std::cerr << "Error opening source file: " << argv[2] << std::endl;
        return 1;
    }

    BlockChain blockChain = BlockChainLoad(file);
    file.close();

    string command = argv[1];
    if (command == "verify") {
        if (argc < 5) {
            std::cerr << "Usage: ./mtm_blockchain verify <source> <target> <output>" << std::endl;
            return 1;
        }

        ifstream target(argv[3]);
        if (!target.is_open()) {
            std::cerr << "Error opening target file: " << argv[3] << std::endl;
            return 1;
        }

        ofstream output("tests/" + string(argv[4]));
        if (!output.is_open()) {
            std::cerr << "Error opening output file: tests/" << argv[4] << std::endl;
            return 1;
        }

        if (BlockChainVerifyFile(blockChain, target))
            output << "Verification passed" << endl;
        else
            output << "Verification failed" << endl;

    } else {
        ofstream output(argv[3]);
        if (!output.is_open()) {
            std::cerr << "Error opening target file: " << argv[3] << std::endl;
            return 1;
        }

        if (command == "compress") {
            BlockChainCompress(blockChain);
            BlockChainDump(blockChain, output);
        } else if (command == "hash") {
            BlockChainDumpHashed(blockChain, output);
        } else if (command == "format") {
            BlockChainDump(blockChain, output);
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
            return 1;
        }
    }

    return 0;
}
