#!/bin/bash

./metamorpho < "$1" > "${1%.*}.masm"
morpho -c "${1%.*}.masm"
