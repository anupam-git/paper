cmake_minimum_required(VERSION 3.5)

project(
    paper
    VERSION 2.0.0
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include(FeatureSummary)

### Include CPR
add_subdirectory(lib/cpr)
include_directories(${CPR_INCLUDE_DIRS})
###

add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")
add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")
add_definitions(-DPROJECT_DESCRIPTION="\\nPaper - A Random Wallpaper Application\\nA CLI Tool to set a random wallpaper from Unsplash.com")
add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
