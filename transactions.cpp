#pragma once

#include <string>
#include <fstream>
#include "Transaction.h"

using std::string;
using std::ofstream;

/**
 * TransactionDumpInfo - Prints the data of the transaction to a given file
 * The data is printed in the following format:
 * Sender Name: <name>
 * Receiver Name: <name>
 * Transaction Value: <value>
 *
 * @param transaction Transaction to print
*/
void TransactionDumpInfo(const Transaction &transaction, ofstream &file) {

}