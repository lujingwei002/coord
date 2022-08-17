

static void bench_table_set_string(benchmark::State& state) {
    auto table = coord::script::Reflect(coorda);
    table.SetTable();
    for (auto _: state) {
        table.Set("name", "ljw");
    }
}

static void bench_table_set_number(benchmark::State& state) {
    auto table = coord::script::Reflect(coorda);
    table.SetTable();
    int score = 0;
    for (auto _: state) {
        table.SetNumber("score", score++);
    }
}

static void bench_table_json_parse(benchmark::State& state) {
    for (auto _: state) {
        coorda->Script->FromJson("a",  R"({"b":{"d":1,"c":"hello","t":{"nickname":"lj\nw","score":100,"avatar":"xx"}}})");
    }
}

BENCHMARK(bench_table_set_string);
BENCHMARK(bench_table_set_number);
BENCHMARK(bench_table_json_parse);
