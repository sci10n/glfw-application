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
    includedirs "Libraries/GLFW/include"
end 

-- This function links statically against GLFW
function linkGLFW()
    libdirs "Libraries/GLFW/lib"
    
    -- Our static lib should not link against GLFW
    filter "kind:not StaticLib"
        links "glfw3"
    filter {}
end

-- Our first project, the static library
project "ExampleLib"
    kind "StaticLib"
    files "Projects/ExampleLib/**"
    includeGLFW()

function useExampleLib()
    includedirs "Projects/ExampleLib"
    
    -- We link against a library that's in the same workspace, so we can just
    -- use the project name - premake is really smart and will handle everything for us.
    links "ExampleLib"
    linkGLFW()
end

-- The windowed app
project "App"
    kind "ConsoleApp"
    files "Projects/App/**"

    includedirs "Projects/ExampleLib"
    
    useExampleLib()
        
    filter { "system:windows" }
    links { "OpenGL32" }
        
    filter { "system:not windows" }
    links { "GL" }

-- We will use this function to include Catch
function includeCatch()
    -- Catch is header-only, we need just the Catch.hpp header
    includedirs "Libraries/Catch/include"
    
    -- We can also configure Catch through defines
    defines "CATCH_CPP11_OR_GREATER"
end

project "UnitTests"
    -- Catch prints information to the console
    kind "ConsoleApp"
    
    files "Projects/UnitTests/**"
    
    includeCatch()
    useExampleLib()