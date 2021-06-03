
Требуется: [conan](https://conan.io/downloads.html), [cmake](https://cmake.org/download/), [MSVC 15+](https://visualstudio.microsoft.com/ru/downloads/)

## Установка для Windows 
[об установке conan + sfml](https://leinnan.github.io/blog/conan-adventuressfml-and-entt-in-c.html)

сконфигурировать conan: \
`conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan` \
`conan profile new default --detect` \
`conan profile update settings.cppstd=17 default` 

В папке проекта: 

запустить установщик пакетов conan \
`conan install . -if build` 

запустить cmake \
`cmake -G "Visual Studio 16 2019" -B build -S .` \
`cmake --build build --config Release` \
`start ./build/bin/tennis.exe`

