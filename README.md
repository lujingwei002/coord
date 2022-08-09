# coord

###
[文档] (blob/main/doc/User Guide.md)
### 环境
- cmake 3.17.5
- g++ 7.3.1

### 编译coord
```bash
#安装依赖
cd coord/dep
make
make install

#编译
cd coord
mkdir build
cd build
cmake3 ..
make
```

### 测试
```bash
cd coord
bin/test
bin/test --gtest_filter=TestRedis.*
```

### 压力测试
```bash
cd coord
bin/benchmark
```
