#!/bin/bash

gcc -o pam_test src/test.c -lpam -lpam_misc
#if it doesnt work