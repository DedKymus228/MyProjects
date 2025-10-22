#include <iostream>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    const int SIZE = 10;
    int array[SIZE];

    for (int i = 0; i < SIZE; i++) {
        int newNumber;
        bool alreadyExists;

        do {
            newNumber = rand() % 10 + 1;
            alreadyExists = false;

            for (int j = 0; j < i; j++) {
                if (array[j] == newNumber) {

                    alreadyExists = true;
                    break;

                }
            }
        } while (alreadyExists);

        array[i] = newNumber;
    }

    int minNumber =110;
    for (int j = 0; j < SIZE; j++) {
        if (array[j] < minNumber) {
            minNumber = array[j];
        }
    }

    for (int i = 0; i < SIZE; i++)
        cout << array[i] << " ";
    cout << endl;
    cout <<"minNumber " << minNumber << endl;
    system("pause");
    return 0;
}