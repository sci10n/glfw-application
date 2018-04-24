name = "project"
workspace (name)
    language "C++"
    location "build"
    architecture "x86_64"
    warnings "Extra"
    cppdialect "C++11"
    configurations {"Debug", "Release"}

    filter {"configurations:Debug"}
        debugdir "../" 
        defines {"DEBUG"}
        optimize "Off"
        symbols "On"

    filter {"configurations:Release"}
        defines {"RELEASE"}
        optimize "Speed"
        symbols "Off"

-- ==============================
-- GLFW Helper functions
-- ==============================

function includeGLFW()
    includedirs "lib/GLFW/include"
end 

function linkGLFW()
    libdirs "lib/GLFW/lib"
    
    -- Our static lib should not link against GLFW
    filter "kind:not StaticLib"
        links "glfw3"
    filter {}
end

-- ==============================
-- GLEW Helper functions
-- ==============================
function includeGLEW()
    includedirs "lib/GLEW/include"
end

function linkGLEW()
    libdirs "lib/GLEW/lib"
    
    -- Our static lib should not link against GLEW
    filter "kind:not StaticLib"
        links "glew32"
    filter {}
end

-- ==============================
-- Static linking helper functions
-- ==============================

function includeCatch()
    includedirs "lib/Catch/include"
    defines "CATCH_CPP11_OR_GREATER"
end

function includeGLM()
    includedirs "lib/GLM"
    defines "GLM_ENABLE_EXPERIMENTAL"
end

-- ==============================
-- Appwrapper project
-- ==============================

function useAppwrapper()
    includedirs {"projects/appwrapper"}
    links "appwrapper"
    linkGLFW()
    linkGLEW()
end

project "appwrapper"
    kind "StaticLib"
    files "projects/appwrapper/**"
    includedirs {"projects/appwrapper/include"}

    includeGLFW()
    includeGLEW()
    includeGLM()

-- Main application
project "app"
    kind "ConsoleApp"
    files "projects/app/**"
    includeGLFW()
    includeGLEW()
    includeGLM()

    includedirs {"projects/appwrapper/include"}
    useAppwrapper()
        
    filter { "system:windows" }
    links { "OpenGL32" }
        
    filter { "system:not windows" }
    links { "GL" }