#include <iostream>
#include <time.h>

using namespace std;

int main() {
    srand(time(NULL));
    int a = (rand() % 101) - 1;
    int b = (rand() % 101) - 1;
    cout << a << " " << b << endl;
};