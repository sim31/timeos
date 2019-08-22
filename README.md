# Timeos
Simple timestamping service. Useful if you want to record a statement or a file hash to prove authorship.

## How to Build 
- cd to 'build' directory
- run the command 'cmake ..'
- run the command 'make'
- After build -
   - The built smart contract is under the 'hello' directory in the 'build' directory
   - You can then do a 'set contract' action with 'cleos' and point in to the './build/hello' directory
- Additions to CMake should be done to the CMakeLists.txt in the './src' directory and not in the top level CMakeLists.txt

---

Tested with eosio.cdt v1.5.0
