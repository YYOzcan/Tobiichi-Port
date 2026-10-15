include(CheckIPOSupported)

check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT IPO_ERROR)

# GOW-Port: GCC/Clang enlazan con LTO en tantos procesos como núcleos (-flto=auto), y con ~6.400 archivos cada proceso
# usa 1-2 GB: en un equipo de 8-16 GB se quedaba sin memoria. PS2X_LTO_JOBS=N lo limita (los instaladores lo eligen
# según la memoria); vacío = el comportamiento de CMake.
set(PS2X_LTO_JOBS "" CACHE STRING "GCC/Clang: procesos del enlace con LTO (vacío = todos los núcleos)")

function(EnableFastReleaseMode TargetName)
    message("> Enabling optimization for: ${TargetName}")
    if(MSVC)
        target_compile_options(${TargetName} PRIVATE
            $<$<CONFIG:Release>:
                /O2 # speed
                /Ob2 # inline aggressively
                /Oi # intrinsics
                /GL # whole program opt
                /Gy # function-level linking
                /Gw # global data in COMDAT
                /GF # string pooling
                /Zc:inline # remove unreferenced inline
                /fp:fast # fast math (graphics friendly)
                /DNDEBUG
                /arch:AVX2 # Advanced Vector Extensions 2
                /GS- # Disable Buffer Security Check (faster)
                /Qspectre- # Disable Spectre mitigations (faster)
            >
        )

        if(TARGET ${TargetName})
            target_link_options(${TargetName} PRIVATE
                $<$<CONFIG:Release>:
                    /LTCG # link-time code generation
                    /OPT:REF # remove unreferenced
                    /OPT:ICF # fold identical COMDATs
                >
            )
        endif()
    endif()

    if(IPO_SUPPORTED)
        set_property(TARGET ${TargetName} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
        if(NOT MSVC AND PS2X_LTO_JOBS)
            target_link_options(${TargetName} PRIVATE $<$<CONFIG:Release>:-flto=${PS2X_LTO_JOBS}>)
        endif()
    else()
        message(WARNING "Interprocedural optimization not supported: ${ipo_error}")
    endif()
endfunction()