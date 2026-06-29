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
    in
    {
      packages.${system}.default = pkgs.stdenv.mkDerivation {
        pname = "fibpass";
        version = "1.0";
        src = pkgs.lib.cleanSourceWith {
          filter =
            name: type:
            let
              base = baseNameOf name;
            in
            base != "build" && base != ".build";
          src = ./.;
        };

        nativeBuildInputs = with pkgs; [
          cmake
        ];
        buildInputs = [
          pkgs.libxcrypt
        ];
        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Release"

          "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
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
          libxcrypt
        ];
      };
    };
}
