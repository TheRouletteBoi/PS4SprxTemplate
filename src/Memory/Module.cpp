#include "module.hpp"
#include <thread>

namespace memory
{
    int GetModuleSize(SceKernelModuleInfo info)
    {
        int size = 0;
        for (int i = 0; i < info.segmentCount; i++)
        {
            size += info.segmentInfo[i].size;
        }
        return size;
    }

    uint64_t MemoryToIDA(const void* address)
    {
        return reinterpret_cast<uint64_t>(address) - 0x400000;
    }

    module::module(const std::string_view name) :range(nullptr, 0), m_name(name), m_loaded(false)
    {
        printf("module constructor\n");
        try_get_module();
    }

    handle module::get_export(std::string_view symbol_name)
    {
        return nullptr;
    }

    bool module::loaded() const
    {
        return m_loaded;
    }

    size_t module::size() const
    {
        return m_size;
    }

    bool module::wait_for_module(std::optional<std::chrono::high_resolution_clock::duration> time)
    {
        return false;
    }

    bool module::try_get_module()
    {
        printf("try_get_module\n");

        if (m_loaded)
            return m_loaded;

        SceKernelModuleInfo info{};
        info.size = sizeof(SceKernelModuleInfo);
        sceKernelGetModuleInfo(0, &info);
        const auto mod = info.segmentInfo[0].address;
        int module_size = GetModuleSize(info);

        printf("mod %d\n", mod);
        printf("module_size %d\n", module_size);

        if (!mod)
            return false;

        m_loaded = true;
        m_base = mod;
        m_size = module_size;

        return m_loaded;
    }
}
