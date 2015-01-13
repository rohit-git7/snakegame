#!/bin/bash
points=$1
high_score=`tail -1 high.txt`
if [ $high_score -lt $points ]
then
echo $points > high.txt
fi
