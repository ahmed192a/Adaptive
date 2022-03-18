#ifndef ARA_CRYPTO_MEM_REGION_H
#define ARA_CRYPTO_MEM_REGION_H

#include <cstdint>
#include <vector>

namespace ara
{
  namespace crypto
  {
    
    // should be std::span but not supported in c++17
    using ReadOnlyMemRegion = std::vector<const std::uint8_t>;

    // should be std::span but not supported in c++17
    using ReadWriteMemRegion = std::vector<std::uint8_t>;


  } // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_MEM_REGION_H