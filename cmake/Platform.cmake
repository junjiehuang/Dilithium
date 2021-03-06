IF(WIN32)
	IF(MSVC)
		IF(CMAKE_GENERATOR MATCHES "Win64")
			SET(DILITHIUM_ARCH_NAME "x64")
			SET(DILITHIUM_VS_PLATFORM_NAME "x64")
		ELSEIF(CMAKE_GENERATOR MATCHES "ARM64")
			SET(DILITHIUM_ARCH_NAME "arm64")
			SET(DILITHIUM_VS_PLATFORM_NAME "ARM64")
		ELSEIF(CMAKE_GENERATOR MATCHES "ARM")
			SET(DILITHIUM_ARCH_NAME "arm")
			SET(DILITHIUM_VS_PLATFORM_NAME "ARM")
		ELSE()
			SET(DILITHIUM_ARCH_NAME "x86")
			SET(DILITHIUM_VS_PLATFORM_NAME "Win32")
		ENDIF()
	ENDIF()
	IF(WINDOWS_STORE)
		SET(DILITHIUM_PLATFORM_NAME "win_store")
		SET(DILITHIUM_PLATFORM_WINDOWS_STORE TRUE)
	ELSE()
		SET(DILITHIUM_PLATFORM_NAME "win")
		SET(DILITHIUM_PLATFORM_WINDOWS_DESKTOP TRUE)
	ENDIF()
	SET(DILITHIUM_PLATFORM_WINDOWS TRUE)
ELSEIF(ANDROID)
	SET(DILITHIUM_PLATFORM_NAME "android")
	SET(DILITHIUM_PLATFORM_ANDROID TRUE)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	SET(DILITHIUM_PLATFORM_NAME "linux")
	SET(DILITHIUM_PLATFORM_LINUX TRUE)
ELSEIF(IOS)
	SET(DILITHIUM_PLATFORM_NAME "ios")
	SET(DILITHIUM_PLATFORM_IOS TRUE)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	IF(IOS)
		SET(DILITHIUM_PLATFORM_NAME "ios")
		SET(DILITHIUM_PLATFORM_IOS TRUE)
	ELSE()
		SET(DILITHIUM_PLATFORM_NAME "darwin")
		SET(DILITHIUM_PLATFORM_DARWIN TRUE)
	ENDIF()
ENDIF()

IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
	SET(DILITHIUM_HOST_PLATFORM_NAME "win")
	SET(DILITHIUM_HOST_PLATFORM_WINDOWS TRUE)
ELSEIF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
	SET(DILITHIUM_HOST_PLATFORM_NAME "linux")
	SET(DILITHIUM_HOST_PLATFORM_LINUX TRUE)
ELSEIF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
	SET(DILITHIUM_HOST_PLATFORM_NAME "darwin")
	SET(DILITHIUM_HOST_PLATFORM_DARWIN TRUE)
ENDIF()

IF(NOT DILITHIUM_ARCH_NAME)
	IF((CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64") OR (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64"))
		SET(DILITHIUM_ARCH_NAME "x64")
	ELSE()
		SET(DILITHIUM_ARCH_NAME "x86")
	ENDIF()
ENDIF()

IF((CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "AMD64") OR (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64"))
	SET(DILITHIUM_HOST_ARCH_NAME "x64")
ELSE()
	SET(DILITHIUM_HOST_ARCH_NAME "x86")
ENDIF()

SET(DILITHIUM_PLATFORM_NAME ${DILITHIUM_PLATFORM_NAME}_${DILITHIUM_ARCH_NAME})
SET(DILITHIUM_HOST_PLATFORM_NAME ${DILITHIUM_HOST_PLATFORM_NAME}_${DILITHIUM_HOST_ARCH_NAME})

IF(DILITHIUM_PLATFORM_ANDROID OR DILITHIUM_PLATFORM_IOS)
	SET(DILITHIUM_PREFERRED_LIB_TYPE "STATIC")
ELSE()
	SET(DILITHIUM_PREFERRED_LIB_TYPE "SHARED")
ENDIF()

IF (DILITHIUM_PLATFORM_WINDOWS_DESKTOP OR DILITHIUM_PLATFORM_LINUX OR DILITHIUM_PLATFORM_DARWIN)
	SET(DILITHIUM_IS_DEV_PLATFORM TRUE)
ELSE()
	SET(DILITHIUM_IS_DEV_PLATFORM FALSE)
ENDIF()
