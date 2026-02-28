#include <algorithm>
#include <ctime>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct MinMax {
    int min;
    int max;
};

int steps = 0;

MinMax findMinMax(const vector<int>& arr, int low, int high, int level) {
    MinMax result{};

    if (low == high) {
        result.min = result.max = arr[low];
        cout << "step " << level << ": Min: " << result.min << " Max: " << result.max
             << '\n';
        return result;
    }

    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }
        cout << "step " << level << ": Min: " << result.min << " Max: " << result.max
             << '\n';
        return result;
    }

    int mid = low + (high - low) / 2;
    MinMax left = findMinMax(arr, low, mid, level + 1);
    MinMax right = findMinMax(arr, mid + 1, high, level + 1);

    result.min = min(left.min, right.min);
    result.max = max(left.max, right.max);

    cout << "step " << level << ": Min: " << result.min << " Max: " << result.max << '\n';
    return result;
}

void exponentialMinMaxDfs(const vector<int>& arr,
                          int index,
                          bool hasChosen,
                          int currentMin,
                          int currentMax,
                          MinMax& answer,
                          long long& calls) {
    calls++;

    if (index == static_cast<int>(arr.size())) {
        if (hasChosen) {
            answer.min = min(answer.min, currentMin);
            answer.max = max(answer.max, currentMax);
        }
        return;
    }

    exponentialMinMaxDfs(arr, index + 1, hasChosen, currentMin, currentMax, answer, calls);

    if (!hasChosen) {
        exponentialMinMaxDfs(arr, index + 1, true, arr[index], arr[index], answer, calls);
    } else {
        exponentialMinMaxDfs(
            arr,
            index + 1,
            true,
            min(currentMin, arr[index]),
            max(currentMax, arr[index]),
            answer,
            calls
        );
    }
}

MinMax exponentialMinMax(const vector<int>& arr, long long& calls) {
    MinMax answer{numeric_limits<int>::max(), numeric_limits<int>::min()};
    calls = 0;
    exponentialMinMaxDfs(arr, 0, false, 0, 0, answer, calls);
    return answer;
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low;

    for (int j = low; j < high; j++) {
        steps++;
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }

    swap(arr[i], arr[high]);
    return i;
}

int quickSelect(vector<int>& arr, int low, int high, int k) {
    if (low <= high) {
        int pi = partition(arr, low, high);
        if (pi == k) {
            return arr[pi];
        } else if (pi > k) {
            return quickSelect(arr, low, pi - 1, k);
        } else {
            return quickSelect(arr, pi + 1, high, k);
        }
    }
    return -1;
}

double findMedian(vector<int> arr) {
    int n = static_cast<int>(arr.size());
    if (n == 0) {
        return 0.0;
    }

    if (n % 2 == 1) {
        return quickSelect(arr, 0, n - 1, n / 2);
    }

    int val1 = quickSelect(arr, 0, n - 1, n / 2);
    int val2 = quickSelect(arr, 0, n - 1, n / 2 - 1);
    return (val1 + val2) / 2.0;
}

int main() {
    int m;
    cout << "Enter the number of elements: ";
    cin >> m;

    if (m <= 0) {
        cout << "Please enter a positive size.\n";
        return 0;
    }

    vector<int> arr(m);
    for (int i = 0; i < m; i++) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> arr[i];
    }

    int n = static_cast<int>(arr.size());

    clock_t start1 = clock();
    MinMax ans = findMinMax(arr, 0, n - 1, 0);
    clock_t end1 = clock();

    clock_t start2 = clock();
    double median = findMedian(arr);
    clock_t end2 = clock();

    bool ranExponential = false;
    MinMax exponentialAns{};
    long long exponentialCalls = 0;
    double time_exponential_ms = 0.0;

    if (n <= 20) {
        ranExponential = true;
        clock_t start3 = clock();
        exponentialAns = exponentialMinMax(arr, exponentialCalls);
        clock_t end3 = clock();
        time_exponential_ms = 1000.0 * static_cast<double>(end3 - start3) / CLOCKS_PER_SEC;
    }

    cout << "Final Min = " << ans.min << '\n';
    cout << "Final Max = " << ans.max << '\n';
    cout << "Median = " << median << '\n';
    cout << "Total comparison steps: " << steps << '\n';

    if (ranExponential) {
        cout << "Exponential Min = " << exponentialAns.min << '\n';
        cout << "Exponential Max = " << exponentialAns.max << '\n';
        cout << "Exponential recursion calls: " << exponentialCalls << '\n';
    } else {
        cout << "Exponential min-max skipped for n > 20 (too slow for O(2^n)).\n";
    }

    double time_min_max_ms = 1000.0 * static_cast<double>(end1 - start1) / CLOCKS_PER_SEC;
    double time_median_ms = 1000.0 * static_cast<double>(end2 - start2) / CLOCKS_PER_SEC;

    cout << "Execution Time (min-max): " << time_min_max_ms << " ms\n";
    cout << "Execution Time (median): " << time_median_ms << " ms\n";
    if (ranExponential) {
        cout << "Execution Time (exponential min-max): " << time_exponential_ms << " ms\n";
    }

    return 0;
}
