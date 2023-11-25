#pragma once
#include <string>

namespace Nutella
{
    class file;
    class file_manager;

    class folder
    {
    public:
        folder(const std::string& folder_path = "");

        file get_file(std::string file_path) const;
        const std::string get_path() const;

    private:
        friend class file_manager;
        file_manager* m_file_manager;

        bool m_is_project_file;

        std::string m_folder_path;
    };
}