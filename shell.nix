{ pkgs ? import <nixpkgs> { } }:

let
  shellDrv =
    { raylib
    , libxkbcommon
    , cmake
    , ...
    }:
    pkgs.mkShell {
      nativeBuildInputs = [ raylib libxkbcommon cmake ];

      shellHook = ''
        echo "Entering the raylib development environment!"

        # Start user's shell
        "$(getent passwd $USER | cut -d : -f 7)"

        echo "Exiting the raylib development environment!"
        exit 0
      '';
    };
in
shellDrv pkgs
