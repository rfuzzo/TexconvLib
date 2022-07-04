cmake_minimum_required(VERSION 3.5)
project(texconv)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/CMake")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/CMake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/CMake")

file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/bin/CMake")

set(CMAKE_CXX_STANDARD 17)
# disable on win build
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

function(add_cxx_compiler_flags)
    set(CMAKE_REQUIRED_QUIET true)
    include(CheckCXXCompilerFlag)
    set(flags ${CMAKE_CXX_FLAGS})
    foreach(flag ${ARGV})
        string(REGEX REPLACE "[^_A-Za-z0-9]" "_" stripped_flag "${flag}")
        set(var "CXX_COMPILER_FLAG_${stripped_flag}")
        check_cxx_compiler_flag("${flag}" "${var}")
        if(${var})
            set(flags "${flags} ${flag}")
        endif()
    endforeach()
    set(CMAKE_CXX_FLAGS ${flags} PARENT_SCOPE)
endfunction()
add_cxx_compiler_flags(-pedantic -fno-permissive -pedantic-errors -Wall -Wextra -Wshadow -Wstrict-aliasing -Wno-misleading-indentation "-ftemplate-depth=1024")


include_directories(.)


# DXTEX options

option(BUILD_TOOLS "Build tex command-line tools" ON)

option(BUILD_SAMPLE "Build DDSView sample" ON)

# Includes the functions for Direct3D 11 resources and DirectCompute compression
option(BUILD_DX11 "Build with DirectX11 Runtime support" ON)

# Includes the functions for creating Direct3D 12 resources at runtime
option(BUILD_DX12 "Build with DirectX12 Runtime support" ON)

# Enable the use of OpenMP for software BC6H/BC7 compression
option(BC_USE_OPENMP "Build with OpenMP support" ON)

option(ENABLE_CODE_ANALYSIS "Use Static Code Analysis on build" OFF)

option(USE_PREBUILT_SHADERS "Use externally built HLSL shaders" OFF)

# Includes the functions for loading/saving OpenEXR files at runtime
# NOTE requires adding DirectXTexEXR.h/.cpp source files (vcpkg does this automatically)
option(ENABLE_OPENEXR_SUPPORT "Build with OpenEXR support" OFF)




set(LIBRARY_HEADERS
    ../DirectXTex/DirectXTex/DirectXTex.h
    ../DirectXTex/DirectXTex/DirectXTex.inl  
)

set(LIBRARY_SOURCES
    ../DirectXTex/DirectXTex/BC.h
    ../DirectXTex/DirectXTex/DDS.h
    ../DirectXTex/DirectXTex/DirectXTexP.h
    ../DirectXTex/DirectXTex/filters.h
    ../DirectXTex/DirectXTex/scoped.h

    ../DirectXTex/DirectXTex/BC.cpp
    ../DirectXTex/DirectXTex/BC4BC5.cpp
    ../DirectXTex/DirectXTex/BC6HBC7.cpp
    ../DirectXTex/DirectXTex/DirectXTexCompress.cpp
    ../DirectXTex/DirectXTex/DirectXTexConvert.cpp
    ../DirectXTex/DirectXTex/DirectXTexDDS.cpp
    ../DirectXTex/DirectXTex/DirectXTexHDR.cpp
    ../DirectXTex/DirectXTex/DirectXTexImage.cpp
    ../DirectXTex/DirectXTex/DirectXTexMipmaps.cpp
    ../DirectXTex/DirectXTex/DirectXTexMisc.cpp
    ../DirectXTex/DirectXTex/DirectXTexNormalMaps.cpp
    ../DirectXTex/DirectXTex/DirectXTexPMAlpha.cpp
    ../DirectXTex/DirectXTex/DirectXTexResize.cpp
    ../DirectXTex/DirectXTex/DirectXTexTGA.cpp
    ../DirectXTex/DirectXTex/DirectXTexUtil.cpp       
)

if(WIN32)
   set(LIBRARY_SOURCES ${LIBRARY_SOURCES}
       ../DirectXTex/DirectXTex/DirectXTexFlipRotate.cpp
       ../DirectXTex/DirectXTex/DirectXTexWIC.cpp)
endif()

set(SHADER_SOURCES
    ../DirectXTex/DirectXTex/Shaders/BC6HEncode.hlsl
    ../DirectXTex/DirectXTex/Shaders/BC7Encode.hlsl)

if(BUILD_DX11 AND WIN32)
   set(LIBRARY_SOURCES ${LIBRARY_SOURCES}
       ../DirectXTex/DirectXTex/BCDirectCompute.h
       ../DirectXTex/DirectXTex/BCDirectCompute.cpp
       ../DirectXTex/DirectXTex/DirectXTexCompressGPU.cpp
       ../DirectXTex/DirectXTex/DirectXTexD3D11.cpp)
endif()






if(BUILD_DX11 AND WIN32)
    if (NOT COMPILED_SHADERS)
        if (USE_PREBUILT_SHADERS)
            message(FATAL_ERROR "ERROR: Using prebuilt shaders requires the COMPILED_SHADERS variable is set")
        endif()
        set(COMPILED_SHADERS ${CMAKE_CURRENT_BINARY_DIR}/Shaders/Compiled)
        file(MAKE_DIRECTORY ${COMPILED_SHADERS})
    else()
        file(TO_CMAKE_PATH ${COMPILED_SHADERS} COMPILED_SHADERS)
    endif()

    set(LIBRARY_SOURCES ${LIBRARY_SOURCES}
        ${COMPILED_SHADERS}/BC6HEncode_EncodeBlockCS.inc)

    if (NOT USE_PREBUILT_SHADERS)
        add_custom_command(
            OUTPUT "${COMPILED_SHADERS}/BC6HEncode_EncodeBlockCS.inc"
            MAIN_DEPENDENCY "${PROJECT_SOURCE_DIR}/../DirectXTex/DirectXTex/Shaders/CompileShaders.cmd"
            DEPENDS ${SHADER_SOURCES}
            COMMENT "Generating HLSL shaders..."
            COMMAND ${CMAKE_COMMAND} -E env CompileShadersOutput="${COMPILED_SHADERS}" CompileShaders.cmd > "${COMPILED_SHADERS}/compileshaders.log"
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/../DirectXTex/DirectXTex/Shaders"
            USES_TERMINAL)
    endif()
endif()

# dbg
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "COMPILED_SHADERS: ${COMPILED_SHADERS}")
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}")

add_library(${PROJECT_NAME} SHARED
        DirectXTexEnums.h
        Texconv.h
        Texconv.cpp
        Format.cpp
        Metadata.cpp
        ${LIBRARY_HEADERS}
        ${LIBRARY_SOURCES})

#add_executable(main
#        DirectXTexEnums.h
#        Texconv.h
#        Texconv.cpp
#        Format.cpp
#        Metadata.cpp
#        ${LIBRARY_HEADERS}
#        ${LIBRARY_SOURCES} main.cpp)

if(BUILD_DX11 AND WIN32)
   target_include_directories(${PROJECT_NAME} PRIVATE ${COMPILED_SHADERS})
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /permissive- /JMC- /Zc:__cplusplus)


    if(BC_USE_OPENMP)
        target_compile_options(${PROJECT_NAME} PRIVATE /openmp /Zc:twoPhase-)
        # target_compile_options(main PRIVATE /openmp /Zc:twoPhase-)
    endif()


endif()