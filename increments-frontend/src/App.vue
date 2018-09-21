<template>
  <div id="app">
    <img alt="Vue logo" src="./assets/logo.png">

    <div class="controls">
      <button @click="() => call($eos.methods.add('incrox', '5 Things to do'))">Add</button>
      <button @click="() => call($eos.methods.rem('incrox', '5 Things to do'))">Remove</button>
      <button @click="() => call($eos.methods.inc('incrox', '5 Things to do'))">Increment</button>
    </div>
    
    <div class="info">
      <list name="Items" :items="items" />
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
    items: []
  }),
  mounted() {
    this.update();
  },
  methods: {
    update() {
      this.$eos.getters.getTable("items").then(res => (this.items = res));
    },
    call(asyncMethod) {
      asyncMethod.then(() => this.update());
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
