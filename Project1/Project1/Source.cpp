#define _CRT_SECURE_NO_WARNING

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm> 

using namespace std;


int length(std::vector<int> &arr)
{
	int res = 0;
	while (arr[res] != -1)
		res++;
	return res;

}

int print(std::vector<int> &arr, int N)
{
	for (int i = 0; i < N; i++)
	{
		std::cout << arr[i] << " ";
	}
	return 0;
}

int selectionSort(std::vector<int> &arr, int N)
{
	int smallest, j, i, exchange;

	for (i = 0; i < N - 1; i++)
	{
		smallest = i;
		for (j = i + 1; j < N; j++)
		{
			if (arr[j] < arr[smallest])
				smallest = j;
		}
		exchange = arr[i];
		arr[i] = arr[smallest];
		arr[smallest] = exchange;
	}

	return(0);
}

int bucketSort(std::vector<int> &arr, int N)
{
	int i, j, num, count;

	std::vector<std::vector<int>> basket(10, std::vector<int>(N + 1, 0));


	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < N + 1; j++)
		{
			basket[i][j] = -1;
		}
	}

	int nums[10] = { 0 };
	for (i = 0; i < N; i++)
	{
		int numi = arr[i] / 10;

		basket[numi][nums[numi]] = arr[i];//numi - номер коробочки 
		nums[numi] ++;

	}
	for (int i = 0; i < 10; i++)
	{
		count = length(basket[i]);
		selectionSort(basket[i], count);
	}
	int k = 0;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; basket[i][j] > -1; j++)
		{
			arr[k] = basket[i][j];
			k++;
		}
	}
	return 0;

}

int quickSortRandom(std::vector<int> &arr, int first, int last)
{
	int l = first;
	int r = last;
	std::vector<int> pivot(1);
	pivot[0] = first;
	while (first < last)
	{
		while ((arr[last] >= pivot[0]) && (first < last))
			last = last - 1;
		if (first != last)
		{
			arr[first] = arr[last];
			first = first + 1;
		}
		while ((arr[first] <= pivot[0]) && (first < last))
			first = first + 1;
		if (first != last)
		{
			arr[last] = arr[first];
			last = last - 1;
		}
	}
	arr[first] = pivot[0];
	pivot[0] = first;
	first = l;
	last = r;
	if (first < pivot[0])
		quickSortRandom(arr, first, pivot[0] - 1);
	if (last > pivot[0])
		quickSortRandom(arr, pivot[0] + 1, last);
	return 0;
}

int quickSortWorst(std::vector<int> &arr, int first, int last)
{
	if (last <= first) {
		return 0;
	}
	int pivot = 999;
	int k, j = 0;
	int i = (first - 1);
	int tmp;
	for (int a = first; i <= last - 1; i++) {
		if (arr[a] < pivot)
			pivot = arr[a];
	}


	int firstF = first;
	int lastL = last;

	while (firstF < lastL)
	{
		while (arr[firstF] < pivot)
			firstF++;
		while (arr[lastL] > pivot)
			lastL--;

		if (firstF <= lastL)
		{
			int tmp = arr[firstF];
			arr[firstF] = arr[lastL];
			arr[lastL] = tmp;
			firstF++;
			lastL--;
		}
	}

	if (first < lastL)
		quickSortWorst(arr, first, lastL);
	if (last > firstF)
		quickSortWorst(arr, firstF, last);

	return 0;
}

void counting_sort(std::vector<int> &arr, int n) {

	int high = *max_element(arr.begin(), arr.end());
	int low = *min_element(arr.begin(), arr.end());
	int range = high - low + 1;
	std::vector<int> count(range), output(arr.size());

	for (int i = 0; i < n; i++)
		count[arr[i] - low]++;

	for (int i = 1; i < count.size(); i++)
		count[i] += count[i - 1];

	for (int i = n - 1; i >= 0; i--)
	{
		output[count[arr[i] - low] - 1] = arr[i];
		count[arr[i] - low]--;
	}

	for (int i = 0; i < n; i++)
		arr[i] = output[i];

}

void mergealg(std::vector<int> &arr, int left, int mid, int right)
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::vector<int> A(n1);
	std::vector<int> B(n2);

	//copy elements to temporary arrays 
	for (i = 0; i < n1; i++)
		A[i] = arr[left + i];
	for (i = 0; i < n2; i++)
		B[i] = arr[mid + 1 + i];

	i = 0;
	j = 0;
	k = left;
	//sort two parts and merge it 
	while (i < n1 && j < n2)
	{
		if (A[i] <= B[j])
		{
			arr[k] = A[i];
			i++;
		}
		else
		{
			arr[k] = B[j];
			j++;
		}
		k++;
	}
	//if there are elements in L 
	while (i < n1)
	{
		arr[k] = A[i];
		i++;
		k++;
	}
	//if there are elements in R 
	while (j < n2)
	{
		arr[k] = B[j];
		j++;
		k++;
	}
}

void mergeSort(std::vector<int> &arr, int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;

		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);

		mergealg(arr, left, mid, right);
	}
}



int main()
{
	int N = 100;
	std::vector<int> myvector(N);

	for (int i = 0; i < N; i++)
	{
		myvector[i] = rand() % 100;
	}

	std::vector<int> myvectorcopy(myvector);

	std::cout << "Source Array:" << std::endl;
	print(myvector, N);

	selectionSort(myvector, N);
	std::cout << ("\n\n1) SELECTION SORT: ");
	print(myvector, N);

	myvector = myvectorcopy;


	bucketSort(myvector, N);
	printf("\n\n3) BUCKET SORT: ");
	print(myvector, N);


	myvector = myvectorcopy;


	quickSortRandom(myvector, 0, N - 1);
	printf("\n\n4) QUICK SORT RANDOM: ");
	print(myvector, N);

	myvector = myvectorcopy;


	quickSortWorst(myvector, 0, N - 1);
	printf("\n\n5) QUICK SORT WORST: ");
	print(myvector, N);

	myvector = myvectorcopy;

	counting_sort(myvector, N);
	printf("\n\n5) COUNTING SORT: ");
	print(myvector, N);

	myvector = myvectorcopy;

	mergeSort(myvector, 0, N - 1);
	printf("\n\n5) MERGE SORT: ");
	print(myvector, N);

	_getch();
	return 0;
}

