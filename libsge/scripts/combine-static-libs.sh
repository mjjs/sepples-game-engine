#!/bin/sh

llvm-ar-11 -M <<EOF
    CREATE build/libsge.a
    ADDLIB build/libsge.a
    ADDLIB ../vendor/spdlog/build/libspdlog.a
    ADDLIB ../vendor/glad/libglad.a
    ADDLIB ../vendor/sdl/build/libSDL2.a
    ADDLIB ../vendor/assimp/build/lib/libassimp.a
    SAVE
    END
EOF
