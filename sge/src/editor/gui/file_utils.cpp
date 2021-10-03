#include "file_utils.h"

#include "engine/core/log.h"

#include <portable-file-dialogs/portable-file-dialogs.h>
#include <string>
#include <vector>

namespace SGE
{

namespace FileDialog
{

constexpr auto CURRENT_FOLDER = ".";

std::string save_file(const std::vector<std::string>& filters)
{
    return pfd::save_file("Select a file", CURRENT_FOLDER, filters,
                          pfd::opt::none)
        .result();
}

std::string open_file(const std::vector<std::string>& filters)
{
    auto filenames =
        pfd::open_file("Select a file", CURRENT_FOLDER, filters, pfd::opt::none)
            .result();

    if (filenames.empty()) {
        return std::string{};
    }

    return filenames[0];
}

} // namespace FileDialog

} // namespace SGE
