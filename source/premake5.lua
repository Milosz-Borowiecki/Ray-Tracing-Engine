project "RayTracingEngine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir("../bin/" .. outputdir .. "/%{prj.name}")
    objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "ray-tracing-engine/**.cpp",
        "ray-tracing-engine/**.h",
    }

    defines {
        "WINDOWS"
    }

    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "on"
    
    filter { "configurations:Release" }
        runtime "Release"
        optimize "on"
    