#!/bin/bash

SERVER_PATH="./files/serwer-bez-tla-Qt6-cmake/build/serwer_graficzny"
SERVER_NAME="serwer_graficzny"
INTERP_PATH="./interp_etap2"

if pgrep -x "$SERVER_NAME" > /dev/null; then
    echo "Serwer graficzny juz dziala (PID: $(pgrep -x "$SERVER_NAME"))"
else
    echo "Uruchamianie serwera graficznego..."
    if [ -f "$SERVER_PATH" ]; then
        $SERVER_PATH &
        sleep 2
        echo "Serwer uruchomiony (PID: $!)"
    else
        echo "BLAD: Nie znaleziono serwera w $SERVER_PATH"
        exit 1
    fi
fi

if [ ! -f "$INTERP_PATH" ]; then
    echo "BLAD: Nie znaleziono $INTERP_PATH"
    echo "Uruchom najpierw: make etap2 DEBUG=1"
    exit 1
fi

echo ""
echo "Uruchamianie interpretera..."
export LD_LIBRARY_PATH="./libs"
$INTERP_PATH
