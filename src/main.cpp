#include <thread>
#include <functional>
#include <future>
#include <thread>
#include <functional>
#include <cstdlib>
#include "FileManager/FileManager.hpp"


#define okay(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)
#define warn(msg, ...) printf("[-] " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) printf("[i] " msg "\n", ##__VA_ARGS__)

__BEGIN_DECLS
int module_start(size_t args, const void* argp)
{
    using namespace Nutella;
    info("module_start");


    std::string base_dir = "/data/";
    base_dir += "RainbowSixSiegePS4";
    g_file_manager.init(base_dir);

    g_file_manager.get_project_file("cache/pointers.bin");



    uint64_t* pGameManager = (uint64_t*)0x0;
    info("\\___[ pGameManager\n\t\\0x%p]\n", pGameManager);


    return 0;
}

int module_stop(size_t args, const void* argp)
{

    return 0;
}
__END_DECLS