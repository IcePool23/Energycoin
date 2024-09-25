
Debian
====================
This directory contains files used to package nrgcd/nrgc-qt
for Debian-based Linux systems. If you compile nrgcd/nrgc-qt yourself, there are some useful files here.

## nrgc: URI support ##


nrgc-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install nrgc-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your nrgc-qt binary to `/usr/bin`
and the `../../share/pixmaps/nrgc128.png` to `/usr/share/pixmaps`

nrgc-qt.protocol (KDE)

