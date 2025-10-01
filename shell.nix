{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.pkg-config
    pkgs.raylib
    pkgs.leveldb
    pkgs.leveldb.dev
    pkgs.boost
  ];

  shellHook = ''
    export SHELL=$(which zsh)
    exec zsh
  '';
}

