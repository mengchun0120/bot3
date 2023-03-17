folders="commonlib botlib desktop"

sum=0
for folder in $folders; do
    x=$(find $folder -name "*.cpp" -or -name "*.h" | xargs wc -l | grep total | awk '{print $1}')
    sum=$(expr $sum + $x)
done

echo $sum
