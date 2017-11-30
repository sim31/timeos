/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <timeos.hpp>
#include <eoslib/db.hpp>
#include <eoslib/string.hpp>

namespace CONTRACT_NAME {

void store_str() {
    eosio::print("store_str called");
    auto size = message_size();
    char str[size];
    read_message(str, size);
    int64_t test_val = 10;

    ::store_str(CONTRACT_CODE, N(timestamps), str, size, (char*)&test_val, sizeof (int64_t));
}
}

using namespace CONTRACT_NAME;
/**
 *  The init() and apply() methods must have C calling convention so that the blockchain can lookup and
 *  call these methods.
 */
extern "C" {

/**
     *  This method is called once when the contract is published or updated.
     */
void init()  {
    eosio::print( "Init World!\n" );
}

/// The apply method implements the dispatch of events to this contract
void apply( uint64_t code, uint64_t action ) {
    if (code == CONTRACT_CODE) {
        eosio::print("code is contract name");
        if (action == N(save)) {
            store_str();
        }
    }
}
} // extern "C"
