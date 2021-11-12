#include "¿Œ»—_3.h"

int main()
{
    int choice;
    cout << "1) Tests :: 2) Own input : ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        tests();
        break;
    case 2:
        our_own_input();
        break;
    default: cout << "Enter something possible to work with!" << endl;
        break;
    }
    system("pause");
    return 0;
}