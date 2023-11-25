#include "pointers.hpp"
#include "memory/all.hpp"

// https://github.com/YimMenu/YimMenu/tree/aa984a563698a8ec8f595a75438f7ca4887b6ea3/src

namespace Nutella
{
    pointers::~pointers()
    {
        g_pointers = nullptr;
    }
}
