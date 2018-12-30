#!bin/sh
# @(#) rename.sh
# @(#)
# @(#) [DESCRIPTION]
# @(#) This script rename files in a desinaged input directory
# @(#) into sequential order filename.
# @(#) 
# @(#) If you set a directory, you can get renamed file in the
# @(#) "renamed_data" directory under the directory you set.
# @(#) 
# @(#) [USAGE]
# @(#) rename.sh $1 $2 $3
# @(#)      $1 : filename without an extension
# @(#)      $2 : file extension
# @(#)      $3 : target directory

# settings
fname=$1   # e.g. cam1chess
extension=$2  # e.g. .png
directory=$3  # e.g. input_data, output_data, etc.

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
newname=$fname$cnt$extension
cp $i ./$directory/renamed_data/$newname

cnt=$(($cnt + 1))
done

echo "RENAME COMPLESION"
