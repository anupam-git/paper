find_package(Qt5Core)

set(
    INTERACTORS

    interactors/FetchWallpaper.h
    interactors/FetchWallpaper.cpp

    interactors/RunAtInterval.h
    interactors/RunAtInterval.cpp

    interactors/SetWallpaper.h
    interactors/SetWallpaper.cpp
)

set(
    HELPERS

    helpers/ConfigHelper.h
    helpers/ConfigHelper.cpp

    helpers/DownloadHelper.h
    helpers/DownloadHelper.cpp

    helpers/FileHelper.h
    helpers/FileHelper.cpp

    helpers/ShellHelper.h
    helpers/ShellHelper.cpp
)

set(
    PARSERS

    parsers/ArgumentParser.h
    parsers/ArgumentParser.cpp

    parsers/ConfigParser.h
    parsers/ConfigParser.cpp
)

add_executable(
    ${PROJECT_NAME}

    main.cpp
    ${INTERACTORS}
    ${HELPERS}
    ${PARSERS}
)
target_link_libraries(
    ${PROJECT_NAME}
    Qt5::Core
    ${CPR_LIBRARIES}
)

