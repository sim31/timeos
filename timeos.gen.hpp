#pragma once
#include <eoslib/types.hpp>
#include <eoslib/message.hpp>
#include <eoslib/datastream.hpp>
#include <eoslib/raw_fwd.hpp>

namespace eosio { namespace raw {
   template<typename Stream> inline void pack( Stream& s, const timestamp_order& value ) {
      raw::pack(s, value.data);
      raw::pack(s, value.owner);
   }
   template<typename Stream> inline void unpack( Stream& s, timestamp_order& value ) {
      raw::unpack(s, value.data);
      raw::unpack(s, value.owner);
   }
   template<typename Stream> inline void pack( Stream& s, const timestamp& value ) {
      raw::pack(s, value.key);
      raw::pack(s, value.value);
   }
   template<typename Stream> inline void unpack( Stream& s, timestamp& value ) {
      raw::unpack(s, value.key);
      raw::unpack(s, value.value);
   }
} }

#include <eoslib/raw.hpp>
namespace eosio {
   void print_ident(int n){while(n-->0){print("  ");}};
   template<typename Type>
   Type current_message_ex() {
      uint32_t size = message_size();
      char* data = (char *)eosio::malloc(size);
      assert(data && read_message(data, size) == size, "error reading message");
      Type value;
      eosio::raw::unpack(data, size, value);
      eosio::free(data);
      return value;
   }
   void dump(const timestamp_order& value, int tab=0) {
      print_ident(tab);print("data:[");prints_l(value.data.get_data(), value.data.get_size());print("]\n");
      print_ident(tab);print("owner:[");printn(value.owner);print("]\n");
   }
   template<>
   timestamp_order current_message<timestamp_order>() {
      return current_message_ex<timestamp_order>();
   }
   void dump(const timestamp& value, int tab=0) {
      print_ident(tab);print("key:[");prints_l(value.key.get_data(), value.key.get_size());print("]\n");
      print_ident(tab);print("value:[");printi(value.value);print("]\n");
   }
   template<>
   timestamp current_message<timestamp>() {
      return current_message_ex<timestamp>();
   }
} //eosio

