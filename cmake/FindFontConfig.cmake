# FindFontConfig.cmake
#
# Finds the fontconfig library
#
# This will define the following variables
#
#    FontConfig_FOUND
#    FontConfig_INCLUDE_DIRS
#
# and the following imported targets
#
#     FontConfig::FontConfig

find_package(PkgConfig)
pkg_check_modules(PC_FontConfig QUIET FontConfig)

find_path(FONTCONFIG_INCLUDE_DIR
  NAMES fontconfig.h
  PATHS
  ${PC_FontConfig_INCLUDEDIR}
  ${PC_FontConfig_INCLUDE_DIRS}
  /usr/X11/include
  /usr/X11R6/include
  /usr/include
  PATH_SUFFIXES fontconfig
)
find_library(FONTCONFIG_LIBRARY
  NAMES fontconfig
  PATHS
  ${PC_FontConfig_LIBDIR}
  ${PC_FontConfig_LIBRARY_DIRS}
)

set(FontConfig_VERSION ${PC_FontConfig_VERSION})

mark_as_advanced(FontConfig_FOUND FontConfig_INCLUDE_DIR FontConfig_LIBRARY FontConfig_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FontConfig
  REQUIRED_VARS FontConfig_INCLUDE_DIR FontConfig_LIBRARY
  VERSION_VAR FontConfig_VERSION
)

if(FontConfig_FOUND)
  set(FontConfig_INCLUDE_DIRS ${FontConfig_INCLUDE_DIR})
  set(FontConfig_LIBRARIES ${FontConfig_LIBRARY})
endif()

if(FontConfig_FOUND AND NOT TARGET FontConfig::FontConfig)
  add_library(FontConfig::FontConfig IMPORTED)
  set_target_properties(FontConfig::FontConfig PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${FontConfig_INCLUDE_DIR}"
  )
  target_link_libraries(FontConfig::FontConfig
    INTERFACE ${FontConfig_LIBRARIES}
  )
endif()
