#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/asset.hpp>
#include <iostream>

using namespace eosio;

class bitcrox : public eosio::contract
{
public:
  using contract::contract;

  // @abi table buys i64
  struct Buy
  {
    account_name orderer;
    asset amount;
    uint32_t date;

    int64_t primary_key() const { return date + orderer; }
    EOSLIB_SERIALIZE(Buy, (orderer)(amount)(date))
  };

  // @abi table sells i64
  struct Sell
  {
    account_name orderer;
    asset amount;
    uint32_t date;

    int64_t primary_key() const { return date + orderer; }
    EOSLIB_SERIALIZE(Sell, (orderer)(amount)(date))
  };

  // @abi table histories i64
  struct History
  {
    account_name buyer;
    account_name seller;
    asset amount;
    uint32_t date;

    int64_t primary_key() const { return date + buyer + seller; }
    EOSLIB_SERIALIZE(History, (buyer)(seller)(amount)(date))
  };

  typedef multi_index<N(buys), Buy> _buys;
  typedef multi_index<N(sells), Sell> _sells;
  typedef multi_index<N(histories), History> _histories;

  // @abi action
  void buy(account_name orderer, asset amount)
  {
    auto order = getSellOrderByAmount(amount);
    if (order != nullptr)
    {
      print("Buying order from ", name{orderer});

      _sells sells(_self, _self);
      auto sellOrder = sells.find(order->date + order->orderer);
      sells.erase(sellOrder);

      _histories histories(_self, _self);
      histories.emplace(_self, [&](auto &h) {
        h.buyer = orderer;
        h.seller = sellOrder->orderer;
        h.amount = amount;
        h.date = now();
      });
    }
    else
    {
      print("Putting buy order from ", name{orderer});

      _buys buys(_self, _self);
      buys.emplace(_self, [&](auto &b) {
        b.orderer = orderer;
        b.amount = amount;
        b.date = now();
      });
    }
  }

  // @abi action
  void sell(account_name orderer, asset amount)
  {
    auto order = getBuyOrderByAmount(amount);
    if (order != nullptr)
    {
      print("Selling order from ", name{orderer});

      _buys buys(_self, _self);
      auto sellOrder = buys.find(order->date + order->orderer);
      buys.erase(sellOrder);

      _histories histories(_self, _self);
      histories.emplace(_self, [&](auto &h) {
        h.buyer = sellOrder->orderer;
        h.seller = orderer;
        h.amount = amount;
        h.date = now();
      });
    }
    else
    {
      print("Putting sell order from ", name{orderer});

      _sells sells(_self, _self);
      sells.emplace(_self, [&](auto &s) {
        s.orderer = orderer;
        s.amount = amount;
        s.date = now();
      });
    }
  }

private:
  const Sell *getSellOrderByAmount(asset amount)
  {
    _sells sells(_self, _self);
    for (auto it = sells.begin(); it != sells.end(); it++)
    {
      if (it->amount == amount)
      {
        return &(*it);
      }
    }
    return nullptr;
  }

  const Buy *getBuyOrderByAmount(asset amount)
  {
    _buys buys(_self, _self);
    for (auto it = buys.begin(); it != buys.end(); it++)
    {
      if (it->amount == amount)
      {
        return &(*it);
      }
    }
    return nullptr;
  }
};

EOSIO_ABI(bitcrox, (buy)(sell))
