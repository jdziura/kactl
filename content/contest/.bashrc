c() {
  g++ -std=c++20 -fsanitize=address,undefined -ggdb3 \
    -DLOCAL -Wall -Wextra -Wshadow -Wfloat-equal $1.cpp -o $1;
}
nc() { g++ -DLOCAL -g -std=c++20 -O2 $1.cpp -o $1; }
