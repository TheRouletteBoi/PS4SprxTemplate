#pragma once
#include <string>

namespace Nutella
{
    class file_manager;

    class file
    {
    public:
        file(const std::string& file_path = "");
        void operator=(const file& other);
        operator std::string();
        operator std::string& ();

        file copy(const std::string& new_path);
        bool exists() const;
        const std::string get_path() const;
        file move(std::string new_path);

    private:
        bool is_absolute_path(const std::string& path);
        std::string get_parent_path(const std::string& file_path);
        std::string combine_paths(const std::string& path1, const std::string& path2);

    private:
        friend class file_manager;

        bool m_is_project_file;
        std::string m_file_path;
    };
}