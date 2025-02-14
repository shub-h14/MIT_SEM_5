# Write shell commands for the following.
# i) To create a directory in your home directory having 2 subdirectories.
mkdir regno/{sub1,sub2}

# ii) In the first subdirectory, create 3 different files with different content in each of them.
cd sub 1
echo "File one" > 1.txt
echo "File two" > 2.txt
echo "File three" > 3.txt

# iii) Copy the first file from the first subdirectory to the second subdirectory.
cp 1.txt '/home/student/regno/sub2'

# iv) Create one more file in the second subdirectory, which has the output of the number of users and number of files.
echo "Number of users are : `ls/home | wc -l` and number of files on home directory are : `lc -l | grep "^d" | wc -l`" > home/student/regno/sub2/count.txt

# v) To list all the files which starts with either a or A. vi)To count the number of files in the current directory.
ls | grep ^[aA]

# vi) To count the number of files in the current directory.
ls | wc -l

# vii) Display the output if the compilation of a program succeeds.
cc hello.c && ./a.out

# viii) Count the number of lines in an input file.
wc -l hello.c

# 2. Execute the following commands in sequence: i) date ii) ls iii) pwd
date;ls;pwd