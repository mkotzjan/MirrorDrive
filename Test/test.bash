#!/bin/bash
count=0

echo
echo ----------------
echo -- Start Test --
echo ----------------
echo

# Tests
if [ -d "Destination/A" ]; then
  echo -e "\e[32m+++\033[0m Destination/A exists"
else
  echo -e "\e[31m---\033[0m Destination/A does not exist"
  count=$((count + 1))
fi

if [ -d "Destination/B" ]; then
  echo -e "\e[32m+++\033[0m Destination/B exists"
else
  echo -e "\e[31m---\033[0m Destination/B does not exist"
  count=$((count + 1))
fi

if [ -d "Destination/C" ]; then
  echo -e "\e[32m+++\033[0m Destination/C exists"
else
  echo -e "\e[31m---\033[0m Destination/C does not exist"
  count=$((count + 1))
fi

if [ -d "Destination/A/D" ]; then
  echo -e "\e[32m+++\033[0m Destination/A/D exists"
else
  echo -e "\e[31m---\033[0m Destination/A/D does not exist"
  count=$((count + 1))
fi

if [ -d "Destination/A/E" ]; then
  echo -e "\e[32m+++\033[0m Destination/A/E exists"
else
  echo -e "\e[31m---\033[0m Destination/A/E does not exist"
  count=$((count + 1))
fi

if [ -f "Destination/A.txt" ]; then
  echo -e "\e[32m+++\033[0m Destination/A.txt exists"
else
  echo -e "\e[31m---\033[0m Destination/A.txt does not exist"
  count=$((count + 1))
fi

if [ -f "Destination/B.txt" ]; then
  echo -e "\e[32m+++\033[0m Destination/B.txt exists"
else
  echo -e "\e[31m---\033[0m Destination/B.txt does not exist"
  count=$((count + 1))
fi

if [ -f "Destination/A/C.png" ]; then
  echo -e "\e[32m+++\033[0m Destination/A/C.png exists"
else
  echo -e "\e[31m---\033[0m Destination/A/C.png does not exist"
  count=$((count + 1))
fi

if [ -f "Destination/B/D.txt" ]; then
  echo -e "\e[32m+++\033[0m Destination/B/D.txt exists"
else
  echo -e "\e[31m---\033[0m Destination/B/D.txt does not exist"
  count=$((count + 1))
fi

if [ -f "Destination/B/E.txt" ]; then
  echo -e "\e[32m+++\033[0m Destination/B/E.txt exists"
else
  echo -e "\e[31m---\033[0m Destination/B/E.txt does not exist"
  count=$((count + 1))
fi

if [ -f "Destination/C/F.pdf" ]; then
  echo -e "\e[32m+++\033[0m Destination/C/F.pdf exists"
else
  echo -e "\e[31m---\033[0m Destination/C/F.pdf does not exist"
  count=$((count + 1))
fi

if [ -f "Destination/A/D/G.txt" ]; then
  echo -e "\e[32m+++\033[0m Destination/A/D/G.txt exists"
else
  echo -e "\e[31m---\033[0m Destination/A/D/G.txt does not exist"
  count=$((count + 1))
fi

if [ -f "Destination/A/D/H.cpp" ]; then
  echo -e "\e[32m+++\033[0m Destination/A/D/H.cpp exists"
else
  echo -e "\e[31m---\033[0m Destination/A/D/H.cpp does not exist"
  count=$((count + 1))
fi

if [ -f "Destination/A/E/I.index" ]; then
  echo -e "\e[32m+++\033[0m Destination/A/E/I.index exists"
else
  echo -e "\e[31m---\033[0m Destination/A/E/I.index does not exist"
  count=$((count + 1))
fi

echo
echo ----------------
echo "--- Result:  ---"
if [ $count == 0 ]; then
  echo -e "\e[32m+++ Success! +++\033[0m"
else
echo -e "\e[31m---" $count "Failed ---\033[0m"
fi
echo --- Finished ---
echo ----------------
echo
