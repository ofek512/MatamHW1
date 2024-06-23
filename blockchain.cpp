
#pragma once

#include <string>
#include <fstream>
#include "BlockChain.h"
#include "Transaction.h"


using std::ifstream;
using std::ofstream;
using std::endl;

/**
 * BlockChainPersonalBalance - returns the balance of a given person, relative to a given BlockChain
 *
 * @param blockChain - BlockChain to calculate the balance from
 * @param name - Name of the person to calculate the balance for
 *
 * @return Balance of the person
*/

int
BlockChainPersonalBalance(const BlockChain &blockChain, const string &name) {
    int balance = 0;
    BlockChainNode *node = blockChain.head;
    while (node != nullptr) {
        const Transaction &transact = node->transaction;
        if (transact.sender == name) {
            balance -= transact.value;
        } else if (transact.receiver == name) {
            balance += transact.value;
        }
        node = node->previous;
    }
    return balance;
}

/**
 * BlockChainAppendTransaction - creates and appends a new transaction to the BlockChain
 *
 * @param blockChain BlockChain to append the transaction to
 * @param value Value of the transaction
 * @param sender Name of the sender
 * @param receiver Name of the receiver
 * @param timestamp String that holds the time the transaction was made
*/
void BlockChainAppendTransaction(
        BlockChain &blockChain,
        unsigned int value,
        const string &sender,
        const string &receiver,
        const string &timestamp
) {
    auto *newNode = new BlockChainNode;
    newNode->transaction = {value, sender, receiver};
    newNode->previous = blockChain.head;
    newNode->timestamp = timestamp;
    blockChain.head = newNode;
}

/**
 * BlockChainAppendTransaction - appends a copy of a given transaction to the BlockChain
 *
 * @param blockChain BlockChain to append the transaction to
 * @param transaction Transaction we want to append
 * @param timestamp String that holds the time the transaction was made
*/
void BlockChainAppendTransaction(
        BlockChain &blockChain,
        const Transaction &transaction,
        const string &timestamp
) {
    auto *newNode = new BlockChainNode;
    newNode->transaction = transaction;
    newNode->previous = blockChain.head;
    newNode->timestamp = timestamp;
    blockChain.head = newNode;
}

/**
 * BlockChainGetSize - returns the number of Blocks in the BlockChain
 *
 * @param blockChain - BlockChain to measure
 *
 * @return Number of Blocks in the BlockChain
*/

int BlockChainGetSize(const BlockChain &blockChain) {
    int counter = 0;
    BlockChainNode *node = blockChain.head;
    while (node != nullptr) {
        node = node->previous;
        counter++;
    }
    return counter;
}

/**
 * BlockChainLoad - Reads data from a file and creates a new block chain
 *
 * @param file Data file to read from
 *
 * @return BlockChain created from the file
 *
*/
BlockChain BlockChainLoad(ifstream &file) {
    BlockChain blockchain, temp_blockchain;
    blockchain.head = nullptr;
    temp_blockchain.head = nullptr;
    string sender, receiver, time_stamp;
    int sum;
    while (file >> sender >> receiver >> sum >> time_stamp) {
        BlockChainAppendTransaction(temp_blockchain, sum, sender, receiver, time_stamp);
    }
    for (int i = 0; i < BlockChainGetSize(temp_blockchain); i++) {
        BlockChainAppendTransaction(blockchain, temp_blockchain.head->transaction, temp_blockchain.head->timestamp);
        temp_blockchain.head = temp_blockchain.head->previous;
    }
    return blockchain;
}

/**
 * BlockChainDump - Prints the data of all transactions in the BlockChain to a given file
 *
 * Data will be printed in the following format:
 *
 * BlockChain info:
 * <n>.
 * Sender Name: <name>
 * Receiver Name: <name>
 * Transaction Value: <value>
 * Transaction Timestamp: <time>
 *
 * @param blockChain BlockChain to print
 * @param file File to print to
 *
*/
void BlockChainDump(const BlockChain &blockChain, ofstream &file) {
    auto *current_node = blockChain.head;
    int counter = 1;
    file << "BlockChain info:" << endl;
    while (current_node != nullptr) {
        file << counter << "." << endl;
        file << "Sender name: " << current_node->transaction.sender << endl;
        file << "Receiver name: " << current_node->transaction.receiver << endl;
        file << "Transaction Value: " << current_node->transaction.value << endl;
        file << "Transaction timestamp: " << current_node->timestamp << endl;
        current_node = current_node->previous;
    }
}

/**
 * BlockChainDumpHashed - Prints the *hashed data* of all transactions in the BlockChain to a given file
 *
 * Data will be printed in the following format:
 * <hashed message>
 * <hashed message>
 * ...
 * <hashed message>
 *
 * @param blockChain BlockChain to print
 * @param file File to print to
 *
*/
void BlockChainDumpHashed(const BlockChain &blockChain, ofstream &file) {
    auto *current_node = blockChain.head;
    for (int i = 1; i < BlockChainGetSize(blockChain); i++) {
        file << TransactionHashedMessage(current_node->transaction) << endl;
        current_node = current_node->previous;
    }
    file << TransactionHashedMessage(current_node->transaction);
}

/**
 * BlockChainVerifyFile - verifies that the file contains correct hashed messages of the given BlockChain
 *
 * Input file is expected to contain data in the following format:
 * <hashed message>
 * <hashed message>
 * ...
 * <hashed message>
 *
 * @param blockChain BlockChain to verify
 * @param file File to read from
 *
 * @return true if the file is valid, false otherwise
*/
bool BlockChainVerifyFile(const BlockChain &blockChain, std::ifstream &file) {
    auto *current_node = blockChain.head;
    string current_hashcode;
    while (file >> current_hashcode) {
        if (current_node == nullptr || current_hashcode != TransactionHashedMessage(current_node->transaction))
            return false;
        current_node = current_node->previous;
    }
    if (current_node != nullptr)
        return false;
    return true;
}

/**
 * BlockChainCompress - Compresses the given block chain based on the transaction's data.
 * All consecutive blocks with the same sender and receiver will be compressed to one Block.
 *
 * @param blockChain BlockChain to compress
*/
void BlockChainCompress(BlockChain &blockChain) {
    auto *looper = blockChain.head;
    BlockChainNode *temp;
    while (looper->previous != nullptr) {
        temp = looper->previous;
        if (looper->transaction.sender == looper->previous->transaction.sender
            && looper->transaction.receiver == looper->previous->transaction.receiver) {
            looper->transaction.value += looper->previous->transaction.value;
            looper->timestamp = looper->previous->timestamp;
            looper->previous = looper->previous->previous;
            delete[] temp;
        }
    }

}