#include <bits/stdc++.h>
using namespace std;
 // x this will be the table that  i will make it in all the code pls
const int x = 10;

// Division Method
// The division method involves dividing the key by a prime number and using the remainder as the hash value.
// h(k) = k mod m
// Division Method: 123 % 10 = 3
// this the key= 123
// and the % 10
int divisionMethod(int key) {
    return key % x;
}

// Multiplication Method
// In the multiplication method, a constant A (0 < A < 1) is used to multiply the key.
// The fractional part of the product is then multiplied by m to get the hash value.
// h(k) = floor(m * (k * A mod 1))
// i wil give you and example like key will be 123 and the constant a 0.5 and x = 10
// key * a = 123 * 0.618034   = 76.11422
// fractional part = 0.618034
//  0.618034 * 10 = 7.61142and it will be the seven  floor in the x
int multiplicationMethod(int key) {
    float A = 0.618034;// this a golden ratio
    return floor(x * fmod(key * A, 1));
}

// Mid-Square Method
// In the mid-square method, the key is squared, and the middle digits of the result are taken as the hash value.
// Steps:
// 1. Square the key.
// 2. Extract the middle digits of the squared value.
// first the the key 123 and will make for it square and we take the middle part of it
int midSquareMethod(int key) {
    int square = key * key;
    int mid = (square / 10) % 100;
    return mid % x;
}

// Folding Method
// The folding method involves dividing the key into equal parts, summing the parts, and then taking the modulo with respect to m.
// Steps:
// 1. Divide the key into parts.
// 2. Sum the parts.
// 3. Take the modulo m of the sum.
// First Iteration:
//key % 100 = 56 (last two digits).
 //sum = 0 + 56 = 56.
 //key /= 100 = 1234.
 //Second Iteration:
 //key % 100 = 34 (last two digits).
 //sum = 56 + 34 = 90.
 //key /= 100 = 12.
 //Third Iteration:
 //key % 100 = 12 (remaining digits).
 //sum = 90 + 12 = 102.
 //key /= 100 = 0 (loop ends).
 //Modulo Operation:
 //sum % x = 102 % 10 = 2.
int foldingMethod(int key) {
    int sum = 0;
    while (key > 0) {
        sum += key % 100;
        key /= 100;
    }
    return sum % x;
}

//chaining method
//   i will explain the code first we do and linked list to insert the key in the list this first
// and we make a the index in the hash table where the key should be stored by calculating key % x
//and pushback mean i will push the key in the list

void chainingInsert(list<int> table[], int key) {
    table[divisionMethod(key)].push_back(key);
}

// first for loop we iterate form 0 to x-1 and x is this of the hase table
// and the second for loop will make for (int key : table[i]) iterates through all the keys in the linked list at bucket i, and cout << key prints them.
// If a bucket is empty, the loop skips over it, and nothing is printed for that bucket except the bucket label
void displayChaining(list<int> table[]) {
    for (int i = 0; i < x; ++i) {
        cout << "Bucket " << i << ": ";
        for (int key : table[i]) cout << key << " ";
        cout << endl;
    }
}

// Open Addressing
// the explain of the code first we do a for form 0 to x ths size
// If the slot at index is not occupied: what is means is not occupied this means is false
//Place the key in that slot
//Mark the slot as occupied
//Exit the function
void openAddressingInsert(int table[], bool occupied[], int key) {
    for (int i = 0; i < x; ++i) {
        int index = (divisionMethod(key) + i) % x; // h(k, i) = (h'(k) + i) mod m
        if (!occupied[index]) {
            table[index] = key;
            occupied[index] = true;
            return;
        }
    }
    cout << "Hash table is full, cannot insert key: " << key << endl;
}

void displayOpenAddressing(int table[], bool occupied[]) {
    for (int i = 0; i < x; ++i) {
        cout << "Slot " << i << ": " << (occupied[i] ? to_string(table[i]) : "Empty") << endl;
    }
}
// Double Hashing Method
int secondaryHash(int key) {
    return 7 - (key % 7); // Secondary hash function, h2(k)
}

void doubleHashingInsert(int table[], bool occupied[], int key) {
    int h1 = divisionMethod(key); // Primary hash function, h1(k)
    int h2 = secondaryHash(key); // Secondary hash function, h2(k)
    for (int i = 0; i < x; ++i) {
        int index = (h1 + i * h2) % x; // h(k, i) = (h1(k) + i * h2(k)) mod m
        if (!occupied[index]) {
            table[index] = key;
            occupied[index] = true;
            return;
        }
    }
    cout << "Hash table is full, cannot insert key: " << key << endl;
}

void displayDoubleHashing(int table[], bool occupied[]) {
    for (int i = 0; i < x; ++i) {
        cout << "Slot " << i << ": " << (occupied[i] ? to_string(table[i]) : "Empty") << endl;
    }
}



int main() {
    // make a example for the Chaining method 12, 22, 15, 25
    int keys[] = {123, 456, 789, 101, 112};

    cout << "Hashing Techniques:\n";
    for (int key : keys) {
        cout << "Key: " << key
             << ", Division: " << divisionMethod(key)
             << ", Multiplication: " << multiplicationMethod(key)
             << ", Mid-Square: " << midSquareMethod(key)
             << ", Folding: " << foldingMethod(key) << endl;
    }
    cout << "\nCollision Resolution Techniques\n";
//Chaining Method
    cout << "\nChaining Method:\n";
    list<int> chainingTable[x];
    for (int key : keys) chainingInsert(chainingTable, key);
    displayChaining(chainingTable);

    //  Open Addressing
    cout << "\nOpen Addressing Method:\n";
    int openTable[x] = {0};
    bool openOccupied[x] = {false};
    for (int key : keys) openAddressingInsert(openTable, openOccupied, key);
    displayOpenAddressing(openTable, openOccupied);


      // Double Hashing
    cout << "\nDouble Hashing Method:\n";
    int doubleTable[x] = {0};
    bool doubleOccupied[x] = {false};
    for (int key : keys) doubleHashingInsert(doubleTable, doubleOccupied, key);
    displayDoubleHashing(doubleTable, doubleOccupied);


    return 0;
}

