import eos from "./index.js";

export default {
  sell: async (name, amount) => {
    const contract = await eos.api.contract(eos.lord);
    const res = await contract.sell(name, amount, { authorization: name });
    return res;
  },
  buy: async (name, amount) => {
    const contract = await eos.api.contract(eos.lord);
    const res = await contract.buy(name, amount, { authorization: name });
    return res;
  }
};
