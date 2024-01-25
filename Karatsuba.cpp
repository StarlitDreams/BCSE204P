#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int max(int a, int b) { return (a > b) ? a : b; }

void normalizeLengths(string &a, string &b) {
    int lenA = a.size();
    int lenB = b.size();
    if (lenA < lenB) {
        for (int i = 0; i < lenB - lenA; i++) {
            a = '0' + a;
        }
    } else if (lenB < lenA) {
        for (int i = 0; i < lenA - lenB; i++) {
            b = '0' + b;
        }
    }
}

string addStrings(string first, string second) {
    string result;

    
    normalizeLengths(first, second);
    int length = first.size();

    int carry = 0;
    for (int i = length - 1; i >= 0; i--) {
        int sum = ((first[i] - '0') + (second[i] - '0') + carry);
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    if (carry) {
        result.push_back(carry + '0');
    }

    reverse(result.begin(), result.end());
    return result;
}


string subtractStrings(string larger, string smaller) {
    string result;

   
    normalizeLengths(larger, smaller);
    int length = larger.size();

    for (int i = length - 1; i >= 0; i--) {
        int diff = (larger[i] - '0') - (smaller[i] - '0');
        if (diff >= 0) {
            result.push_back(diff + '0');
        } else {
       
            int j = i - 1;
            while (j >= 0 && larger[j] == '0') {
                larger[j] = '9';
                j--;
            }
            larger[j]--;

            result.push_back(diff + 10 + '0');
        }
    }

    reverse(result.begin(), result.end());

    while (result[0] == '0' && result.length() != 1) {
        result.erase(0, 1);
    }

    return result;
}


string karatsubaMultiply(string X, string Y) {
    
    if (X.size() == 1 && Y.size() == 1) {
        int result = (X[0] - '0') * (Y[0] - '0');
        return to_string(result);
    }

   
    normalizeLengths(X, Y);
    int n = X.size();

    if (n == 1) {
        return to_string((X[0] - '0') * (Y[0] - '0'));
    }

    int fh = n / 2;   
    int sh = (n - fh); 

   
    string Xl = X.substr(0, fh);
    string Xr = X.substr(fh, sh);
    
    string Yl = Y.substr(0, fh);
    string Yr = Y.substr(fh, sh);

    
    string p1 = karatsubaMultiply(Xl, Yl);
    string p2 = karatsubaMultiply(Xr, Yr);
    string p3 = karatsubaMultiply(addStrings(Xl, Xr), addStrings(Yl, Yr));

   
    string firstPart = p1.append(2 * sh, '0');
    string secondPart = subtractStrings(p3, addStrings(p1, p2)).append(sh, '0');
    string result = addStrings(firstPart, addStrings(secondPart, p2));

    
    while (result[0] == '0' && result.length() != 1) {
        result.erase(0, 1);
    }

    return result;
}

int main(void) {
    
    string X;
    string Y;
    cout<<"Enter the first number: ";
    cin>>X;
    cout<<"Enter the second number: ";
    cin>>Y;

    cout << "Multiplication of " << X << " and " << Y << " is: " << karatsubaMultiply(X, Y) << endl;

   
}
