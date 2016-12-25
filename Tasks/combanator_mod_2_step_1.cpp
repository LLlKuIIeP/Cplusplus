#include <iostream>
#include <vector>


int n, m;
std::vector<int> letters;
std::vector<bool> usd;
std::vector<int> res;

void placement_lex(int pos) {
        if (pos == m) {
                for(auto &elem : res) {
                        std::cout << elem << " ";
                }
                std::cout << std::endl;

            return;
        }

        for(int i = 0; i < n; ++i) {
                if (!usd[i]) {
                        usd[i] = true;
                        res[pos] = letters[i];
                        placement_lex(pos + 1);
                        usd[i] = false;
                }
        }
}

int main(int argc, char *argv[]) {


        std::cin >> n >> m;
        for(int i = 0; i < n; ++i) {
                letters.push_back(i);
        }

        usd.resize(n);
        res.resize(m);
        placement_lex(0);

        return 0;
}

