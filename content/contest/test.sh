for((i=1;i>0;i++)) do
    echo "$i"
    ./gen $i > test.in
    ./main < test.in > main.out
    ./brut < test.in > brut.out
    diff -b main.out brut.out || break
done
