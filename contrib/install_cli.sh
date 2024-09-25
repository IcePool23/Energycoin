 #!/usr/bin/env bash

 # Execute this file to install the nrgc cli tools into your path on OS X

 CURRENT_LOC="$( cd "$(dirname "$0")" ; pwd -P )"
 LOCATION=${CURRENT_LOC%Nrgc-Qt.app*}

 # Ensure that the directory to symlink to exists
 sudo mkdir -p /usr/local/bin

 # Create symlinks to the cli tools
 sudo ln -s ${LOCATION}/Nrgc-Qt.app/Contents/MacOS/nrgcd /usr/local/bin/nrgcd
 sudo ln -s ${LOCATION}/Nrgc-Qt.app/Contents/MacOS/nrgc-cli /usr/local/bin/nrgc-cli
