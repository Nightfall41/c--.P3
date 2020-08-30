#include <iostream>
#include "matrix.h"
using namespace std;

/*
     guassian bro :D 
*/

int main()
{
    // vctr vctrRow(20.0, 2.0, 11.7);

    // vctr vctrColumn(4.0, 1.9, 22.4);

    Matrix test(2, 3, 2);



    cout << endl;
    Matrix test2(3, 2, 15);


    Matrix res = test * test2;

    res.print();

    cout << endl;

    // cout << "plus : " << (vctrRow + vctrColumn) << "\n";
    // cout << "min : " << (vctrRow - vctrColumn) << "\n";
    // cout << "multiply : " << (vctrRow * vctrColumn) << "\n";
    // cout << "multiply by 5 : " << (vctrColumn * 5.0) << "\n";
    // cout << "scaler product:" << (vctrColumn * vctrRow) << "\n";
    // cout << "cross vector " << (vctrColumn ^ vctrRow) << "\n"; 
    return 0;
}