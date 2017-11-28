cmake_minimum_required (VERSION 2.6)
project (HelloWorld)

set(OXYGINE_ROOT /Users/oesse/projects/oxygine/oxygine-framework/oxygine)
set(OXYGINE_SRC ${OXYGINE_ROOT}/src)
set(THIRD_PARTY ${OXYGINE_ROOT}/third_party/${PLATFORM})
set(OXYGINE_INCLUDE_DIRS ${OXYGINE_SRC})

set(OXYGINE_LIBRARY_DIRS
	${OXYGINE_LIBRARY_DIRS}
	${OXYGINE_SOURCE_DIR}/libs
	${THIRD_PARTY}/libraries)

set(OXYGINE_DEFINITIONS
	${OX_DEFINITIONS})

set(OX_HAVE_LIBPNG 1)
set(OX_HAVE_HTTP 1)
set(OX_USE_SDL2 1)

file(GLOB OXYGINE_JS_LIBRARIES ${OXYGINE_SRC}/core/emscripten/*.js)

set(OXYGINE_CXX_FLAGS "${OXYGINE_CXX_FLAGS} -s USE_SDL=2 -s USE_LIBPNG=1 -s USE_ZLIB=1 -s FULL_ES2=1 ")	
set(OXYGINE_CXX_FLAGS "${OXYGINE_CXX_FLAGS} -std=c++11 ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_ZLIB=1")#for minizip.c

set(OX_DEFINITIONS ${OX_DEFINITIONS} -DOX_NO_MT)

set(PLATFORM emscripten)

add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")


set(CORE_LIBS
	${CORE_LIBS}
	oxygine-framework	
	${OPENGL_LIBRARIES}		
)
set(CORE_LIBS ${CORE_LIBS} ${LIBPNG})
set(OXYGINE_CORE_LIBS ${CORE_LIBS})

set(LIBPNG ${libprefix}png)

add_executable(HelloWorld ./src/example.cpp ./src/main.cpp  ./src/example.h)
target_link_libraries(HelloWorld ${OXYGINE_CORE_LIBS} /Users/oesse/liboxygine-framework.a)

SET(CMAKE_EXECUTABLE_SUFFIX ".html")	
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 --memory-init-file 0 -s TOTAL_MEMORY=50331648")
em_link_pre_js(HelloWorld  ${OXYGINE_JS_LIBRARIES}  ${CMAKE_CURRENT_SOURCE_DIR}/build/data.js)
