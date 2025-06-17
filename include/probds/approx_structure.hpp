#ifndef PROBDS_APPROX_STRUCTURE_HPP
#define PROBDS_APPROX_STRUCTURE_HPP

#include <string_view>

namespace probds {

class ApproxStructure {
public:
    virtual ~ApproxStructure() = default;

    // Insert a key into the structure
    virtual void add(std::string_view key) = 0;

    // Query membership or frequency depending on structure
    virtual bool query(std::string_view key) const = 0;

    // Merge another structure into this one
    virtual void merge(const ApproxStructure &other) = 0;

    // Expected error rate of the structure
    virtual double errorRate() const = 0;
};

} // namespace probds

#endif // PROBDS_APPROX_STRUCTURE_HPP
