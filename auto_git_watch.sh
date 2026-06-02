#!/bin/bash

MSG="auto update"

while inotifywait -r -e modify,create,delete .; do
    git add .

    git commit -m "$MSG $(date +%H:%M:%S)" 2>/dev/null

    git push 2>/dev/null

    echo "synced ✔"
done
