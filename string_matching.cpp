#include <iostream>
#include <vector>
#include <string>

using namespace std;

void naiveStringMatcher(const string& T, const string& P) {
    int n = T.length();
    int m = P.length();
    for (int i = 0; i <= n - m; ++i) {
        int j;
        for (j = 0; j < m; ++j) {
            if (T[i + j] != P[j]) {
                break;
            }
        }
        if (j == m) {
            cout << "Pattern found at index " << i << endl;
        }
    }
}

vector<int> computeLPSArray(const string& P) {
    int m = P.length();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;
    while (i < m) {
        if (P[i] == P[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void KMPMatcher(const string& T, const string& P) {
    int n = T.length();
    int m = P.length();
    vector<int> lps = computeLPSArray(P);

    int i = 0;
    int j = 0;
    while (i < n) {
        if (P[j] == T[i]) {
            j++;
            i++;
        }
        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < n && P[j] != T[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i = i + 1;
            }
        }
    }
}

int main() {
    string T = "000010001010001";
    string P = "0001";
    cout << "Naive String Matching:\n";
    naiveStringMatcher(T, P);
    cout << "\nKMP String Matching:\n";
    KMPMatcher(T, P);
    return 0;
}
