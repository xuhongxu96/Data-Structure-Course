#include <iostream>
using namespace std;

int arr[100];
int n;

void selectionSort() {
	for (int i = 0; i < n; ++i) {
		int minV = arr[i];
		int mi = i;
		int j;
		for (j = i + 1; j < n; ++j) {
			if (arr[j] < minV) {
				minV = arr[j];
				mi = j;
			}
		}
		arr[mi] = arr[i];
		arr[i] = minV;
		for (int i = 0; i < n; ++i) cout << arr[i] << " ";
		cout << endl;
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> arr[i];
	selectionSort();
	return 0;
}
