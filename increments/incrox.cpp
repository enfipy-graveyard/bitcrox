#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <iostream>

using namespace eosio;
using namespace std;

#define S(X) string_to_name(X.c_str())

class incrox : public eosio::contract
{
public:
  using contract::contract;

  // @abi table items i64
  struct Item
  {
    string name;
    int32_t nonce;

    uint64_t primary_key() const { return S(name); }
    EOSLIB_SERIALIZE(Item, (name)(nonce))
  };

  typedef multi_index<N(items), Item> _items;

  // @abi action
  void add(account_name from, string name)
  {
    require_auth(from);

    // print("Adding item ", S(name));

    _items items(_self, from);
    auto exist = items.find(S(name));

    eosio_assert(exist == items.end(), "Item with this name already exists");

    items.emplace(from, [&](auto &o) {
      o.name = name;
      o.nonce = 0;
    });
  }

  // @abi action
  void inc(account_name whose, string name)
  {
    // print("Incrementing item ", S(name));

    _items items(_self, whose);
    auto exist = items.find(S(name));

    eosio_assert(exist != items.end(), "Item with this name doesn't exists");

    items.modify(exist, 0, [&](auto &o) {
      o.nonce++;
    });
  }

  // @abi action
  void rem(account_name whose, string name)
  {
    require_auth(whose);

    // print("Removing item ", S(name));

    _items items(_self, whose);
    auto exist = items.find(S(name));

    eosio_assert(exist != items.end(), "Item with this name doesn't exists");

    items.erase(exist);
  }
};

EOSIO_ABI(incrox, (add)(inc)(rem))
