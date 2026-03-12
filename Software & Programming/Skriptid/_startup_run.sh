#!/bin/bash

SCRIPTS_TO_RUN=(
    "$HOME/Desktop/skriptid/git_pull_all.sh"
    "$HOME/Desktop/skriptid/update_all.sh"
)
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo "--------------------------------------"
echo -e "${YELLOW}Auto-Sequence Initiated${NC}"
echo "--------------------------------------"

for i in {15..1}; do
    echo -ne "Starting in: ${YELLOW}$i${NC} seconds...   \r"
    sleep 1
done

echo -e "${GREEN}STARTING NOW!${NC}                   "
echo ""

for script in "${SCRIPTS_TO_RUN[@]}"; do
    
    echo "--------------------------------------"
    if [ -f "$script" ]; then
        echo -e "Running: ${YELLOW}$script${NC}"
        chmod +x "$script"
        "$script"
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}Done.${NC}"
        else
            echo -e "${RED}Script finished with errors.${NC}"
        fi
    else
        echo -e "${RED}Error: File not found ($script)${NC}"
    fi
done

echo "--------------------------------------"
echo "All tasks finished."