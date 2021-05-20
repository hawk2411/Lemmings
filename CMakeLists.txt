cmake_minimum_required(VERSION 3.17)
project(lemmings)

# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/basic_frag.glsl ${CMAKE_CURRENT_BINARY_DIR}/shaders/basic_frag.glsl COPYONLY)
# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/basic_vert.glsl ${CMAKE_CURRENT_BINARY_DIR}/shaders/basic_vert.glsl COPYONLY)

file(COPY ${CMAKE_SOURCE_DIR}/Game/images DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Game/levels DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Game/shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Game/sounds DESTINATION ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)
add_executable(lemmings src/main.cpp
       src/Game.cpp
       src/main.cpp
       src/SoundManager.cpp
        src/Sound.cpp
        src/LemmingsException.cpp
        src/TimerEventService.h
        src/TimerEventService.cpp
        src/StateManager.cpp
        src/Texture.cpp
        src/Difficulties.h
        src/Sprite.cpp
        src/GameState.cpp
        src/Menu.cpp
        src/ShaderManager.cpp
        src/ShaderProgram.cpp
        src/Shader.cpp
        src/Credits.cpp
        src/Instructions.cpp
        src/Word.cpp
        src/LetterFactory.cpp
        src/Utils.cpp
        src/KeyFactory.h
        src/KeyFactory.cpp
        src/InfoLevel.h
        src/InfoLevel.cpp
        src/EventCreator.h
        src/EventCreator.cpp
        libs/SOIL/src/image_helper.c
        libs/SOIL/src/image_helper.h
        libs/SOIL/src/image_DXT.h
        libs/SOIL/src/image_DXT.c
        libs/SOIL/src/SOIL.c
        libs/SOIL/src/SOIL.h
        libs/SOIL/src/stb_image_aug.c
        libs/SOIL/src/stb_image_aug.h
        libs/SOIL/src/stbi_DDS_aug.h
        libs/SOIL/src/stbi_DDS_aug_c.h

        src/TimerEventService.cpp src/TimerEventService.h src/EventCreator.cpp src/EventCreator.h)


find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
find_package(fmod REQUIRED)

#set(GLM_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/libs/glm)
#message("GLM include  ${GLM_INCLUDE_DIRS} ")
message("GLM libs ${GLM_LIBRARIES}")
message("Fmod include dir: ${FMOD_INCLUDE_DIR}")
message("Fmod core lib dir: ${FMOD_CORE_LIBRARY}")
message("Fmod studio lib ${FMOD_STUDIO_LIBRARY}")
message("FMOD_FSBANK_LIBRARY ${FMOD_FSBANK_LIBRARY}")
message("FMOD_FSBVORBIS_LIBRARY ${FMOD_FSBVORBIS_LIBRARY}")
message("FMOD_OPUS_LIBRARY ${FMOD_OPUS_LIBRARY}")

#-fuse-ld=gold
#${GLM_INCLUDE_DIRS}
#${GLUT_INCLUDE_DIRS}
#${GLUT_LIBRARY}
include_directories(${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS}  ${GLEW_INCLUDE_DIRS} ${FMOD_INCLUDE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${GLM_LIBRARIES} ${FMOD_CORE_LIBRARY} ${FMOD_STUDIO_LIBRARY})
