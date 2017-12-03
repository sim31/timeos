#pragma once

#include <eoslib/eos.hpp>
#include <eoslib/string.hpp>
#include <eoslib/db.hpp>

#define CONTRACT_NAME timeos
#define CONTRACT_NAME_UINT64 N(timeos)

namespace CONTRACT_NAME {

  //@abi action createts removets
  struct timestamp_order {
    eosio::string data;
    account_name  owner;
  };

  //@abi table str
  struct timestamp {
    eosio::string data;
    time          date;

    timestamp() : date(0) {}
    timestamp(const eosio::string& data, time date) : data(data), date(date) {}
    //Create timestamp with time from previous block
    timestamp(const timestamp_order& order) : data(order.data) {
      date = now();
    }
  };

  // Returns default timestamp value if data is not stored in the db
  timestamp get_timestamp(account_name owner, eosio::string data) {
    time t;
    auto r = load_str(owner, CONTRACT_NAME_UINT64, N(timestamp), (char*)data.get_data(),
             data.get_size(), (char*)&t, sizeof (t));
    return (r > -1) ? timestamp(data, t) : timestamp();
  }
}



