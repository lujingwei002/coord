

static void bench_protobuf_set_string(benchmark::State& state) {
    auto user = coorda->Proto->NewReflect("test.User");
    for (auto _: state) {
        user.SetString("nickname", "ljw");
    }
}

static void bench_protobuf_set_number(benchmark::State& state) {
    auto user = coorda->Proto->NewReflect("test.User");
    int score = 0;
    for (auto _: state) {
        user.SetNumber("score", score++);
    }
}

BENCHMARK(bench_protobuf_set_string);

BENCHMARK(bench_protobuf_set_number);
