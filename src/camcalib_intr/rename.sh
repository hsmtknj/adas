#!/bin/sh

# settings
headname=$1   # e.g. cam1chess
extension=$2  # e.g. .png
directory=$3  # e.g. input_data, output_dta, etc.

# find file numbers in a current directory
total_file_num=$(ls ./$directory/*$extension | wc -l)
echo "FILE NUMBERS:"$total_file_num

# make a directory to keep original data
# rm -r ./$directory/renamed_data
mkdir ./$directory/renamed_data

# rename
cnt=0
for i in ./$directory/*$extension
do
# rename
newname=$headname$cnt$extension
cp $i ./$directory/renamed_data/$newname

cnt=$(($cnt + 1))
done

echo "RENAME COMPLESION"
