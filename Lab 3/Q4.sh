echo "enter basics"
read ba
echo "enter TA"
read ta
gs=$(echo "scale=2; $ba * 1.1 + $ta" | bc)
echo "GS = $gs"