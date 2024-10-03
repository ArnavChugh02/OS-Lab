declare -a arrA
j=0
for i in $@
do
arrA[j]=$i
((j++))
done
echo ${arrA[@]}
