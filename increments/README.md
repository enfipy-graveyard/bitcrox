# EOS Test Smart Contract

#### Installation

You can run through [docker](https://developers.eos.io/eosio-nodeos/docs/docker-quickstart) or build from [sources](https://developers.eos.io/eosio-nodeos/docs/install-nodeos).

Then you should start `nodeos`:

> nodeos -e -p eosio --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console --http-validate-host=false --access-control-allow-origin=\* --http-server-address=0.0.0.0:8888

And `keosd`:

> keosd --http-server-address=0.0.0.0:8899

#### Setup

Create `default` wallet:

> cleos wallet create --to-console

Create `key pair`:

> cleos create key --to-console

And import it:

> cleos wallet import

Create account with name `incrox`:

> cleos create account eosio incrox {public_OwnerKey} {public_ActiveKey}

And two accounts for `user` and `tester`:

> cleos create account eosio user {public_OwnerKey} {public_ActiveKey}
> cleos create account eosio tester {public_OwnerKey} {public_ActiveKey}

#### Run smart contract

Build `wast`, `wasm` and `abi` files by running scripts:

> eosiocpp -o incrox.wast incrox.cpp
> eosiocpp -g incrox.abi incrox.cpp

And run it:

> cleos set contract incrox ../incrox -p incrox@active

Or you can just open this project in `vscode` and enter `F5`

# This smart conract is on Jungle Testnet

> cleos --url http://dev.cryptolions.io:38888 set contract enfipyenfipy ../incrox -p enfipyenfipy
> cleos --url http://dev.cryptolions.io:38888 get table enfipyenfipy enfipyenfipy items
> cleos --url http://dev.cryptolions.io:38888 push action enfipyenfipy rem '["enfipyenfipy", "5 Things to do"]' -p enfipyenfipy@active
> cleos --url http://dev.cryptolions.io:38888 get table enfipyenfipy enfipyenfipy items
