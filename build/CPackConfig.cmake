# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "C:/Users/markus/Desktop/Archic/BookManager;C:/Users/markus/Desktop/Archic/BookManager/build")
set(CPACK_CMAKE_GENERATOR "MinGW Makefiles")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
set(CPACK_DEBIAN_PACKAGE_DEBUG "OFF")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libasio-dev")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "CrowCpp")
set(CPACK_DEBIAN_PACKAGE_SECTION "libdevel")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "C:/Program Files/CMake/share/cmake-3.30/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "BookManager built using CMake")
set(CPACK_GENERATOR "ZIP")
set(CPACK_INNOSETUP_ARCHITECTURE "x64")
set(CPACK_INSTALL_CMAKE_PROJECTS "C:/Users/markus/Desktop/Archic/BookManager/build;BookManager;ALL;/")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/BookManager")
set(CPACK_MODULE_PATH "C:/Users/markus/Desktop/Archic/BookManager/libs/Crow/cmake")
set(CPACK_NSIS_DISPLAY_NAME "Crow 1.1.1")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "Crow 1.1.1")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "C:/msys64/ucrt64/bin/objcopy.exe")
set(CPACK_OBJDUMP_EXECUTABLE "C:/msys64/ucrt64/bin/objdump.exe")
set(CPACK_OUTPUT_CONFIG_FILE "C:/Users/markus/Desktop/Archic/BookManager/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION "A Fast and Easy to use C++ microframework for the web.")
set(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Program Files/CMake/share/cmake-3.30/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "BookManager built using CMake")
set(CPACK_PACKAGE_FILE_NAME "Crow-1.1.1-win64")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://crowcpp.org")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Crow 1.1.1")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Crow 1.1.1")
set(CPACK_PACKAGE_NAME "Crow")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "CrowCpp")
set(CPACK_PACKAGE_VERSION "1.1.1")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_READELF_EXECUTABLE "C:/msys64/ucrt64/bin/readelf.exe")
set(CPACK_RESOURCE_FILE_LICENSE "C:/Program Files/CMake/share/cmake-3.30/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "C:/Program Files/CMake/share/cmake-3.30/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "C:/Program Files/CMake/share/cmake-3.30/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/Users/markus/Desktop/Archic/BookManager/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "win64")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/Users/markus/Desktop/Archic/BookManager/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
