#pragma once

#include <eoslib/eos.hpp>
#include <eoslib/string.hpp>

#define CONTRACT_NAME timeos1
#define CONTRACT_NAME_UINT64 N(timeos1)

/* @abi action savekeyval
*  @abi table
*/
struct key_val {
    eosio::string key;
    eosio::string value;
};




