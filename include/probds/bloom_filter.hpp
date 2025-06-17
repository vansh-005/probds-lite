#ifndef PROBDS_BLOOM_FILTER_HPP
#define PROBDS_BLOOM_FILTER_HPP

#include "approx_structure.hpp"
#include "hash.hpp"
#include <vector>
#include <cstdint>
#include <cmath>
#include <bit>

namespace probds {

class BloomFilter : public ApproxStructure {
public:
    BloomFilter(std::size_t bits, std::size_t hashes)
        : m_bits(bits), m_hashes(hashes), m_data((bits + 63) / 64) {}

    void add(std::string_view key) override {
        auto h1 = fnv1a(key);
        auto h2 = fnv1a(std::string_view(reinterpret_cast<const char*>(&h1), sizeof(h1)));
        for (std::size_t i = 0; i < m_hashes; ++i) {
            std::size_t idx = (h1 + i * h2) % m_bits;
            m_data[idx / 64] |= (1ull << (idx % 64));
        }
    }

    bool query(std::string_view key) const override {
        auto h1 = fnv1a(key);
        auto h2 = fnv1a(std::string_view(reinterpret_cast<const char*>(&h1), sizeof(h1)));
        for (std::size_t i = 0; i < m_hashes; ++i) {
            std::size_t idx = (h1 + i * h2) % m_bits;
            if (!(m_data[idx / 64] & (1ull << (idx % 64))))
                return false;
        }
        return true;
    }

    void merge(const ApproxStructure &other) override {
        const auto *o = dynamic_cast<const BloomFilter*>(&other);
        if (!o || o->m_bits != m_bits || o->m_hashes != m_hashes)
            return; // incompatible
        for (std::size_t i = 0; i < m_data.size(); ++i)
            m_data[i] |= o->m_data[i];
    }

    double errorRate() const override {
        double exp = static_cast<double>(-static_cast<long double>(m_hashes) * m_size / m_bits);
        double prob = std::pow(1.0 - std::exp(exp), m_hashes);
        return prob;
    }

    std::size_t capacity() const { return m_bits; }

private:
    std::size_t m_bits;
    std::size_t m_hashes;
    std::vector<std::uint64_t> m_data;
    std::size_t m_size{0};
};

} // namespace probds

#endif // PROBDS_BLOOM_FILTER_HPP
