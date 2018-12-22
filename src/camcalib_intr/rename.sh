#!/bin/sh

# settings
headname="cam2chess"
extension=".png"

# find file numbers in a current directory
total_file_num=$(ls ./tmp_data | wc -l)
echo "FILE NUMBERS:"$total_file_num

# make a directory to keep original data
rm -r ./tmp_data/renamed_data
mkdir ./tmp_data/renamed_data

# rename
cnt=0
for i in ./tmp_data/*.png
do
# rename
newname=$headname$cnt$extension
cp $i ./tmp_data/renamed_data/$newname

cnt=$(($cnt + 1))
done

echo "RENAME COMPLESION"
