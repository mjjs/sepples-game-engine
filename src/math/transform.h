#ifndef _GE_TRANSFORM_H
#define _GE_TRANSFORM_H

#include "matrix4.h"
#include "vector3.h"

namespace Math {
    class Transform {
        private:
            Vector3 translation_;
            Vector3 rotation_;
            Vector3 scale_{1,1,1};

        public:
            void set_translation(const Vector3& translation_vector);
            void set_rotation(const Vector3& rotation_vector);
            void set_scale(const Vector3& scale_vector);
            Matrix4 get_transformation() const;
    };
} // namespace Math
#endif
