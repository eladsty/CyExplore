#!/bin/bash

gcc -fPIC -c src/mypam.c

sudo ld -x --shared -o /usr/lib/security/mypam.so mypam.o

rm mypam.o
