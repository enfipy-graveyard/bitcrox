<template>
  <div id="app">
    <img alt="Vue logo" src="./assets/logo.png">

    <div class="controls">
      <button @click="sell">Sell one</button>
      <button @click="buy">Buy one</button>
      <button @click="buyMultiple">Buy two</button>
    </div>
    
    <div class="info">
      <list name="Sells" :items="sells" />
      <list name="Buys" :items="buys" />
      <list name="Histories" :items="histories" />
    </div>
  </div>
</template>

<script>
export default {
  name: "app",
  components: {
    list: () => import("@/components/List")
  },
  data: () => ({
    sells: [],
    buys: [],
    histories: []
  }),
  mounted() {
    this.update();
  },
  methods: {
    update() {
      this.$eos.getters.getTable("sells").then(res => (this.sells = res));
      this.$eos.getters.getTable("buys").then(res => (this.buys = res));
      this.$eos.getters
        .getTable("histories")
        .then(res => (this.histories = res));
    },
    sell() {
      this.$eos.methods.sell("user", "1000.00 EOS").then(() => this.update());
    },
    buy() {
      this.$eos.methods.buy("tester", "1000.00 EOS").then(() => this.update());
    },
    buyMultiple() {
      this.$eos.methods.buy("tester", "1000.00 EOS").then(() => this.update());
      this.$eos.methods.buy("user", "1000.00 EOS").then(() => this.update());
    }
  }
};
</script>

<style>
#app {
  font-family: "Avenir", Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
.info {
  display: flex;
  justify-content: center;
}
.info .list {
  margin: 0 20px;
}
</style>
