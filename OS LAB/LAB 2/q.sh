# ========================== LAB EXERCISES: (PART 1) ==========================

# 1. Try the following shell commands
echo $HOME
echo $PATH
echo $MAIL
echo $USER
echo $SHELL
echo $TERM

# 2. Try the following snippet, which illustrates the difference between local and environment variable:
firstname=Rakesh
lastname=Sharma
echo $firstname $lastname
export lastname # make it a global variable
sh # start child shell
echo $firstname $lastname
echo $firstname $lastname

# 3. Try the following snippet, which illustrates the meaning of special local variables:
cat >script.sh
echo the name of this script is $0
echo the first argument is $1
echo a list of all the arguments is $*
echo this script places the date into a temporary file
echo called $1.$$
date > $1.$$ # redirect the output of date
ls $1.$$ # list the file rm $1.$$
rm # remove the file

chmod +x script.sh # change permission to executable
./script.sh Rahul Sachin Kumble # argument


# ========================== LAB EXERCISES: (PART 2) ==========================

# 4. Try the following, which illustrates the usage of ps:
(sleep 10; echo done) &
ps

# 5. Try the following, which illustrates the usage of kill:
(sleep 10; echo done) &
kill pid # pid is the process id of background process

# 6. Try the following, which illustrates the usage of wait:
(sleep 10; echo done 1 ) &
(sleep 10; echo done 2 ) &
echo done 3; wait ; echo done 4


# ========================== LAB EXERCISES: (PART 3) ==========================

# 7. List all the files under the given input directory, whose extension has only one character
cat > ex3q1.sh
cd $1
ls *.[a-z]
# come out of the file now
chmod +x ex3q1.sh # change permission to executable

# 8. Write a shell script that accepts two command line parameters. First parameter indicates the
# directory and the second parameter indicates a regular expression. The script should display all
# the files and directories in the directory specified in the first argument matching the format
# specified in the second argument.
cat > ex3q3.sh
cd $1
ls $2
# come out of the file now
chmod +x ex3q2.sh # change permission to executable

# 9. Count the number of users logged on to the system. Display the output as Number of users
# logged into the system.
echo "Number of logged in users are : $(who | wc -l)"

# 10. Count only the number of files in the current directory.
cat > ex3q4.sh
echo Number of files in the directory are `ls -l|grep "^-" | wc -l`
# come out of the file now
chmod +x ex3q2.sh # change permission to executable

# 11. Write a shell script that takes two sorted numeric files as input and produces a single sorted
# numeric file without any duplicate contents.
cat ex3q5a.sh
#contents in the file
1
2
2
3
# come out of this file
cat ex3q5b.sh
#contents in the file
1
1
2
3
3
# come out of this file
cat ex3q5a.sh > ex3q5c.sh
cat ex3q5b.sh >> ex3q5c.sh
cat ex3q5c.sh # will display the contents of the file and it will be listed like this below :
1
1
1
2
2
2
3
3
3
# now, run the following commant outside the file
sort ex3q5c.sh -u # sort and sustain unique elements

# 12. Write a shell script that accepts two command line arguments. First argument indicates format
# of file and the second argument indicates the destination directory. The script should copy all
# the files as specified in the first argument to the location indicated by the second argument.
# Also, try the script where the destination directory name has space in it.
!/bin/bash
cp ./$1 $2
# now make files
touch a.a
touch b.a
touch c.a
mkdir finald # final destination file
./6.sh '*.a' finald/
ls finald
# a.a b.a c.a -> all files will be copied here