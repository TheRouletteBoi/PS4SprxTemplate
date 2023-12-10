#pragma once
#include "file_manager/file_manager.hpp"
#include "file_manager/cache_file.hpp"

#include "memory/batch.hpp"
//#include "memory/byte_patch.hpp"
#include "memory/module.hpp"


namespace Nutella
{
    class pointers
    {
    public:
        explicit pointers();
        ~pointers();

    public:
        void* rage_scrThreadRun{};
    };

    inline pointers* g_pointers{};
}
