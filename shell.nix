{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.pkg-config
    pkgs.raylib
  ];

  shellHook = ''
    export SHELL=$(which zsh)
    exec zsh
  '';
}

