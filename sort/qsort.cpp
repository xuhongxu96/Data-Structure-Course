#include <iostream>
using namespace std;

int arr[100];
int n;

void quickSort(int l, int r) {
	if (r - l > 1) {
		int pos = l;
		int data = arr[l];
		for (int i = l + 1; i < r; ++i) {
			if (arr[i] < data) {
				++pos;
				if (pos != i) {
					int temp = arr[pos];
					arr[pos] = arr[i];
					arr[i] = temp;
				}
			}
		}
		arr[l] = arr[pos];
		arr[pos] = data;
		for (int i = 0; i < n; ++i) cout << arr[i] << " ";
		cout << endl;

		quickSort(l, pos);
		quickSort(pos + 1, r);
	}

}

int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> arr[i];
	quickSort(0, n);
	for (int i = 0; i < n; ++i) cout << arr[i] << " ";
	return 0;
}
