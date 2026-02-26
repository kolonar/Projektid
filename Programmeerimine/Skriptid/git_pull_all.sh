#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

SEARCH_DIR="$HOME/Desktop/git"

echo "------------------------------------------------------"
echo "Searching for Git repositories in: $SEARCH_DIR"
echo "------------------------------------------------------"
find "$SEARCH_DIR" -name ".git" -type d -prune | while read gitdir; do
    repo_dir=$(dirname "$gitdir")
    echo ""
    echo "Checking: $repo_dir"
    cd "$repo_dir" || continue
    if [[ -n $(git status --porcelain) ]]; then
        echo -e "${RED}SKIPPED: You have uncommitted changes.${NC}"
    else
        echo "Pulling latest changes..."
        timeout 15s git pull origin $(git rev-parse --abbrev-ref HEAD)
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}Success.${NC}"
        else
            echo -e "${RED}Error: Pull failed (Merge conflict, network issue, or no upstream).${NC}"
        fi
    fi

    cd - > /dev/null
done

echo ""
echo "------------------------------------------------------"
echo "Operation Complete"
echo "------------------------------------------------------"