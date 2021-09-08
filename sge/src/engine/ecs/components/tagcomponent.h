#ifndef _SGE_TAG_COMPONENT_H
#define _SGE_TAG_COMPONENT_H

#include <cstddef>
#include <string>

namespace SGE
{

class TagComponent
{
  private:
    std::string tag_;

  public:
    TagComponent() = default;
    TagComponent(const std::string& tag);

    const std::string& tag() const;
    std::string& tag()
    {
        return tag_;
    }
};

} // namespace SGE
#endif
