

static void bench_map_set_string(benchmark::State& state) {
    std::map<std::string, std::string> dict;
    for (auto _: state) {
        dict["name"] = "ljw";
    }
}

static void bench_map_set_number(benchmark::State& state) {
    std::map<std::string, int> dict;
    int score = 0;
    for (auto _: state) {
        dict["score"] = score++;
    }
}

BENCHMARK(bench_map_set_string);
BENCHMARK(bench_map_set_number);
