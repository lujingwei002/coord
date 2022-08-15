


static void bench_json_array(benchmark::State& state) {
    for (auto _: state) {
        auto json = coorda->Json->NewArray();   
        auto book1 = json->AddObject();
        book1->SetString("name", "c++");
        auto book2 = json->AddObject();
        book2->SetString("name", "lua");
    }
}

static void bench_json_object(benchmark::State& state) {
    for (auto _: state) {
        auto json1 = coorda->Json->NewObject();   
        json1->SetString("name", "c++");
        auto json2 = coorda->Json->NewObject();   
        json2->SetString("name", "c++");
    }
}

static void bench_json_object_set_string(benchmark::State& state) {
    auto json = coorda->Json->NewObject();  
    for (auto _: state) { 
        json->SetString("name", "c++");
    }
}

static void bench_json_object_set_number(benchmark::State& state) {
    auto json = coorda->Json->NewObject(); 
    int score = 0; 
    for (auto _: state) { 
        json->SetNumber("score", score++);
    }
}

static void bench_json_object_tostring(benchmark::State& state) {
    auto json = coorda->Json->NewObject();  
    json->SetString("name", "c++");
    for (auto _: state) { 
        json->ToString();
    }
}

static void bench_json_object_decode(benchmark::State& state) {
    for (auto _: state) { 
        auto json = coorda->Json->Decode(R"({"b":{"d":1,"c":"hello","t":{"nickname":"lj\nw","score":100,"avatar":"xx"}}})"); 
    }
}

BENCHMARK(bench_json_array);
BENCHMARK(bench_json_object);
BENCHMARK(bench_json_object_set_string);
BENCHMARK(bench_json_object_set_number);
BENCHMARK(bench_json_object_tostring);
BENCHMARK(bench_json_object_decode);
