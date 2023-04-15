{
    description = "Sepples Game Engine development environment";

    inputs = {
        nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
        flake-utils.url = "github:numtide/flake-utils";
    };

    outputs = { self, nixpkgs, flake-utils }:
        flake-utils.lib.eachDefaultSystem (system:
            let
                pkgs = import nixpkgs { inherit system; };
            in {
                devShells.default = pkgs.mkShell {
                    LD_LIBRARY_PATH = with pkgs; with xorg; lib.strings.concatStrings [
                        "${libX11}/lib:"
                        "${libXext}/lib:"
                        "${libXinerama}/lib:"
                        "${libXi}/lib:"
                        "${libXrandr}/lib:"
                        "${libglvnd}/lib"
                    ];

                    buildInputs = with pkgs; [
                        stdenv
                        pkgconfig
                        libglvnd
                        xorg.libX11
                        xorg.libXext
                        xorg.libXinerama
                        xorg.libXi
                        xorg.libXrandr
                    ];

                    packages = with pkgs; [
                        llvmPackages_9.llvm-polly
                        llvmPackages_15.clang
                        gnumake
                        cmake
                        gdb
                        bear
                    ];

                    shellHook = ''
                        export PS1="(SGE) $PS1"
                    '';
                };
            }
        );
}
