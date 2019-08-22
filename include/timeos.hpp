#include <eosiolib/eosio.hpp>
using namespace eosio;

CONTRACT timeos : public contract {
   public:
      using contract::contract;

      ACTION timestamp( std::string& str );

      using timestamp_action = action_wrapper<"timestamp"_n, &timeos::timestamp>;
};
