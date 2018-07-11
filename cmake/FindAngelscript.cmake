#
#
#


find_path(Angelscript_INCLUDE_DIR angelscript.h)

if(WIN32 AND "${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
  set(Angelscript_NAMES ${Angelscript_NAMES} angelscript64)
else()
  set(Angelscript_NAMES ${Angelscript_NAMES} angelscript)
endif()

find_path(FONTCONFIG_INCLUDE_DIR
  NAMES angelscript.h
  PATHS
  /usr/include
)
find_library(Angelscript_LIBRARY_DEBUG
  NAMES ${Angelscript_NAMES}d
)
find_library(Angelscript_LIBRARY_RELEASE
  NAMES ${Angelscript_NAMES}
)

if (Angelscript_LIBRARY_DEBUG OR Angelscript_LIBRARY_RELEASE)
  set(Angelscript_FOUND TRUE)
  set(Angelscript_LIBRARIES DEBUG ${Angelscript_LIBRARY_DEBUG} OPTIMIZED ${Angelscript_LIBRARY_RELEASE})
else()
  set(Angelscript_FOUND FALSE)
  set(Angelscript_LIBRARIES "")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Angelscript
  REQUIRED_VARS Angelscript_LIBRARIES Angelscript_INCLUDE_DIR
)

mark_as_advanced(Angelscript_FOUND Angelscript_INCLUDE_DIR Angelscript_LIBRARIES Angelscript_LIBRARY_DEBUG Angelscript_LIBRARY_RELEASE)

if(Angelscript_FOUND AND NOT TARGET Angelscript::Angelscript)
  add_library(Angelscript::Angelscript IMPORTED MODULE)
  set_target_properties(Angelscript::Angelscript PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${Angelscript_INCLUDE_DIR}"
  )
  target_link_libraries(Angelscript::Angelscript
    INTERFACE ${Angelscript_LIBRARIES}
  )
endif()
