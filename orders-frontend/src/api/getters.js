import eos from "./index.js";

export default {
  getTable: async name => {
    const res = await eos.api.getTableRows({
      code: eos.lord,
      scope: eos.lord,
      table: name,
      json: true,
      limit: 30
    });
    return res.rows;
  }
};
