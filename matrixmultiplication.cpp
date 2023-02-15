#include <iostream>
using namespace std;

int main() {
    int m1, n1, m2, n2;
    cout << "Enter the number of rows and columns for matrix 1: ";
    cin >> m1 >> n1;

    cout << "Enter the number of rows and columns for matrix 2: ";
    cin >> m2 >> n2;

    if (n1 != m2) {
        cout << "The matrices cannot be multiplied!";
        return 0;
    }

    int mat1[m1][n1], mat2[m2][n2], result[m1][n2];

    cout << "Enter the elements of matrix 1: ";
    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n1; j++) {
            cin >> mat1[i][j];
        }
    }

    cout << "Enter the elements of matrix 2: ";
    for (int i = 0; i < m2; i++) {
        for (int j = 0; j < n2; j++) {
            cin >> mat2[i][j];
        }
    }

    // Perform matrix multiplication
    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    // Print the result
    cout << "The product of the matrices is:\n";
    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n2; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
