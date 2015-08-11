# Anagiwahst
A simple graphical Qt property creator/editor.


### Precompiled packages

Precompiled packages are available in the openSUSE Build Service: https://software.opensuse.org/package/anagiwahst

### How to compile
#### Install dependencies

Install cmake, gcc, g++, git, Qt5Core, Qt5Gui, Qt5Qml, Qt5Quick and Qt5Widgets. For translations install lrelease.

On openSUSE:

    sudo zypper install gcc gcc-c++ cmake git libQt5Gui-devel libqt5-qtdeclarative-devel libqt5-qtquickcontrols libqt5-linguist
    
    
On Fedora:

    yum install qt5-qtbase qt5-qtbase-devel qt5-qtdeclarative qt5-qtdeclarative-devel qt5-qtdeclarative-static qt5-qtquickcontrols


On Ubuntu:

    sudo apt-get install g++ gcc git qtbase5-dev libqt5qml5 libqt5qml-quickcontrols qtdeclarative5-dev libqt5quick5
    

#### Get source code from git repository

    git clone https://github.com/Buschtrommel/Anagiwahst.git
    

#### Start building

    cd Anagiwahst
    mkdir build && cd build
    cmake -DCMAKE_INSTALL_PREFIX=/usr/local
    make
    sudo make install

    
### License

Copyright (c) 2015 Buschtrommel <kontakt@buschmann23.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
