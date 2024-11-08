// GROUP:   2
// ID:      20227012
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    Rodyna Amr Fathy

#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long CountInvMerge(long long* a, int n)
{
    int mid = n / 2;
    int i = 0, j = mid, k = 0;
    long long inv_count = 0;

    // Temporary array for merging
    long long* temp = new long long[n];
    
    // Copy elements from a to temp
    for (int idx = 0; idx < n; idx++) {
        temp[idx] = a[idx];
    }

    while (i < mid && j < n)
    {
        if (temp[i] <= temp[j])
        {
            a[k++] = temp[i++];
        }
        else
        {
            a[k++] = temp[j++];
            inv_count += (mid - i);  // Count inversions
        }
    }

    // Copy the remaining elements of the left half, if any
    while (i < mid)
        a[k++] = temp[i++];

    // Copy the remaining elements of the right half, if any
    while (j < n)
        a[k++] = temp[j++];

    delete[] temp;
    return inv_count;
}

long long CountInv(long long* a, int n)
{
    long long inv_count = 0;

    if (n <= 1)
        return 0;

    int mid = n / 2;

    // Recursively count inversions in left and right halves
    inv_count += CountInv(a, mid);
    inv_count += CountInv(a + mid, n - mid);

    // Count and merge inversions between left and right halves
    inv_count += CountInvMerge(a, n);

    return inv_count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n;
    while (true) {
        cin >> n;

        if (n == 0) break;

        long long* a = new long long[n];

        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        cout << CountInv(a, n) << endl;
        delete[] a;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
