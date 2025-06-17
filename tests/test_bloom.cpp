#include <cassert>
#include "probds/bloom_filter.hpp"
#include <string>

int main() {
    probds::BloomFilter bf(1024, 3);
    const std::string key = "hello";
    assert(!bf.query(key));
    bf.add(key);
    assert(bf.query(key));
    return 0;
}
