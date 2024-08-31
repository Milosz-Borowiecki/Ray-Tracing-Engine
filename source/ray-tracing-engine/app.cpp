#include "app.h"

App::App(){
#if 1
    m_scene = complexScene();

    constexpr point3 lookfrom(13,2,3);
    constexpr point3 lookat(0,0,0);
    constexpr point3 vup(0,1,0);
    constexpr auto dist_to_focus = 10.0f;
    constexpr auto aperture = 0.0f;
#else
    //HittableList world = simpleScene();

    constexpr point3 lookfrom(3,3,2);
    constexpr point3 lookat(0,0,-1);
    constexpr glm::vec3 vup(0,1,0);
    const auto dist_to_focus = glm::length((lookfrom - lookat));
    constexpr auto aperture = 0.1f;
#endif
}

void App::startRender(){
    std::cout << "P3\n" << m_camera.getWidth() << ' ' << m_camera.getHeight() << "\n255\n";

    auto start = std::chrono::high_resolution_clock::now();

    m_renderer.render(m_camera,m_scene);

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cerr << "Time taken to render: "<< duration.count() << " milliseconds\n";

    std::cerr << "\nDone.\n";
}