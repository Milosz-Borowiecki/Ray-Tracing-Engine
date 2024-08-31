#ifndef APP_H
#define APP_H

#include <chrono>
#include "hittableList.h"
#include "rtweekend.h"
#include "finalRender.h"
#include "renderer/renderer.h"
#include "renderer/camera.h"

class App {
    public:
        App();

        void startRender();

    private:
        Renderer m_renderer;
        Camera m_camera;
        Scene m_scene;
};

#endif