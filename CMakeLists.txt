cmake_minimum_required(VERSION 3.5)

project(
    paper
    VERSION 2.0.0
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX /usr)

include(FeatureSummary)

add_definitions(-DORGANISATION_NAME="Paper")
add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")
add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")
add_definitions(-DPROJECT_DESCRIPTION="\\nPaper - A Random Wallpaper Application\\nA CLI Tool to set a random wallpaper from Unsplash.com")
add_subdirectory(src)

install(FILES "paper.desktop" DESTINATION share/applications)
install(FILES "paper.svg" DESTINATION share/icons)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
