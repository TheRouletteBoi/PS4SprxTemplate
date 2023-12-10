#include "pointers.hpp"
#include "memory/all.hpp"

// https://github.com/YimMenu/YimMenu/tree/aa984a563698a8ec8f595a75438f7ca4887b6ea3/src


namespace Nutella
{
    pointers::pointers()
    {
        /*
        0x1F21120 ragescrThreadRun
        IDA: E8 ? ? ? ? 64 48 8B 0C 25 ? ? ? ? 4E 89 3C 29 
        CODE:  \xE8\x00\x00\x00\x00\x64\x48\x8B\x0C\x25\x00\x00\x00\x00\x4E\x89\x3C\x29, x????xxxxx????xxxx
        call    ragescrThreadRun
        */


        memory::batch main_batch;
        main_batch.add("rage::scrThreadRun", "E8 ? ? ? ? 64 48 8B 0C 25 ? ? ? ? 4E 89 3C 29 ", [this](memory::handle ptr) {

            printf("ptr %p", ptr);

            rage_scrThreadRun = ptr.rip().as<void*>();
        });


        auto mem_region = memory::module("eboot.bin");
        printf("eboot base address %p\n", mem_region);
        if (!main_batch.run(mem_region))
        {
            printf("failed to find some patterns\n");
            //throw std::runtime_error("Failed to find some patterns.");
        }
        else
        {
            printf("we found all patterns\n");
        }

        g_pointers = this;
    }

    pointers::~pointers()
    {
        g_pointers = nullptr;
    }
}
