# User Variables
set (SUPPORT_FUNCTION_CALL_TRACE 1)

# NO DATA FOR SECTION: Custom additions (begin)

# Common Include
include (${CAMX_CDK_PATH}/../linuxembedded/common.cmake)

# Files and Build Type
add_library( com.qti.sensor.ov7251 SHARED
    ../../ov7251_sensor.cpp
)

# Libraries to compile
target_link_libraries (com.qti.sensor.ov7251 dl)

# Include Paths
include_directories (${CAMX_C_INCLUDES})
include_directories (../..)
include_directories (${CAMX_CDK_PATH}/sensor)

# Dependencies


# Definitions
add_definitions (${CAMX_CFLAGS})
add_definitions (${CAMX_CPPFLAGS})
# NO DATA FOR SECTION: Custom additions (end)

# Auto-Gen
#add_dependencies(com.qti.sensor.ov7251 autogen)

install(TARGETS com.qti.sensor.ov7251 LIBRARY DESTINATION lib/camera)

if (CONFIG STREQUAL "Debug")
    add_definitions( -g )
endif()

