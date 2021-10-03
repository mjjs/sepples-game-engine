#ifndef _SGE_FILE_UTILS_H
#define _SGE_FILE_UTILS_H

#include <string>
#include <vector>

namespace SGE
{

namespace FileDialog
{

std::string save_file(const std::vector<std::string>& filters);
std::string open_file(const std::vector<std::string>& filters);

} // namespace FileDialog

} // namespace SGE

#endif
