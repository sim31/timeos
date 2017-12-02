#pragma once
#include <eoslib/types.hpp>
#include <eoslib/message.hpp>
#include <eoslib/datastream.hpp>
#include <eoslib/raw_fwd.hpp>

namespace eosio { namespace raw {
   template<typename Stream> inline void pack( Stream& s, const key_val& value ) {
      raw::pack(s, value.key);
      raw::pack(s, value.value);
   }
   template<typename Stream> inline void unpack( Stream& s, key_val& value ) {
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
   void dump(const key_val& value, int tab=0) {
      print_ident(tab);print("key:[");prints_l(value.key.get_data(), value.key.get_size());print("]\n");
      print_ident(tab);print("value:[");prints_l(value.value.get_data(), value.value.get_size());print("]\n");
   }
   template<>
   key_val current_message<key_val>() {
      return current_message_ex<key_val>();
   }
} //eosio

