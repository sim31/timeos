/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <timeos.hpp>
#include <timeos.gen.hpp>
#include <eoslib/db.hpp>
#include <eoslib/string.hpp>

namespace CONTRACT_NAME {

  void store_timestamp(uint64_t scope, uint64_t table, const timestamp& ts) {
    bytes date = eosio::raw::pack(ts.date);
    ::store_str(scope, table, (char*)ts.data.get_data(), ts.data.get_size(), (char*)date.data, date.len);
  }

  void create_timestamp(const timestamp_order& order) {
    //TODO: Should updating same data with newer date be allowed?
    eosio::require_auth(order.owner);
    timestamp ts = timestamp(order);
    store_timestamp(order.owner, N(timestamp), ts);
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
  }

  /// The apply method implements the dispatch of events to this contract
  void apply( uint64_t code, uint64_t action ) {
    if (code == CONTRACT_NAME_UINT64) {
        if (action == N(newtimestamp)) {
            create_timestamp(eosio::current_message<timestamp_order>());
          }
      }
  }
} // extern "C"
