g++ -std=c++17 meow.cpp
#clang++ -std=c++17 -Wl,--stack-size,16777216 meow.cpp  -o meow  # Sets stack to ~256MB
./a.out
