#include <thread>
#include <functional>
#include <future>
#include <thread>
#include <functional>
#include <cstdlib>
#include "file_manager/file_manager.hpp"
#include "offsets/pointers.hpp"


#define okay(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)
#define warn(msg, ...) printf("[-] " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) printf("[i] " msg "\n", ##__VA_ARGS__)



/***
* TODO: 
* file manager is good but try to implement it without globals
* rework pointers and pattern scanner (maybe combine them into a single memory.hpp file)
* 
* 
* BUG: 
* batch.cpp crash the game when sprx is injected
* 
*/

__BEGIN_DECLS
int module_start(size_t args, const void* argp)
{
    using namespace Nutella;
    info("module_start");


    std::string base_dir = "/data/";
    base_dir += "RainbowSixSiegePS4";
    g_file_manager.init(base_dir);

    g_file_manager.get_project_file("cache/pointers.bin");


    auto pointers_instance = std::make_unique<pointers>();
    printf("Pointers initialized.\n");


    printf("\\___[ rage_scrThreadRun\n\t\\0x%p]\n\t\\0x%p\n", g_pointers->rage_scrThreadRun, memory::MemoryToIDA(g_pointers->rage_scrThreadRun));

    return 0;
}

int module_stop(size_t args, const void* argp)
{

    return 0;
}
__END_DECLS