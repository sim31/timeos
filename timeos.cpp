/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <timeos.hpp>
#include <timeos.gen.hpp>
#include <eoslib/db.hpp>
#include <eoslib/string.hpp>

namespace CONTRACT_NAME {

void store_key_val(uint64_t scope, uint64_t table, const key_val& keyval) {
  eosio::print("Inserting key_val:\n");
  eosio::dump(keyval);
  bytes key = eosio::raw::pack(keyval.key);
  bytes val = eosio::raw::pack(keyval.value);
  eosio::print("keylen: ", key.len, "val.len: ", val.len, "\n");
  //::store_str(scope, table, (char*)key.data, key.len, (char*)val.data, val.len);
  ::store_str(scope, table, (char*)keyval.key.get_data(), keyval.key.get_size(), (char*)val.data, val.len);

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
    if (code == CONTRACT_NAME_UINT64) {
        eosio::print("code is contract name");
        if (action == N(savekeyval)) {
            key_val kv = eosio::current_message<key_val>();
            store_key_val(CONTRACT_NAME_UINT64, N(keyval), kv);
        }
    }
}
} // extern "C"
