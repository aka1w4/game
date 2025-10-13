{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.pkg-config
    #pkgs.raylib
    pkgs.libGL
    pkgs.xorg.libX11
    #pkgs.leveldb
    #pkgs.leveldb.dev
  ];

  shellHook = ''
    export SHELL=$(which zsh)
    exec zsh
  '';
}

