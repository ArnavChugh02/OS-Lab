arrAsFunc() {
    local -n p1=$1
    local -n p2=$2
    for i in "${p1[@]}"; do
        for j in "${p2[@]}"; do
            if [ "$i" = "$j" ]; then
                echo "$i"
                echo "$j"
            fi
        done
    done
}

a=(ab jd nh)
b=(ab jd ne)

arrAsFunc a b

