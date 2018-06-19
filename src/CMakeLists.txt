find_package(
    Qt5

    COMPONENTS
        Core
        Network

    REQUIRED
)

set(
    INTERACTORS

    interactors/Interactor.h
    interactors/Interactor.cpp

    interactors/FetchWallpaperInteractor.h
    interactors/FetchWallpaperInteractor.cpp

    interactors/RunAtIntervalInteractor.h
    interactors/RunAtIntervalInteractor.cpp

    interactors/SetWallpaperInteractor.h
    interactors/SetWallpaperInteractor.cpp
)

set(
    HELPERS

    helpers/ConfigHelper.h
    helpers/ConfigHelper.cpp

    helpers/DownloadHelper.h
    helpers/DownloadHelper.cpp

    helpers/ShellHelper.h
    helpers/ShellHelper.cpp
)

set(
    PARSERS

    parsers/ArgumentParser.h
    parsers/ArgumentParser.cpp
)

set(
    UTILS

    utils/CommonUtils.h
    utils/CommonUtils.cpp
)

add_executable(
    ${PROJECT_NAME}

    main.cpp
    ${INTERACTORS}
    ${HELPERS}
    ${PARSERS}
    ${UTILS}
)
target_link_libraries(
    ${PROJECT_NAME}
    Qt5::Core
    Qt5::Network
)

