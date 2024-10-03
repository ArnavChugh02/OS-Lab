for i in *.txt;do
if [ -e "$file" ];then
mv "$file" "${file%.txt}.text"
echo "Renamed: $file -> ${file%.txt}.text"
fi
done                         
