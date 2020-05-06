make
cd bin

cat ../test.txt | ./main > out.txt

cmp "out.txt" "../verify.txt";

#print comparison status
status=$?
if [[ $status = 0 ]]; then
    echo "${green}Test passed.${reset}"
else
    echo "${red}Test failed.${reset}"
fi