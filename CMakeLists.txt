Project (anagramarama)
CMake_Minimum_Required (VERSION 3.1...4.0)

include(GNUInstallDirs)

Set (BINDIR "${CMAKE_INSTALL_BINDIR}" CACHE PATH "Where to install binaries")
Set (DATAROOTDIR "${CMAKE_INSTALL_DATAROOTDIR}" CACHE PATH "Sets the root of data directories to a non-default location")
Set (ICONDIR "${DATAROOTDIR}/icons" CACHE PATH "Sets the icon directory for desktop entry to a non-default location.")
Set (DESKTOPDIR "${DATAROOTDIR}/applications" CACHE PATH "Sets the desktop file directory for desktop entry to a non-default location.")

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)

# Find LibGamerzilla library
if (NOT APPLE)
    pkg_search_module(GAMERZILLA OPTIONAL gamerzilla)

    if (GAMERZILLA_LIBRARIES)
        message(STATUS "Gamerzilla found")
        add_definitions(-DGAMERZILLA)
    endif()
endif()


if(CMAKE_VERSION VERSION_LESS 3.20)
    set(dir DATAROOTDIR)
endif()
GNUInstallDirs_get_absolute_install_dir(DATAROOTDIR_FULL DATAROOTDIR DATAROOTDIR)

add_definitions(-DDATA_PATH=\"${DATAROOTDIR_FULL}/anagramarama\")

#Add the include directories of the (found) libraries.
Include_Directories(
	${SDL2_INCLUDE_DIRS}
	${SDL2_MIXER_INCLUDE_DIRS}
	${SDL2_IMAGE_INCLUDE_DIRS}
	${GAMERZILLA_INCLUDE_DIRS}
)

file(GLOB SOURCES src/dlb.c src/linked.c src/sprite.c src/ag_core.c src/ag.c src/sdlscale.c)

Add_Executable (anagramarama ${SOURCES})
Target_Link_Libraries (
	anagramarama
	${SDL2_LIBRARIES}
	${SDL2_MIXER_LIBRARIES}
	${SDL2_IMAGE_LIBRARIES}
	${GAMERZILLA_LIBRARIES}
)

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
endif ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
