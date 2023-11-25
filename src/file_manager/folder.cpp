#include "folder.hpp"
#include "file_manager.hpp"

namespace Nutella
{
    folder::folder(const std::string& folder_path) :
        m_folder_path(folder_path)
    {
    }

    file folder::get_file(std::string file_path) const
    {
        if (file_path.empty() || file_path[0] == '/')
            throw std::invalid_argument("folder#get_file requires a relative path.");

        if (file_path.find("..") != std::string::npos)
            throw std::invalid_argument("Relative path traversal is not allowed, refrain from using \"..\" in file paths.");

        return file(m_folder_path + '/' + file_path);
    }

    const std::string folder::get_path() const
    {
        return m_folder_path;
    }
}