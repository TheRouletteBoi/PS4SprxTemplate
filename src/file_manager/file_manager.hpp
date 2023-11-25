#pragma once
#include "file.hpp"
#include "folder.hpp"

namespace Nutella
{
    class file_manager final
    {
    public:
        file_manager() = default;
        virtual ~file_manager() = default;
        file_manager(const file_manager&) = delete;
        file_manager(file_manager&&) noexcept = delete;
        file_manager& operator=(const file_manager&) = delete;
        file_manager& operator=(file_manager&&) noexcept = delete;

        bool init(const std::string& base_dir);

        const std::string& get_base_dir();

        file get_project_file(const std::string& file_path);

        folder get_project_folder(const std::string& folder_path);

        static std::string ensure_file_can_be_created(const std::string& file_path);
        static std::string ensure_folder_exists(const std::string& folder_path);

    private:
        std::string m_base_dir;
    };

    inline auto g_file_manager = file_manager();
}