#!/bin/bash

DEVICE_ID=$(cat device-id)
rm *firmware*
particle compile photon `find . -type f -iname *.ino -or -iname *.h -or -iname *.c* -not -iname *.csv -not -ipath */examples/*`

echo Flashing $DEVICE_ID
particle flash $DEVICE_ID *firmware*.bin
