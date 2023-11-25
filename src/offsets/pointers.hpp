#pragma once
#include "file_manager/file_manager.hpp"
#include "file_manager/cache_file.hpp"

#include "memory/batch.hpp"
//#include "memory/byte_patch.hpp"
#include "memory/module.hpp"


namespace Nutella
{
    template<uint32_t hash>
    struct compile_time_helper
    {
        static_assert(hash == -1);
        static constexpr bool print_hash = (hash == -1);
    };

    class pointers
    {
    private:

    public:
        explicit pointers();
        ~pointers();

    private:
        cache_file m_gta_pointers_cache;
        cache_file m_sc_pointers_cache;

    public:
    };

    inline pointers* g_pointers{};
}
