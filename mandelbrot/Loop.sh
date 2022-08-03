#!/bin/bash
LoopTargets=""
NoTargest=$1
StartScale=$(printf "%.12f" $2)
Step=$(printf "%.12f" $3)
for Target in `seq $NoTargest` ; do
    File="$(printf '%04d' $Target).ppm"
    # printf "%04d.ppm: a.out" $Target
    # printf "\t./a.out 1 %04d.ppm 8e-9" $Target
    echo $File: a.out
    echo $'\t'./a.out $File $StartScale
    LoopTargets="$LoopTargets $File"
    StartScale=$(echo $StartScale + $Step|bc)
done
echo;echo;echo LoopTargets:$LoopTargets