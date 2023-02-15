#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {2, 2, 2, 4, 4, 4, 5, 5, 6, 8, 8, 9};

    unordered_map<int, int> freq;
    int n = arr.size();
    int i = 0;

    while (i < n) {
        int count = 1;
        while (i < n-1 && arr[i] == arr[i+1]) {
            count++;
            i++;
        }
        freq[arr[i]] = count;
        i++;
    }

    cout << "Output: {";
    for (auto it = freq.begin(); it != freq.end(); ++it) {
        cout << it->first << ": " << it->second;
        if (next(it) != freq.end()) {
            cout << ", ";
        }
    }
    cout << "}" << endl;

    return 0;
}
