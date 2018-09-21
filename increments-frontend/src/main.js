import Vue from "vue";
import "babel-polyfill";

import eos from "./api";
import App from "./App.vue";

Vue.config.productionTip = false;
Vue.prototype.$eos = eos;

new Vue({
  render: h => h(App)
}).$mount("#app");
