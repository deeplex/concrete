
// Copyright Henrik Steffen Gaßmann 2023.
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <climits>
#include <random>

#include <dplx/cncr/uuid.hpp>

namespace dplx::cncr
{

template <std::uniform_random_bit_generator UniformRandomNumberGenerator>
class random_uuidv4_generator
{
public:
    using result_type = uuid;
    using part_type = std::uint64_t;
    using engine_type = std::conditional_t<
            UniformRandomNumberGenerator::max()
                            - UniformRandomNumberGenerator::min()
                    >= std::numeric_limits<part_type>::max(),
            UniformRandomNumberGenerator,
            std::independent_bits_engine<UniformRandomNumberGenerator,
                                         sizeof(part_type) * CHAR_BIT,
                                         part_type>>;

private:
    engine_type mEngine;

public:
    random_uuidv4_generator() = default;

    explicit random_uuidv4_generator(UniformRandomNumberGenerator const &gen)
        : mEngine(gen)
    {
    }
    explicit random_uuidv4_generator(UniformRandomNumberGenerator &&engine)
        : mEngine(static_cast<engine_type &&>(engine))
    {
    }
    template <typename SeedSeq>
    explicit random_uuidv4_generator(SeedSeq &seq)
        : mEngine(seq)
    {
    }

    [[nodiscard]] auto base() const noexcept -> engine_type const &
    {
        return mEngine;
    }
    [[nodiscard]] auto underlying() const noexcept
            -> UniformRandomNumberGenerator const &
    {
        if constexpr (std::is_same_v<engine_type, UniformRandomNumberGenerator>)
        {
            return mEngine;
        }
        else
        {
            return mEngine.base();
        }
    }

    static constexpr auto min() noexcept -> uuid
    {
        return uuid("00000000-0000-4000-8000-000000000000");
    }
    static constexpr auto max() noexcept -> uuid
    {
        return uuid("ffffffff-ffff-4fff-bfff-ffffffffffff");
    }

    template <typename SeedSeq>
    void seed(SeedSeq &seq)
    {
        mEngine.seed(seq);
    }

    [[nodiscard]] auto operator()() -> uuid
    {
        blob<part_type, uuid::state_size / sizeof(part_type)> state{
                static_cast<part_type>(mEngine()),
                static_cast<part_type>(mEngine()),
        };
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        // set version field to 4
        state.values[0] = (state.values[0] & 0xffff'ffff'ffff'0fffU)
                        | 0x0000'0000'0000'4000U;
        // set variant field to 0b10
        state.values[1] = (state.values[1] & 0x3fff'ffff'ffff'ffffU)
                        | 0x8000'0000'0000'0000U;
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        return std::bit_cast<uuid>(state);
    }

    void discard(unsigned long long const z)
    {
        for (unsigned i = 0U; i < uuid::state_size / sizeof(part_type); ++i)
        {
            mEngine.discard(z);
        }
    }
};

} // namespace dplx::cncr
