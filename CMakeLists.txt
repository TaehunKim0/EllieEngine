# CMakeList.txt : 최상위 CMake 프로젝트 파일, 전역 구성을 수행하고
# 여기에 하위 프로젝트를 포함합니다.
#

#################################################
## EllieEngine 최상위 Cmake Setting
#################################################

cmake_minimum_required (VERSION 3.8)

# 프로젝트 이름 설정
set(MAIN_PROJECT_NAME EllieEngine)
project (${MAIN_PROJECT_NAME})

# 윈도우 옵션 설정
option(TARGET_WINDOWS "Windows Option" ON)
if(TARGET_WINDOWS)
	set(PLATFORM_DEFINITION PLATFORM_WINDOWS)
endif()

################################################
# Sub Project 하위 프로젝트를 포함합니다.
################################################

add_subdirectory ("Source/Ellie-Runtime")
add_subdirectory ("Source/Ellie-Player")

