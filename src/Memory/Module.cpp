#include "Module.hpp"
#include <thread>

namespace memory
{
    module::module(const std::string_view name) :range(nullptr, 0), m_name(name), m_loaded(false)
    {
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
        return false;
    }
}
