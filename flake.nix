{
  description = "C++ project";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/25.11";

  outputs =
    {
      self,
      nixpkgs,
    }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
      cross = pkgs.pkgsCross.mingwW64;
    in
    {
      packages.${system}.default = pkgs.stdenv.mkDerivation {
        pname = "fib";
        version = "1.0";
        src = pkgs.lib.cleanSource ./.;

        nativeBuildInputs = with pkgs; [
          cmake
        ];
        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Release"

          "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
        ];
      };

      windows = cross.stdenv.mkDerivation {
        pname = "fib";
        version = "1.0";
        src = pkgs.lib.cleanSource ./.;

        nativeBuildInputs = [
          cross.buildPackages.cmake
        ];

        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Release"
          "-DCMAKE_SYSTEM_NAME=Windows"
          "-DCMAKE_EXE_LINKER_FLAGS=-static"
        ];
      };

      devShells.${system}.default = pkgs.mkShell {
        shellHook = ''
          if [ ! -f compile_commands.json ]; then
            echo "Configuring CMake for development..."
            cmake -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
            ln -sf build/compile_commands.json .
          fi
        '';

        buildInputs = with pkgs; [
          cmake
          gcc
        ];
      };
    };
}
