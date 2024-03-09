#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++)    
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

void findSubsets(vector<int>& arr, int index, vector<int>& current, int sum, int m) {
    if (sum == m) {
        cout << "{ ";
        for (int i = 0; i < current.size(); i++)
            cout << current[i] << " ";
        cout << "}" << endl;
        return;
    }

    if (index == arr.size() || sum > m) {
        return;
    }

    current.push_back(arr[index]);
    findSubsets(arr, index + 1, current, sum + arr[index], m);
    
    current.pop_back();
    findSubsets(arr, index + 1, current, sum, m);
}

int main() {
    vector<int> S = {3, 34, 4, 12, 5, 2, 5, 7, 8, 9, 10, 11, 6, 13, 14};
    int m = 30;
    vector<int> currentSet;

    bubbleSort(S);
    findSubsets(S, 0, currentSet, 0, m);

    return 0;
}
