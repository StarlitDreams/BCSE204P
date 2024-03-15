#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int value;
    int weight;
    Item(int value, int weight) : value(value), weight(weight) {}
};

struct Node {
    int level;
    int profit;
    int weight;
    double bound;
};

bool cmp(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double bound(Node u, int n, int W, vector<Item>& arr) {
    if (u.weight >= W) return 0;
    
    double profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;
    
    while ((j < n) && (totweight + arr[j].weight <= W)) {
        totweight    += arr[j].weight;
        profit_bound += arr[j].value;
        j++;
    }
    
    if (j < n) {
        profit_bound += (W - totweight) * (double)arr[j].value / arr[j].weight;
    }
    
    return profit_bound;
}

int knapsack(int W, vector<Item>& arr, int n) {
    sort(arr.begin(), arr.end(), cmp);
    
    vector<Node> Q;
    Node u, v;
    
    u.level = -1;
    u.profit = u.weight = 0;
    Q.push_back(u);
    
    int maxProfit = 0;
    while (!Q.empty()) {
        u = Q.back();
        Q.pop_back();
        
        if (u.level == -1) v.level = 0;
        if (u.level == n-1) continue;
        
        v.level = u.level + 1;
        
        v.weight = u.weight + arr[v.level].weight;
        v.profit = u.profit + arr[v.level].value;
        
        if (v.weight <= W && v.profit > maxProfit)
            maxProfit = v.profit;
        
        v.bound = bound(v, n, W, arr);
        
        if (v.bound > maxProfit)
            Q.push_back(v);
        
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, W, arr);
        if (v.bound > maxProfit)
            Q.push_back(v);
    }
    
    return maxProfit;
}

int main() {
    int W = 50;
    vector<Item> arr = {{60, 10}, {100, 20}, {120, 30}};
    
    int n = arr.size();
    
    cout << "Maximum possible profit: " << knapsack(W, arr, n);
    
    return 0;
}
