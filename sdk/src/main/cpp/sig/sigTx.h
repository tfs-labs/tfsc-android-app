#ifndef __SIG_TX__
#define __SIG_TX__
#include "proto/transaction.pb.h"
#include <string>

std::string testSig(CTransaction& tx ,void * pkey);


std::string toSig(const std::string& data,void * pkey);

#endif