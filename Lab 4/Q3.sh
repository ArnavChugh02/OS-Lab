i=0
for j in $*
do
arr[i]=$j
((j++))
done
echo ${arr[@]}
