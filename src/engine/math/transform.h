#ifndef _SGE_TRANSFORM_H
#define _SGE_TRANSFORM_H

#include "camera.h"
#include "matrix4.h"
#include "vector3.h"

namespace Math {
    class Transform {
        private:
            Camera camera_;
            Vector3 translation_;
            Vector3 rotation_;
            Vector3 scale_{1,1,1};

            inline static float z_near_;
            inline static float z_far_;
            inline static float width_;
            inline static float height_;
            inline static float fov_;

        public:
            void set_translation(const Vector3& translation_vector);
            void set_rotation(const Vector3& rotation_vector);
            void set_scale(const Vector3& scale_vector);
            void set_camera(const Camera& camera);
            Camera& get_camera();
            static void set_projection(float fov, float width, float height, float z_near, float z_far);
            Matrix4 get_transformation() const;
            Matrix4 get_projected_transformation() const;
    };
} // namespace Math
#endif
