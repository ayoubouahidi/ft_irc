#!/bin/bash

# check if repo
if [ ! -d .git ]; then
  echo "Not a git repository"
  exit 1
fi

# add all changes
git add .

# commit message (parameter or default)
msg="$1"
if [ -z "$msg" ]; then
  msg="auto commit"
fi

git commit -m "$msg"

# push
git push

echo "Done ✔"
