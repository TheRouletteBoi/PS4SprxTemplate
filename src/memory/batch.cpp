#include "batch.hpp"

#include "range.hpp"

#include <future> // std::async

// not needed
#include <mutex>
#include <vector>
#include <functional>
#include <optional>


static std::mutex s_entry_mutex;
static std::vector<std::future<bool>> g_futures;

namespace memory
{
    void batch::add(std::string name, pattern pattern, std::function<void(handle)> callback)
    {
        m_entries.emplace_back(std::move(name), std::move(pattern), std::move(callback));
    }

    bool scan_pattern_and_execute_callback(range region, memory::batch::entry entry)
    {
        printf("scan_pattern_and_execute_callback()\n");

        if (std::optional<handle> result = region.scan(entry.m_pattern))
        {
            printf("passed result\n");

            if (entry.m_callback)
            {
                printf("passed callback\n");

                std::lock_guard<std::mutex> lock(s_entry_mutex);// Acquire a lock on the mutex to synchronize access.
                
                printf("lock guard\n");

                std::invoke(std::move(entry.m_callback), *result);

                printf("passed invoke\n");

                return true;
            }
        }

        return false;
    }

    bool batch::run(range region)
    {
        printf("bath::run\n");

        printf("range begin %p\n", region.begin().as<void*>());
        printf("range end %p\n", region.end().as<void*>());
        printf("range size %p\n", region.size());

        for (auto& entry : m_entries)
        {
            printf("adding pattern to queue\n");

            // async is broken and crashes internally.

            g_futures.emplace_back(std::async(std::launch::async, scan_pattern_and_execute_callback, region, entry));
        }

        bool found_all_patterns = true;
        for (auto& future : g_futures)
        {
            printf("waitting for future\n");

            future.wait();

            printf("getting pointers\n");
            if (!future.get())
            {
                found_all_patterns = false;
                printf("get failed\n");
            }
        }


        printf("clear all\n");
        m_entries.clear();
        g_futures.clear();

        return found_all_patterns;
    }
}