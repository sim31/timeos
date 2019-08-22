project(timeos)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( timeos timeos timeos.cpp )
target_include_directories( timeos PUBLIC ${CMAKE_SOURCE_DIR}/../include )
#target_ricardian_directory( timeos ${CMAKE_SOURCE_DIR}/../ricardian )
