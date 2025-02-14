# ========================== LAB EXERCISES ==========================


# 1. Find whether the given number is even or odd.
echo "Enter a number:"
read number
if [ $((number % 2)) -eq 0 ]; then
    echo "even"
else
    echo "odd"
fi


# 2. Print the first ‘n’ odd numbers.
echo "Enter the number of odd numbers to print:"
read n
count=0
number=1
while [ $count -lt $n ]; do
    echo $number
    number=$((number + 2))
    count=$((count + 1))
done


# 3. Find all the possible quadratic equation roots using case.
#!/bin/bash
echo "Enter coefficients for the quadratic equation ax^2 + bx + c"
echo "Enter a:"
read a
echo "Enter b:"
read b
echo "Enter c:"
read c
# Calculate the discriminant
D=$((b * b - 4 * a * c))
# Use case to handle different values of the discriminant
case $D in
    # If D > 0
    [1-9]*)
        echo "Real and different roots"
        x1=$(( (-b - (D ** 0.5)) / (2 * a) ))
        x2=$(( (-b + (D ** 0.5)) / (2 * a) ))
        echo "x1 = $x1"
        echo "x2 = $x2"
        ;;
    # If D = 0
    0)
        echo "Real and same root"
        x=$(( -b / (2 * a) ))
        echo "x = $x"
        ;;
    # If D < 0
    *)
        echo "Imaginary roots"
        ;;
esac


# 4. Find the factorial of a given number.
#!/bin/bash
echo "Enter number to find factorial of:"
read n
# Initialize factorial result
x=1
# Loop to calculate factorial
for ((y=n; y>0; y--)); do
    x=$((x * y))
done
echo "Factorial is $x"




# ========================== EXTRA EXERCISES ==========================


# 1. Print if a number is positive, negative or zero.
echo "Enter a number:"
read number
if [ $number -lt 0 ]; then
    echo "negative"
elif [ $number -eq 0 ]; then
    echo "zero"
else
    echo "positive"
fi


# 2. Take a file as input and compile it if it is a C file.
case $1 in
*.c)
    cc $1
    ;;
*.h|*.sh)
    # do nothing
    ;;
*)
    echo "Unsupported file type"
    ;;
esac