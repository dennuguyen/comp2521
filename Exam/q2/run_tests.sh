#!/bin/sh

if [ ! -d "tests" ]
then
	echo "You must run this script from your 'q1' directory"
	exit 1
fi

if [ ! -x "gist" ]
then
	echo "You don't seem to have a program to test"
	echo "Did you run make? Were there any errors?"
	exit 1
fi

ulimit -t 10
for t in 01 02 03 04 05 06 07 08 09 10 11
do
	tt="tests/$t"
	sh $tt.sh 2>&1 | head -n100 > $tt.observed
	diff -wi $tt.expected $tt.observed > $tt.diffs

	echo ""
	echo "===== Test $t ====="
	if [ ! -s "$tt.diffs" ]
	then
		echo OK
	else
		echo FAILED
		echo ""
		echo "===== Differences between expected and observed output ===="
		cat "$tt.diffs"
		echo ""
		echo "You can see the complete expected output in $tt.expected"
		echo "You can see your complete output in $tt.observed"
#		head -n10 $tt.observed
#		echo ""
#		echo "===== First ten lines of expected output ====="
#		head -n10 $tt.expected
#		echo ""
#		echo "See the file $t.diffs for diff output"
	fi
done
