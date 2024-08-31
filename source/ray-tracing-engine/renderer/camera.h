#ifndef CAMERA_H
#define CAMERA_H

#include "../rtweekend.h"

class Camera {
    public:

        struct CameraSettings {
            point3 origin = point3(13,2,3);
            point3 direction = point3(0,0,0);
            glm::vec3 view_up = point3(0,1,0);
            float vertical_field_of_view = 20.0f;
            float aperture = 0.0f;
            uint32_t width = 1280;
            uint32_t height = 720;
            float focus_dist = 10.0f;
        }; 

        Camera();

        Ray getRay(const uint32_t& x_pos,const uint32_t& y_pos) const;

        Ray getNonRandomRay(const uint32_t& x_pos,const uint32_t& y_pos) const;
        
        point3 defocusDiskSample() const;

        const uint32_t getWidth() const { return m_cameraSettings.width; }

        const uint32_t getHeight() const { return m_cameraSettings.height; }

    private:
        CameraSettings m_cameraSettings;
        glm::vec3 u, v, w;
        glm::vec3 defocus_disk_u;
        glm::vec3 defocus_disk_v;
        glm::vec3 pixel_delta_u;
        glm::vec3 pixel_delta_v;
        point3 pixel00_loc;
};
#endif