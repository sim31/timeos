/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <timeos.hpp>
#include <timeos.gen.hpp>

namespace CONTRACT_NAME {

  void store_timestamp(uint64_t scope, uint64_t table, const timestamp& ts) {
    bytes date = eosio::raw::pack(ts.date);
    ::store_str(scope, table, (char*)ts.data.get_data(), ts.data.get_size(), (char*)date.data, date.len);
  }

  bool is_timestamped(const timestamp_order& order) {
    time t;
    auto r = load_str(order.owner, CONTRACT_NAME_UINT64, N(timestamp),
             (char*)order.data.get_data(), order.data.get_size(), (char*)&t, sizeof (t));
    return r > -1;
  }

  void create_timestamp(const timestamp_order& order) {
    eosio::require_auth(order.owner);
    assert(!is_timestamped(order), "Data is already timestamped");
    timestamp ts = timestamp(order);
    store_timestamp(order.owner, N(timestamp), ts);
  }

  void remove_timestamp(const timestamp_order& order) {
    eosio::require_auth(order.owner);
    auto success = remove_str(order.owner, N(timestamp), (char*)order.data.get_data(), order.data.get_size());
    assert(success == 1, "Timestamp with this data does not exist");
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
      if (action == N(createts)) {
        create_timestamp(eosio::current_message<timestamp_order>());
      }
      else if (action == N(removets)) {
        //FIXME: Should removing timestamp be allowed?
        remove_timestamp(eosio::current_message<timestamp_order>());
      }
    }
  }
} // extern "C"
