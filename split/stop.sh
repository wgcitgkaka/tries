#!/bin/sh
for line in `ps -ef | grep 'split' | awk '{print $2}' | sed '$d'`
do
kill -9 $line
done 
