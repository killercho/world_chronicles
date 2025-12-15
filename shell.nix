{ pkgs ? import <nixpkgs> { } }:

let
  shellDrv =
    { raylib
    , libxkbcommon
    , cmake
    , libclang
    , gdb
    , gnumake
    , tree
    , ...
    }:
    pkgs.mkShell {
      nativeBuildInputs = [ raylib libxkbcommon cmake libclang gdb gnumake tree ];
      buildInputs = [ ];
      env.NIX_ENFORCE_PURITY = 0;

      shellHook = ''
        echo
        echo "Entering the raylib development environment!"
        echo

        echo "Creating the correct raylib clangd compile file under the '.clangd' name..."
        RAYLIB_NIX_PACKAGE_PATH=$(nix-instantiate --eval-only --expr '(import <nixpkgs> {}).raylib.outPath')
        echo "
        CompileFlags:
          Add: -I$RAYLIB_NIX_PACKAGE_PATH/include" > .clangd

        # Remove the build folder when entering the env
        # only if that option is specificaly given as an answer
        read -t 2 -p "Delete the build folder? [y/N] " NUKE
        NUKE="''${NUKE,,}"
        if [ "$NUKE" == 'y' -o "$NUKE" == 'yes' ]; then
            echo "Removing the build folder..."
            rm -rf "build"
        elif [ -z "$NUKE" ]; then
            echo n
        elif ! [ "$NUKE" == 'n' -o "$NUKE" == 'no' ]; then
            echo "Unknown responce '$NUKE', not removing the build!"
        fi

        # Create the build folder that will be used to build the project
        # Only if that folder was not already created
        if [[ ! -e "build/" ]]; then
          echo "Creating the build folder..."
          mkdir build
        fi

        # Run the cmake inside of the build folder to generate the cmake files
        # and go back to the root folder
        cd build && cmake .. -DENABLE_TESTS=On -DCMAKE_BUILD_TYPE=Debug && cd ..

        # Start user's shell
        # The start of the new user shell needs to happen after
        # all of the commands were executed
        "$(getent passwd $USER | cut -d : -f 7)"

        echo
        echo "Exiting the raylib development environment!"
        echo
        exit 0
      '';
    };
in
shellDrv pkgs
