cmake_minimum_required(VERSION 3.0)
project(CGA218)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
set(INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src")

##-------------------------------add your source files here-------------------------------------------------------------
##        new source paths must be added to the include list, if contained headers are used elsewhere!
## Framework/Assets
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Assets/AssetManager.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Assets/AssetManager.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Assets/ShaderProgram.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Assets/ShaderProgram.cpp")
# add that directory to include list:
list(APPEND INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Assets")

## Framework/Rendering
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Rendering/Primitives.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Rendering/Primitives.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Rendering/Texture2D.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Rendering/Texture2D.cpp")
# add that directory to include list:
list(APPEND INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Rendering")
## Framework/SceneElements
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Material.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Material.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Transform.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Transform.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Mesh.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Mesh.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Renderable.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Renderable.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Camera.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Camera.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/FreeCamera.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/FreeCamera.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/ThirdPersonCamera.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/ThirdPersonCamera.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/PointLight.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/PointLight.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Skybox.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Skybox.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/PixelEmitter.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/PixelEmitter.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/FireEmitter.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/FireEmitter.cpp")
# add that directory to include list:
list(APPEND INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements")
## Game
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Game/Game.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Game/Game.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Game/Scene.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Game/Scene.cpp")
# add that directory to include list:
list(APPEND INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src/Game")

##---------------------------------framework files----------------------------------------------------------------------
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/CommonTypes.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/fw_config.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/GameWindow.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/GameWindow.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/glerror.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/glerror.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/Input.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/Input.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/libheaders.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/OBJLoader.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/OBJLoader.cpp")
# add that directory to include list:
list(APPEND INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/framework")

##--------------------------------external dependencies-----------------------------------------------------------------
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs")

##--------------------------------executable target---------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)

add_executable(CGA218 ${SOURCES})
target_include_directories(
        CGA218
        PRIVATE ${INCLUDES}
)

target_link_libraries(CGA218 PUBLIC cga2fw_external_dependencies)

##-------------------------------copy assets to output------------------------------------------------------------------

file(COPY "assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")