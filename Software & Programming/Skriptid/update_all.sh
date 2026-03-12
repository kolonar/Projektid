#!/bin/bash

# --- Värvikoodid ---
BLUE='\e[1;34m'
NC='\e[0m'

# --- Abifunktsioon ---
print_header() {
    echo -e "${BLUE}# $1${NC}"
}

set -e

echo "--- Starting full system update ---"

# 1. Uuenda APT pakettide nimekirju
echo
print_header "### 1/5: Updating APT package lists... ###"
sudo apt update

# 2. Uuenda kõiki paigaldatud APT pakette
echo
print_header "### 2/5: Upgrading APT packages (full-upgrade)... ###"
sudo apt full-upgrade -y

# 3. Uuenda kõiki paigaldatud Snap pakette
echo
print_header "### 3/5: Updating Snap packages... ###"
sudo snap refresh

# 4. Uuenda Flatpak pakette (kui see on paigaldatud)
if command -v flatpak &> /dev/null
then
    echo
    print_header "### 4/5: Updating Flatpak packages... ###"
    sudo flatpak update -y
else
    echo
    print_header "### 4/5: Flatpak not found. Skipping. ###"
fi

# 5. Eemalda vanad ja mittevajalikud paketid
echo
print_header "### 5/5: Removing unused packages... ###"
sudo apt autoremove -y
sudo apt autoclean

echo
echo "--- System update complete! ---"
