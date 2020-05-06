make
cd bin

cat ../test.txt | ./main > out.txt

cmp "out.txt" "../verify.txt";

red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

status=$?
if [[ $status = 0 ]]; then
    echo "${green}Test passed.${reset}"
else
    echo "${red}Test failed.${reset}"
fi