#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;


int main(int argc, char const *argv[]) 
{
    int n;
    cin >> n;
    vector<int> v(n);
    for(auto &elem : v) {
        cin >> elem;
    }

    reverse(v.begin(), v.end());

    vector<int> seq(v.size() + 1, numeric_limits<int>::max());
    seq.front() = numeric_limits<int>::min();
    vector<int> pos(v.size() + 1, -1);
    vector<int> prev(v.size(), -1);
    int max_ = 0;

    for (auto i = 0; i < v.size(); ++i) {
        int j = distance(seq.begin(), upper_bound(seq.begin(), seq.end(), v[i]));

        if (seq[j - 1] <= v[i] && v[i] < seq[j]) {
          seq[j] = v[i];
          pos[j] = i;
          prev[i] = pos[j - 1];
          max_ = max(max_, j);
        }
    }

    vector<int> answer;
    vector<int> v_indexs;
    auto k = pos[max_];

    while (k != -1) {
        answer.push_back(v[k]);
        v_indexs.push_back(v.size() - k);
        k = prev[k];
    }

    cout << v_indexs.size() << endl;
    for (auto &elem : v_indexs) {
        cout << elem << ' ';
    }
    cout << endl;

    return 0;
}
