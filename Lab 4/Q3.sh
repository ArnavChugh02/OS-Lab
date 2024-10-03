n=$#
arr=("$@")
sortarray(){
for ((i=0;i<$n;i++))
do
	for ((j=0;j<n-i-1;j++))
	do
		if [[ ${arr[j]} > ${arr[$j+1]} ]]; then
			temp=${arr[j]}
			arr[j]=${arr[$j+1]}
			arr[$j+1]=$temp
		fi
	done
done
}
sortarray arr
for i in "${arr[@]}"; do
	echo $i
done