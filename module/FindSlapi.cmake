#
# Find the Slapi includes and library
#
# This module defines
# SLAPI_INCLUDE_DIR, where to find slapi.h, etc.
# SLAPI_LIBRARIES, the libraries to link against to use SLAPI.
# SLAPI_FOUND, If false, do not try to use SLAPI.

# also defined, but not for general use are
# SLAPI_LIBRARY, where to find the SLAPI library.
# SLAPI_DEBUG_LIBRARY, where to find the SLAPI library in debug
# mode.
#

SET(SLAPI_INCLUDE_DIR ${CMAKE_MODULE_PATH}/slapi/headers/)
SET( SLAPI_LIBRARY ${CMAKE_MODULE_PATH}/slapi/binaries/slapi.dll)

# TODO choose the librairy based on the compiler version MAC_OS, WIN32, WIN64

# # With Win32, important to have both
# IF(WIN32)
#   #TODO support of x64
#   #FIND_LIBRARY(SLAPI_LIBRARY SLAPI
#   #             ${SLAPI_INCLUDE_DIR}/../binaries/
#   #             )
#   SET( SLAPI_LIBRARY ${CMAKE_MODULE_PATH}/slapi/binaries/slapi.dll)
# ELSE(WIN32)
#   # As the librairy can be used only on Windows throw fatal error
#   MESSAGE( "Slapi can only be used on Windows..." )
# ENDIF(WIN32)

IF(SLAPI_INCLUDE_DIR)
  IF(SLAPI_LIBRARY)
    SET(SLAPI_FOUND "YES")
    SET(SLAPI_LIBRARIES ${SLAPI_LIBRARY} ) #${CMAKE_DL_LIBS})
    SET(SLAPI_DEBUG_LIBRARIES ${SLAPI_DEBUG_LIBRARY} ) #${CMAKE_DL_LIBS})
  ENDIF(SLAPI_LIBRARY)
ENDIF(SLAPI_INCLUDE_DIR)
