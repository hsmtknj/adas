#!bin/sh
# @(#) file: initdir.sh
# @(#)
# @(#) [DESCRIPTION]
# @(#) This script provides initializing for the following directories.
# @(#)      - input_data
# @(#)      - detected_data
# @(#)      - output_data
# @(#) This script deletes all files excluding *.md.
# @(#) 
# @(#) [USAGE]
# @(#) initdir.sh

# initialize intput directry
echo "INITIALIZE INPUT_DIRECTORY"
cd ./input_data
ls | grep -v -E 'md$' | xargs rm -r
cd ..

# initialize detected directry
cd ./detected_data
echo "INITIALIZE DETECTED_DIRECTORY"
ls | grep -v -E 'md$' | xargs rm -r
cd ..

# initialize output directry
cd ./output_data
echo "INITIALIZE OUTPUT_DIRECTORY"
ls | grep -v -E 'md$' | xargs rm -r
cd ..
