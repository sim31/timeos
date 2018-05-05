/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosiolib/eosio.hpp>

namespace timeos {

   class timeos : eosio::contract {
      public:
         timeos(account_name contract_name) : eosio::contract(contract_name) {}

         //@abi action createts
         void create_timestamp(account_name owner, const std::string& data) {
            //TODO:

         }

         //@abi table timestamp i64
         struct timestamp {
            uint64_t pkey;
            time time;
            //TODO: is this the best choice for type?
            std::string data;

            uint64_t get_primary_key() const {
               return pkey;
            }

            uint64_t get_reverse_pk() const {
               //TODO: check if order is right
               return ~pkey;
            }

            EOSLIB_SERIALIZE(timestamp, (pkey)(time)(data))
         };

         typedef eosio::multi_index< N(timestamp), timestamp, eosio::indexed_by<
            N(reversepk),
            eosio::const_mem_fun<timestamp, uint64_t, &timestamp::get_reverse_pk>
         > > timestamps;
   };

}

