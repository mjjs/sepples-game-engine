#ifndef _GE_TRANSFORM_H
#define _GE_TRANSFORM_H

#include "matrix4.h"
#include "vector3.h"

namespace Math {
    class Transform {
        private:
            Vector3 translation;

        public:
            explicit Transform(const Vector3& translation);
            Matrix4 get_transformation() const;
    };
} // namespace Math
#endif
