#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

int binarysearch(const vector<int> &arr, int target) {
  int start = 0;
  int end = arr.size() - 1;

  while (start <= end) {
    int mid = start + (end - start) / 2;

    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] > target) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }
  return -1;
}

int linersearch(const vector<int> &arr, int target) {
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] == target) {
      return i;
    }
  }
  return -1;
}

int main() {
  int size;
  cout << "Enter the size of the array: ";
  cin >> size;

  vector<int> arr(size);
  for (int i = 0; i < size; i++) {
    cout << "Enter element " << i + 1 << ": ";
    cin >> arr[i];
  }

  vector<int> sorted_arr = arr;
  sort(sorted_arr.begin(), sorted_arr.end());

  cout << "\nOriginal array: ";
  for (int x : arr) {
    cout << x << " ";
  }
  cout << "\nSorted array (for Binary Search): ";
  for (int x : sorted_arr) {
    cout << x << " ";
  }
  cout << "\n\n";

  while (true) {
    int choice;
    cout << "Choose a search algorithm:\n";
    cout << "1. Linear Search\n";
    cout << "2. Binary Search\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 3) {
      cout << "Exiting...\n";
      break;
    }

    int target;
    if (choice == 1 || choice == 2) {
      cout << "Enter the target element to search: ";
      cin >> target;
    }

    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    int result = -1;

    switch (choice) {
    case 1:
      start_time = high_resolution_clock::now();
      result = linersearch(arr, target);
      end_time = high_resolution_clock::now();
      break;
    case 2:
      start_time = high_resolution_clock::now();
      result = binarysearch(sorted_arr, target);
      end_time = high_resolution_clock::now();
      break;
    default:
      cout << "Invalid choice!\n\n";
      continue;
    }

    if (result != -1) {
      if (choice == 1) {
        cout << "Element found at index " << result << " in Original array.\n";
      } else {
        cout << "Element found at index " << result << " in Sorted array.\n";
      }
    } else {
      cout << "Element not found.\n";
    }

    auto duration = duration_cast<nanoseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " nanoseconds.\n\n";
    cout << "--------------------------------------------------\n";
  }

  return 0;
}