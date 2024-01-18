cmake_minimum_required(VERSION 3.16)
project(lemmings)

# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/basic_frag.glsl ${CMAKE_CURRENT_BINARY_DIR}/shaders/basic_frag.glsl COPYONLY)
# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/basic_vert.glsl ${CMAKE_CURRENT_BINARY_DIR}/shaders/basic_vert.glsl COPYONLY)

file(COPY ${CMAKE_SOURCE_DIR}/Game/images DESTINATION ${CMAKE_BINARY_DIR})
#file(COPY ${CMAKE_SOURCE_DIR}/Game/levels DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Game/shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Game/sounds DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB levelFiles "${CMAKE_SOURCE_DIR}/Game/levels/*.txt")
foreach(file ${levelFiles})
    get_filename_component(file_name ${file} NAME)
    configure_file(${file} ${CMAKE_BINARY_DIR}/levels/${file_name} COPYONLY)
endforeach()


set(CMAKE_CXX_STANDARD 14)
add_executable(lemmings src/main.cpp
        src/EasyMaskManager.cpp
        src/DoorMaya.cpp
        src/Builder.cpp
        src/Digger.cpp
        src/Lemming.cpp
        src/NumDisplayGreen.cpp
        src/Sprite.cpp
        src/DoorFactory.cpp
        src/Walker.cpp
        src/DoorHell.cpp
        src/GreenNumFactory.cpp
        src/HardMaskManager.cpp
        src/Countdown.cpp
        src/PercentageDisplay.cpp
        src/ShaderProgram.cpp
        src/Climber.cpp
        src/Shader.cpp
        src/Menu.cpp
        src/JobAssigner.cpp
        src/DoorStandard.cpp
        src/InfoLevel.cpp
        src/Miner.cpp
        src/Button.cpp
        src/UserInterface.h
        src/UserInterface.cpp
        src/MaskedTexturedQuad.cpp
        src/TrapdoorFactory.cpp
        src/main.cpp
        src/Credits.cpp
        src/ShaderManager.cpp
        src/ParticleSystemManager.cpp
        src/Trapdoor.cpp
        src/NumDisplay.cpp
        src/UIAdapter.cpp
        src/ParticleFactory.cpp
        src/DoorEgypt.cpp
        src/Escaper.cpp
        src/LevelRunner.cpp
        src/ParticleSystem.cpp
        src/Exploder.cpp
        src/VariableTexture.cpp
        src/Utils.cpp
        src/Cursor.cpp
        src/PurpleNumFactory.cpp
        src/GameState.cpp
        src/Door.cpp
        src/Job.cpp
        src/LetterFactory.cpp
        src/Game.cpp
        src/Particle.cpp
        src/Instructions.cpp
        src/PredefinedWordFactory.cpp
        src/TrapdoorStandard.cpp
        src/ButtonFactory.cpp
        src/Floater.cpp
        src/Level.cpp
        src/JobFactory.cpp
        src/Basher.cpp
        src/Results.cpp
        src/TrapdoorHell.cpp
        src/Faller.cpp
        src/Blocker.cpp
        src/Scene.cpp
        src/Texture.cpp
        src/NumDisplayButton.cpp
        src/PurplePercentageDisplay.cpp
        src/StateManager.cpp
        src/Scroller.cpp
        src/KeyFactory.cpp
        src/TimeDisplay.cpp
        src/ButtonNumFactory.cpp
        src/Word.cpp
        src/LemmingsException.cpp
        src/TimerEventService.h
        src/TimerEventService.cpp
        src/LevelIndex.h
        src/LevelIndex.cpp
        src/MusicFabric.hpp
        libs/SOIL/src/image_helper.c
        libs/SOIL/src/image_helper.h
        libs/SOIL/src/image_DXT.h
        libs/SOIL/src/image_DXT.c
        libs/SOIL/src/SOIL.c
        libs/SOIL/src/SOIL.h
        libs/SOIL/src/stb_image_aug.c
        libs/SOIL/src/stb_image_aug.h
        libs/SOIL/src/stbi_DDS_aug.h
        libs/SOIL/src/stbi_DDS_aug_c.h src/ChangeSceneEvent.cpp src/UserEvent.h)


find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
message("Hallo: ${CMAKE_SOURCE_DIR}/libs")
include_directories(${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS}  ${GLEW_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/libs)
target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES}  SDL2_mixer)
