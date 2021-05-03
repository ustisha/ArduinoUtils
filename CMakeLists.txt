cmake_minimum_required(VERSION 3.17)
project(ArduinoUtils)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(src)

add_executable(ArduinoUtils
        include/Button.h
        include/Clock.h
        include/Format.h
        include/DebugLog.h
        include/HandlerInterface.h
        include/Motion.h
        include/Relay.h
        include/Switch.h
        include/Task.h
        src/Button.cpp
        src/Clock.cpp
        src/Format.cpp
        src/HandlerInterface.cpp
        src/Motion.cpp
        src/Relay.cpp
        src/Switch.cpp
        src/Task.cpp)
