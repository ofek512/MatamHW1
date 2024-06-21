#pragma once

#include <string>
#include <fstream>
#include "BlockChain.h"
#include "Transaction.h"

using std::string;
using std::ifstream;
using std::ofstream;

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
    Transaction newTrans;
    newTrans.value = value;
    newTrans.sender = sender;
    newTrans.receiver = receiver;
    auto *newNode = new BlockChainNode;
    newNode->transaction = newTrans;
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
    auto* newNode = new BlockChainNode;
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
    BlockChainNode* node = blockChain.head;
    while (node != nullptr) {
        node = node->previous;
        counter++;
    }
    return counter;
}
