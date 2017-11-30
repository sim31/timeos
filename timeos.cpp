/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <timeos.hpp>
#include <eoslib/db.hpp>
#include <eoslib/string.hpp>

namespace CONTRACT_NAME {

// Store data packed the same way as the eosio::abi_serializer does
// into single string index table.
void store_packed_str(uint64_t scope, uint64_t table, char* data, uint32_t size) {
    uint32_t keylen = data[0];
    char* key = data + 1;
    uint32_t valuelen = size - keylen - 1;
    char* value = data + (size - valuelen);

    eosio::print("keylen= ", keylen, ", valuelen= ", valuelen);
//    char* test_val = "\t123456789";
//    auto test_val_size = eosio::cstrlen(test_val);
//    eosio::print("test_val_size = ", test_val_size);

    ::store_str(scope, table, key, keylen, value, valuelen);

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
            auto size = message_size();
            char buff[size];
            read_message(buff, size);
            store_packed_str(CONTRACT_CODE, N(timestamps), buff, size);
        }
    }
}
} // extern "C"
