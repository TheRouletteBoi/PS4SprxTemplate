#include "File.hpp"
#include "FileManager.hpp"

#include <_fs.h>

namespace Nutella
{
    file::file(const std::string& file_path) :
        m_file_path(file_path)
    {
    }

    void file::operator=(const file& other)
    {
        m_file_path = other.m_file_path;
    }

    file::operator std::string()
    {
        return m_file_path;
    }

    file::operator std::string& ()
    {
        return m_file_path;
    }

    bool file::exists() const
    {
        SceKernelStat st;
        return (sceKernelStat(m_file_path.c_str(), &st) == 0);
    }

    const std::string file::get_path() const
    {
        return m_file_path;
    }

    file file::move(std::string new_path)
    {
        FILE* file = fopen(new_path.c_str(), "w");
        if (file != nullptr)
            fclose(file);
        else
            throw std::runtime_error("Error creating file at the new path");

        if (!is_absolute_path(new_path))
            new_path = combine_paths(get_parent_path(m_file_path), new_path);

        if (sceKernelRename(m_file_path.c_str(), new_path.c_str()) != 0)
            throw std::runtime_error("Error moving file");

        return { new_path };
    }

    bool file::is_absolute_path(const std::string& path)
    {
        return !path.empty() && path[0] == '/';
    }

    std::string file::get_parent_path(const std::string& file_path)
    {
        size_t last_slash = file_path.find_last_of('/');
        if (last_slash != std::string::npos)
            return file_path.substr(0, last_slash);
        return "";
    }

    std::string file::combine_paths(const std::string& path1, const std::string& path2)
    {
        if (path1.empty() || is_absolute_path(path2))
            return path2;
        else
            return path1 + "/" + path2;
    }
}