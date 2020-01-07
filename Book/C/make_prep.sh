#
#  this is a simple shell script that I used to produce
#  the include file with the subset of files in the current
#  directory that are c source files.
#
#  Note: I was lazy and did not correctly handle the case 
#  of the last line which should not end with a continuation.
#  To cover that, you have to go into an editor and delete that
#  final, spurious continuation.
#
#  HISTORY: Written by Tim Mattson, December 24, 2019
#!/bin/bash
echo "source = \\"
while read LINE; do
     echo "   " $LINE  " \\"
done
