# God of War: Tobiichi Launcher (Qt 6 Quick). Lanza ps2EntryRunner con la configuración elegida.
# Compilar: cmake -S launcher -B launcher/build -G Ninja -DCMAKE_BUILD_TYPE=Release && ninja -C launcher/build
cmake_minimum_required(VERSION 3.21)
project(TobiichiLauncher VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)
qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(tobiichi-launcher WIN32
    src/main.cpp
    src/lanzador.cpp
    src/lanzador.h
)

set(ARCHIVOS_QML
    qml/Main.qml
    qml/Tema.qml
    qml/Textos.js
    qml/Ascuas.qml
    qml/Meandro.qml
    qml/Pestana.qml
    qml/Fila.qml
    qml/Selector.qml
    qml/Interruptor.qml
    qml/Deslizador.qml
    qml/BotonJugar.qml
    qml/BotonSecundario.qml
    qml/CampoRuta.qml
    qml/Tecla.qml
    qml/PaginaGrafico.qml
    qml/PaginaRendimiento.qml
    qml/PaginaArchivos.qml
    qml/PaginaControles.qml
    qml/PaginaOtros.qml
)
# Los QML van en la raíz del módulo (sin "qml/"): así el import implícito de su carpeta es el propio módulo y
# Tema se carga como singleton.
foreach(archivo IN LISTS ARCHIVOS_QML)
    get_filename_component(nombre "${archivo}" NAME)
    set_source_files_properties(${archivo} PROPERTIES QT_RESOURCE_ALIAS ${nombre})
endforeach()
set_source_files_properties(qml/Tema.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(tobiichi-launcher
    URI Tobiichi
    VERSION 1.0
    RESOURCE_PREFIX /qt/qml
    QML_FILES ${ARCHIVOS_QML}
    RESOURCES
        recursos/fuentes/Cinzel.ttf
)

target_compile_definitions(tobiichi-launcher PRIVATE TOBIICHI_VERSION="${PROJECT_VERSION}")
target_link_libraries(tobiichi-launcher PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2)

install(TARGETS tobiichi-launcher RUNTIME DESTINATION bin)
