import eos from "./index.js";

export default {
  add(from, name) {
    return eos.api.contract(eos.lord).then(contract => {
      return contract.add(from, name, { authorization: from }).then(res => res);
    });
  },
  rem(whose, name) {
    return eos.api.contract(eos.lord).then(contract => {
      return contract.rem(whose, name, { authorization: whose }).then(res => res);
    });
  },
  inc(whose, name) {
    return eos.api.contract(eos.lord).then(contract => {
      return contract.inc(whose, name, { authorization: whose }).then(res => res);
    });
  }
};
