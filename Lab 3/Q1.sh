echo -n "Enter file name: "
read filename
result=`file $filename`
if [[ $result == "$filename: directory" ]]; then
echo "It is a directory"
else
echo "Not a directory"
fi
