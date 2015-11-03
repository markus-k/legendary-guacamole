#!/bin/bash

screen qemu-system-i386 -curses -kernel build/kernel $@
