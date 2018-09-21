import eosjs from "eosjs";

import getters from "./getters";
import methods from "./methods";

export default {
  lord: "bitcrox",
  pubKey: "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV",
  api: eosjs({
    httpEndpoint: "http://127.0.0.1:8888",
    keyProvider: "5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3"
  }),
  getters,
  methods
};
