CMake_Minimum_Required (VERSION 3.10)
Project (anagramarama)

Set (BINDIR "bin" CACHE STRING "Where to install binaries")
Set (DATAROOTDIR "${CMAKE_INSTALL_PREFIX}/share" CACHE STRING "Sets the root of data directories to a non-default location")
Set (ICONDIR "${DATAROOTDIR}/icons" CACHE STRING "Sets the icon directory for desktop entry to a non-default location.")
Set (DESKTOPDIR "${DATAROOTDIR}/applications" CACHE STRING "Sets the desktop file directory for desktop entry to a non-default location.")

# Find SDL2 packages
find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Find LibGamerzilla library
if (NOT APPLE)
    include(FindPkgConfig)
    pkg_search_module(GAMERZILLA OPTIONAL gamerzilla)

    if (GAMERZILLA_LIBRARIES)
        message(STATUS "Gamerzilla found")
        add_definitions(-DGAMERZILLA)
    endif()
endif()

#add_definitions(-DDATA_PATH=\"${DATAROOTDIR}/anagramarama\")
add_definitions(-DDATA_PATH="${DATAROOTDIR}/anagramarama")

#Add the include directories of the (found) libraries.
Include_Directories(
	${SDL2_INCLUDE_DIRS}
	${SDL2_MIXER_INCLUDE_DIRS}
	${SDL2_IMAGE_INCLUDE_DIRS}
	${GAMERZILLA_INCLUDE_DIRS}
)

file(GLOB SOURCES src/dlb.c src/linked.c src/sprite.c src/ag_core.c src/ag.c src/sdlscale.c)

Add_Executable (anagramarama ${SOURCES})

# link lib
target_link_libraries(anagramarama PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer ${GAMERZILLA_LIBRARIES})

#file(GLOB TESTAG_SOURCES src/dlb.c src/linked.c src/sprite.c src/ag_core.c src/ag_test.c)

#Add_Executable (test_ag ${TESTAG_SOURCES})

#file(GLOB TESTAGCORE_SOURCES src/agcore_test.c src/dlb.c src/linked.c)

#Add_Executable (test_agcore ${TESTAGCORE_SOURCES})

#file(GLOB TESTLINKED_SOURCES src/linked.c)

#Add_Executable (test_agcore ${TESTLINKED_SOURCES})

#file(GLOB TESTDLB_SOURCES src/dlb.c)

#Add_Executable (test_agcore ${TESTDLB_SOURCES})

Install (TARGETS anagramarama RUNTIME DESTINATION ${BINDIR})
Install (DIRECTORY ${PROJECT_SOURCE_DIR}/audio ${PROJECT_SOURCE_DIR}/gamerzilla ${PROJECT_SOURCE_DIR}/i18n DESTINATION ${DATAROOTDIR}/anagramarama/)

if ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
	Install (FILES man/anagramarama.6 DESTINATION ${DATAROOTDIR}/man/man6/)
	Install (FILES anagramarama.desktop DESTINATION ${DESKTOPDIR})
	Install (FILES anagramarama.metainfo.xml DESTINATION ${DATAROOTDIR}/metainfo/)
	Install (FILES icons/16x16/anagramarama.png DESTINATION ${ICONDIR}/hicolor/16x16/apps/)
	Install (FILES icons/32x32/anagramarama.png DESTINATION ${ICONDIR}/hicolor/32x32/apps/)
	Install (FILES icons/48x48/anagramarama.png DESTINATION ${ICONDIR}/hicolor/48x48/apps/)
	Install (FILES icons/64x64/anagramarama.png DESTINATION ${ICONDIR}/hicolor/64x64/apps/)
	Install (FILES icons/128x128/anagramarama.png DESTINATION ${ICONDIR}/hicolor/128x128/apps/)
endif ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
