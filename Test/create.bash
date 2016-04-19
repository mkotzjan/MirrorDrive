#!/bin/bash
echo -- Start --

# Delete if exist
if [ -d "Source" ]; then
  echo - Delete Source
  rm -r Source
fi

if [ -d "Destination" ]; then
  echo - Delete Destination
  rm -r Destination
fi

# Create folders
echo - Create source folder
mkdir Source
echo - Create destination folder
mkdir Destination

# Fill with some demo data
echo - Fill source folder
mkdir Source/A
mkdir Source/B
mkdir Source/C
mkdir Source/A/D
mkdir Source/A/E
echo > Source/A.txt
echo > Source/B.txt
echo > Source/A/C.png
echo > Source/B/D.txt
echo > Source/B/E.txt
echo > Source/C/F.pdf
echo > Source/A/D/G.txt
echo > Source/A/D/H.cpp
echo > Source/A/E/I.index

echo -- Finished --
