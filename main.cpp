#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>

using namespace std;

void printStack(stack<int> s, int maxDisks) {
    vector<int> elements;
    while (!s.empty()) {
        elements.push_back(s.top());
        s.pop();
    }
    for (int i = elements.size(); i < maxDisks; ++i) {
        cout << setw(maxDisks) << "" << "|" << setw(maxDisks) << "" << endl;
    }
    for (int i = 0; i < elements.size(); ++i) {
        int spaces = maxDisks - elements[i];
        cout << setw(spaces) << "" << "<";
        for (int j = 0; j < elements[i] * 2 - 1; ++j) {
            cout << "o";
        }
        cout << ">" << setw(spaces) << "" << endl;
    }
}

void printTowers(stack<int> towers[], int numTowers, int maxDisks) {
    cout << "Current Towers:\n";
    for (int i = 0; i < numTowers; ++i) {
        cout << "Tower " << i + 1 << ":\n";
        printStack(towers[i], maxDisks);
    }
    cout << endl;
}

bool moveDisk(stack<int>& from, stack<int>& to) {
    if (from.empty()) {
        cout << "Invalid move: Source tower is empty!\n";
        return false;
    } else if (!to.empty() && from.top() > to.top()) {
        cout << "Invalid move: Cannot place larger disk on smaller disk!\n";
        return false;
    } else {
        to.push(from.top());
        from.pop();
        return true;
    }
}

bool checkWin(stack<int> towers[], int numDisks, int targetTower) {
    return (towers[targetTower - 1].size() == numDisks);
}

int main() {
    int numDisks;
    cout << "Enter the number of disks: ";
    cin >> numDisks;

    stack<int> towers[3];  // Three towers (stacks)

    // Initialize the first tower with disks (largest to smallest)
    for (int i = numDisks; i >= 1; --i) {
        towers[0].push(i);
    }

    int source, destination;
    int moveCount = 0;
    while (true) {
        printTowers(towers, 3, numDisks);
        
        cout << "Enter move (e.g., 1 3 to move from Tower 1 to Tower 3): ";
        cin >> source >> destination;

        if (source < 1 || source > 3 || destination < 1 || destination > 3) {
            cout << "Invalid input! Towers are numbered 1 to 3.\n";
            continue;
        }

        if (moveDisk(towers[source - 1], towers[destination - 1])) {
            moveCount++;
            if (checkWin(towers, numDisks, 3)) {
                printTowers(towers, 3, numDisks);
                cout << "Congratulations! You solved the Tower of Hanoi puzzle in " << moveCount << " moves!\n";
                break;
            }
        }
    }
    return 0;
}