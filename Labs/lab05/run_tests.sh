#!/bin/sh

RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET_COLOR="\033[0m"

QNAME="lab05"
BIN="./glab"

echo "Compiling..."
make || exit 1
echo

if [ ! -f "$BIN" ]
then
	echo "No such executable: $BIN"
	exit 1
fi

if [ ! -x "$BIN" ]
then
	echo "$BIN is not executable"
	exit 1
fi

if [ ! -d tests ]
then
	echo "Missing tests directory"
	exit 1
fi

if [ "$#" -eq 0 ]
then
	inFiles="*"
elif [ "$#" -eq 1 ]
then
	inFiles="empty"
else
	echo "Usage-1: autotest  "
	echo "Usage-2: autotest <test-number> "
	exit 1
fi

echo "***  Testing $QNAME  ***"
echo

for gg in graphs/$inFiles
do
    g=`basename $gg`
	$BIN $gg < tests/$g.in > tests/$g.out
	echo "------------------------------ "
	if diff tests/$g.exp tests/$g.out > /dev/null
    then
        printf "${GREEN}Test $g passed\n$RESET_COLOR"
    else
        printf "${RED}Test $g failed\n$RESET_COLOR"
        printf "${YELLOW}Check differences between tests/$g.exp and tests/$g.out\n$RESET_COLOR"
    fi
	echo "------------------------------ "
done
