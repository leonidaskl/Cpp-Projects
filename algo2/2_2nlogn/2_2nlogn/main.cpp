
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

// Binary search (note boundaries in the caller), Πολυπλοκοτητας nlogn

int CeilIndex( vector<int>& arr, int l, int r, int key )
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (arr[m] >= key)
            r = m;
        else
            l = m;
    }
    
    return r;
}

int LongestIncreasingSubsequenceLength( vector<int>& arr )
{
    if (arr.size() == 0)
        return 0;
    
    vector<int> tail(arr.size(), 0);
    int length = 1; // always points empty slot in tail
    
    tail[0] = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        
        // new smallest value
        if (arr[i] < tail[0])
            tail[0] = arr[i];
        
        // v[i] extends largest subsequence
        else if (arr[i] > tail[length - 1])
            tail[length++] = arr[i];
        
        else
            tail[CeilIndex(tail, -1, length - 1, arr[i])] = arr[i];
    }
    tail.clear();
    return length;
}



int main()
{
    int n, temp;
    
    //ifstream infile("test.txt");
    
    
    vector<int> arr;
    vector<int> rarr;
    vector<int> rlis;
    vector<int> lis;
    cin >> n;
    
    //infile >> n;
    //cout << n << endl;
    
    for (int i = 0; i < n; i++) {
        
        cin >> temp;
        //infile >> temp;
        //cout << temp << " ";
        arr.push_back(temp);
        lis.push_back(LongestIncreasingSubsequenceLength(arr));
        
        
    }
    //cout << endl;
    rarr.push_back(arr[n-1]);
    rlis.push_back(0);
    for (int i = n-1; i > 0; i--) {
        
        rarr.insert(rarr.begin(), arr[i]);
        rlis.insert(rlis.begin(), LongestIncreasingSubsequenceLength(rarr));
        
    }
    
    rarr.insert(rarr.begin(), arr[0]);
    rlis.insert(rlis.begin(), LongestIncreasingSubsequenceLength(rarr));
    
    
    arr.clear();
    rarr.clear();
    int max = 0;
    for (int i = 0; i < n - 1; i++)
        if (lis[i] + rlis[i + 1] > max)
            max = lis[i] + rlis[i + 1];
    if (max > lis[n-1])
        cout << max << endl;
    else
        cout << lis[n] << endl;
    lis.clear();
    rlis.clear();
    
    
    
    return 0;
}

