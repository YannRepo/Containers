
rm output_std
rm output_ft
rm output_diff
c++ -Wall -Wextra -std=c++98 -D TEST_CHOICE=1 main.cpp -o main && ./main >output_std
c++ -Wall -Wextra -std=c++98 -D TEST_CHOICE=0 main.cpp -o main && ./main >output_ft
diff output_std output_ft > output_diff
clear
cat output_diff
 