#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;

void min_reduction(vector<int>& arr) {
    int min_value = INT_MAX;
    #pragma omp parallel for reduction(min: min_value)
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    cout << "Minimum value: " << min_value << endl;
}

void max_reduction(vector<int>& arr) {
    int max_value = INT_MIN;
    #pragma omp parallel for reduction(max: max_value)
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(vector<int>& arr) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}

void average_reduction(vector<int>& arr) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    cout << "Average: " << (double)sum / arr.size() << endl;
}

int main() {
    int n, x;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr;
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        arr.push_back(x);
    }

    min_reduction(arr);
    max_reduction(arr);
    sum_reduction(arr);
    average_reduction(arr);

    return 0;
}

/* 
✅ Step-by-step MSYS2 Installation for OpenMP Support:
🔽 1. Download MSYS2 Installer
Go to the official website:
👉 https://www.msys2.org

Download the installer for 64-bit Windows (msys2-x86_64-*.exe).

💻 2. Run the Installer
Install it to the default location (e.g., C:\msys64).

Do not install it in a folder with spaces like C:\Program Files.

⚙️ 3. Open MSYS2 Terminal
After installation, open:

🔹 "MSYS2 MinGW 64-bit" from your Start menu.
(This is the one you will use to compile C++ with OpenMP.)

🔁 4. Update the Package Manager
In the terminal, run:

bash
Copy
Edit
pacman -Syu
If prompted, close the terminal and open it again, then run:

bash
Copy
Edit
pacman -Su
📦 5. Install GCC with OpenMP Support
bash
Copy
Edit
pacman -S mingw-w64-x86_64-gcc
This installs the 64-bit version of GCC (with OpenMP).

🛠️ 6. Compile Your Program
Navigate to your source code location:

bash
Copy
Edit
cd /c/Users/YourUsername/Downloads
Then compile:

bash
Copy
Edit
g++ -fopenmp parallel_reduction.cpp -o parallel_reduction.exe
And run:

bash
Copy
Edit
./parallel_reduction.exe


For Ubuntu: 

✅ Steps to Compile and Run OpenMP Programs in Ubuntu:
Open Terminal (Ctrl+Alt+T)

Install g++ with OpenMP support:

bash
Copy
Edit
sudo apt update
sudo apt install g++ libomp-dev
Navigate to your code directory:

bash
Copy
Edit
cd ~/Downloads   # or the directory where your `.cpp` file is
Compile your OpenMP code:

bash
Copy
Edit
g++ -fopenmp parallel_reduction.cpp -o parallel_reduction
Run the program:

bash
Copy
Edit
./parallel_reduction

*/
