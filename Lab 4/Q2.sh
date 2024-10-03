while :
do
echo "Do you want to remove a file (yes/no): "
read a
if [ "$a" = "yes" ]; then
	echo -n "File Name:"
	read filename
	echo $filename " removed successfully."
	rm $filename
else
	echo "Exiting.."
	break 
fi
done


