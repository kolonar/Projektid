#!/bin/bash

# Värvide definitsioonid
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Määra otsitav kaust
SEARCH_DIR="$HOME/Desktop/git"

echo "------------------------------------------------------"
echo "Searching for Git repositories in: $SEARCH_DIR"
echo "------------------------------------------------------"

# Otsi kõiki .git kaustu ja käi need läbi
find "$SEARCH_DIR" -name ".git" -type d -prune | while read gitdir; do

    # Leia projekti teekond
    repo_dir=$(dirname "$gitdir")
    
    echo ""
    echo "Checking: $repo_dir"

    # Sisene kausta või jätka järgmisega
    cd "$repo_dir" || continue

    # Kontrolli kinnitamata muudatusi
    if [[ -n $(git status --porcelain) ]]; then
        # Jäta vahele, kui failid on muudetud (FAIL -> RED)
        echo -e "${RED}SKIPPED: You have uncommitted changes.${NC}"
    else
        echo "Pulling latest changes..."
        
        # Tõmba uuendused (timeout 15s)
        timeout 15s git pull origin $(git rev-parse --abbrev-ref HEAD)
        
        # Kontrolli kas käsk õnnestus
        if [ $? -eq 0 ]; then
            # Õnnestus (PASS -> GREEN)
            echo -e "${GREEN}Success.${NC}"
        else
            # Ebaõnnestus (FAIL -> RED)
            echo -e "${RED}Error: Pull failed (Merge conflict, network issue, or no upstream).${NC}"
        fi
    fi

    # Mine tagasi eelmisesse kausta
    cd - > /dev/null
done

echo ""
echo "------------------------------------------------------"
echo "Operation Complete"
echo "------------------------------------------------------"