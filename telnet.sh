#!/bin/bash

echo Waiting for QEMU serial console...
while true; do telnet 127.0.0.1 1235 2>/dev/null; sleep 0.5; done

# Copy from Github