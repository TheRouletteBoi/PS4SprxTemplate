#include "file_manager.hpp"

#include <_fs.h>

namespace Nutella
{
    bool file_manager::init(const std::string& base_dir)
    {
        m_base_dir = base_dir;
        file_manager::ensure_folder_exists(m_base_dir);

        return true;
    }

    const std::string& file_manager::get_base_dir()
    {
        return m_base_dir;
    }

    file file_manager::get_project_file(const std::string& file_path)
    {
        if (!file_path.empty() && file_path[0] == '/')
            throw std::invalid_argument("Project files are relative to the BaseDir, don't use absolute paths!");
        if (file_path.find("..") != std::string::npos)
            throw std::invalid_argument("Relative path traversal is not allowed, refrain from using \"..\" in file paths.");

        return file_manager::ensure_file_can_be_created(m_base_dir + '/' + file_path);
    }

    folder file_manager::get_project_folder(const std::string& folder_path)
    {
        if (!folder_path.empty() && folder_path[0] == '/')
            throw std::invalid_argument("Project folders are relative to the BaseDir, don't use absolute paths!");
        if (folder_path.find("..") != std::string::npos)
            throw std::invalid_argument("Relative path traversal is not allowed, refrain from using \"..\" in folder paths.");

        return file_manager::ensure_folder_exists(m_base_dir + '/' + folder_path);
    }

    std::string file_manager::ensure_file_can_be_created(const std::string& file_path)
    {
        std::string parent_path = file_path.substr(0, file_path.find_last_of('/'));

        // Ensure the parent directory exists
        file_manager::ensure_folder_exists(parent_path);

        // Try to create the file
        int fd = sceKernelOpen(file_path.c_str(), O_CREAT | O_EXCL | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd != -1) 
        {
            sceKernelClose(fd);
            return file_path;
        }
        else 
            printf("Error creating file\n");

        return file_path;
    }

    std::string file_manager::ensure_folder_exists(const std::string& folder_path)
    {
        SceKernelStat st;
        int statResult = sceKernelStat(folder_path.c_str(), &st);
        bool create_path = (statResult == -1);

        if (!create_path && !S_ISDIR(st.st_mode))
        {
            sceKernelUnlink(folder_path.c_str());
            create_path = true;
        }
        if (create_path)
            sceKernelMkdir(folder_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

        return folder_path;
    }
}
