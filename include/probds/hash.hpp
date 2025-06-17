#ifndef PROBDS_HASH_HPP
#define PROBDS_HASH_HPP

#include <cstdint>
#include <string_view>

namespace probds {

inline std::uint64_t fnv1a(std::string_view data) {
    constexpr std::uint64_t FNV_OFFSET = 14695981039346656037ull;
    constexpr std::uint64_t FNV_PRIME  = 1099511628211ull;
    std::uint64_t hash = FNV_OFFSET;
    for (unsigned char c : data) {
        hash ^= c;
        hash *= FNV_PRIME;
    }
    return hash;
}

} // namespace probds

#endif // PROBDS_HASH_HPP
