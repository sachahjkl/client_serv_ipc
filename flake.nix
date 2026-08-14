{
  description = "Reproducible build and checks for client_serv_ipc";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    { nixpkgs, self }:
    let
      systems = [
        "x86_64-linux"
        "aarch64-linux"
      ];
      forAllSystems = nixpkgs.lib.genAttrs systems;
    in
    {
      packages = forAllSystems (
        system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in
        {
          default = pkgs.stdenv.mkDerivation {
            pname = "client-serv-ipc";
            version = "1.0.0";
            src = self;
            nativeBuildInputs = [ pkgs.gnumake ];
            dontConfigure = true;
            buildPhase = ''
              runHook preBuild
              make -j "$NIX_BUILD_CORES" \
                CC="${pkgs.stdenv.cc.targetPrefix}cc" \
                CFLAGS="-std=c11 -O2 -Wall -Wextra -Wpedantic -Werror -Wno-error=unused-result -Wformat=2 -Wno-unused-parameter -Wshadow -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -ffile-prefix-map=$PWD=."
              runHook postBuild
            '';
            installPhase = ''
              runHook preInstall
              install -Dm755 bin/client "$out/bin/client"
              install -Dm755 bin/serveur "$out/bin/serveur"
              runHook postInstall
            '';
          };
        }
      );

      checks = forAllSystems (
        system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
          package = self.packages.${system}.default;
        in
        {
          actionlint = pkgs.runCommand "actionlint" { nativeBuildInputs = [ pkgs.actionlint ]; } ''
            actionlint -config-file ${self}/.github/actionlint.yaml ${self}/.github/workflows/ci.yml
            touch "$out"
          '';

          inherit package;

          ipc = pkgs.runCommand "client-serv-ipc-test" { nativeBuildInputs = [ pkgs.coreutils ]; } ''
            set -eu
            cd "$TMPDIR"
            ${package}/bin/serveur >server.log 2>&1 &
            server_pid=$!
            cleanup() {
              kill "$server_pid" 2>/dev/null || true
              wait "$server_pid" 2>/dev/null || true
            }
            trap cleanup EXIT
            sleep 1

            ${package}/bin/client services >services.log
            grep -F "calcul-simple" services.log
            ${package}/bin/client calcul-simple + 2 3 >calculation.log
            grep -Fx "5" calculation.log

            mkdir "$out"
            cp services.log calculation.log server.log "$out/"
          '';
        }
      );

      formatter = forAllSystems (
        system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in
        pkgs.writeShellApplication {
          name = "nix-fmt";
          runtimeInputs = [ pkgs.nixfmt ];
          text = "nixfmt flake.nix";
        }
      );
    };
}
