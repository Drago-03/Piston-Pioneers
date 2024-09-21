@echo off
"C:\\Users\\mante\\AppData\\Local\\Android\\Sdk\\cmake\\3.22.1\\bin\\cmake.exe" ^
  "-HC:\\Users\\mante\\OneDrive\\Desktop\\Workspace\\ArduinoControllerApp\\AndroidStudioProjects\\app\\src\\main\\cpp" ^
  "-DCMAKE_SYSTEM_NAME=Android" ^
  "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON" ^
  "-DCMAKE_SYSTEM_VERSION=29" ^
  "-DANDROID_PLATFORM=android-29" ^
  "-DANDROID_ABI=x86" ^
  "-DCMAKE_ANDROID_ARCH_ABI=x86" ^
  "-DANDROID_NDK=C:\\Users\\mante\\AppData\\Local\\Android\\Sdk\\ndk\\26.1.10909125" ^
  "-DCMAKE_ANDROID_NDK=C:\\Users\\mante\\AppData\\Local\\Android\\Sdk\\ndk\\26.1.10909125" ^
  "-DCMAKE_TOOLCHAIN_FILE=C:\\Users\\mante\\AppData\\Local\\Android\\Sdk\\ndk\\26.1.10909125\\build\\cmake\\android.toolchain.cmake" ^
  "-DCMAKE_MAKE_PROGRAM=C:\\Users\\mante\\AppData\\Local\\Android\\Sdk\\cmake\\3.22.1\\bin\\ninja.exe" ^
  "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=C:\\Users\\mante\\OneDrive\\Desktop\\Workspace\\ArduinoControllerApp\\AndroidStudioProjects\\app\\build\\intermediates\\cxx\\Debug\\1r1g731w\\obj\\x86" ^
  "-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=C:\\Users\\mante\\OneDrive\\Desktop\\Workspace\\ArduinoControllerApp\\AndroidStudioProjects\\app\\build\\intermediates\\cxx\\Debug\\1r1g731w\\obj\\x86" ^
  "-DCMAKE_BUILD_TYPE=Debug" ^
  "-BC:\\Users\\mante\\OneDrive\\Desktop\\Workspace\\ArduinoControllerApp\\AndroidStudioProjects\\app\\.cxx\\Debug\\1r1g731w\\x86" ^
  -GNinja
