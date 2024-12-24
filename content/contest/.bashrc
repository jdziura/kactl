c() {
  g++ -std=c++20 -fsanitize=address,undefined -g \
    -DLOCAL -Wall -Wextra -Wshadow $1.cpp -o $1;
}
nc() { g++ -std=c++20 -O2 $1.cpp -o $1; }
alias rm='trash'
alias mv='mv -i'
alias cp='cp -i'
