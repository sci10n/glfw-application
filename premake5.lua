name = "project"
workspace (name)
    language "C++"
    location "build"
    architecture "x86_64"
    warnings "Extra"
    cppdialect "C++11"
    configurations {"Debug", "Release"}

    filter {"configurations:Debug"}
        defines {"DEBUG"}
        optimize "Off"
        symbols "On"

    filter {"configurations:Release"}
        defines {"RELEASE"}
        optimize "Speed"
        symbols "Off"

-- This function includes GLFW's header files
function includeGLFW()
    includedirs "lib/GLFW/include"
end 

-- This function links statically against GLFW
function linkGLFW()
    libdirs "lib/GLFW/lib"
    
    -- Our static lib should not link against GLFW
    filter "kind:not StaticLib"
        links "glfw3"
    filter {}
end

-- Our first project, the static library
project "libexample"
    kind "StaticLib"
    files "projects/libexample/**"
    includeGLFW()

function useExampleLib()
    includedirs "projects/libexample"
    links "libexample"
    linkGLFW()
end

project "applciation"
    kind "ConsoleApp"
    files "projects/app/**"

    includedirs "projects/libexample"
    
    useExampleLib()
        
    filter { "system:windows" }
    links { "OpenGL32" }
        
    filter { "system:not windows" }
    links { "GL" }

-- We will use this function to include Catch
function includeCatch()
    -- Catch is header-only, we need just the Catch.hpp header
    includedirs "lib/Catch/include"
    
    -- We can also configure Catch through defines
    defines "CATCH_CPP11_OR_GREATER"
end

project "tests"
    -- Catch prints information to the console
    kind "ConsoleApp"
    
    files "projects/tests/**"
    
    includeCatch()
    useExampleLib()