#pragma once

#include <eoslib/eos.hpp>
#include <eoslib/string.hpp>

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

    timestamp() {}
    timestamp(const eosio::string& data, time date) : data(data), date(date) {}
    //Create timestamp with time from previous block
    timestamp(const timestamp_order& order) : data(order.data) {
      date = now();
    }
  };

}



