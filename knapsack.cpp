#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Item {
public:
    int value;
    int weight;
    double density;

    Item(int v, int w) : value(v), weight(w) {
        density = (double)value / weight;
    }
};

void sortItemsByDensity(vector<Item>& items) {
    int n = items.size();
    for (int i = 1; i < n; i++) {
        Item key = items[i];
        int j = i - 1;
        while (j >= 0 && items[j].density < key.density) {
            items[j + 1] = items[j];
            j = j - 1;
        }
        items[j + 1] = key;
    }
}

double knapsack(int W, vector<Item>& items) {
    sortItemsByDensity(items); 
    int curWeight = 0; 
    double finalvalue = 0.0;
    for (size_t i = 0; i < items.size(); i++) {
        if (curWeight + items[i].weight <= W) {
            curWeight += items[i].weight;
            finalvalue += items[i].value;
        } else {
            int remain = W - curWeight;
            finalvalue += items[i].value * ((double) remain / items[i].weight);
            break;
        }
    }
    return finalvalue;
}

int main() {
    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;
    cout << "Enter the capacity of knapsack: ";
    cin >> W;
    vector<Item> items;

    for (int i = 0; i < n; i++) {
        int value, weight;
        cout << "Enter value and weight for item " << i + 1 << ": ";
        cin >> value >> weight;
        items.emplace_back(value, weight);
    }

    cout << "Maximum value we can obtain = " << knapsack(W, items);
    return 0;
}
