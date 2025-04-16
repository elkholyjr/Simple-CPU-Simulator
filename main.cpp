#include <iostream>
#include "Simulator.h"

using namespace std;

int main() {
    Simulator sim;

    int choice;
    while (true) {
        cout << "1. Single Step\n";
        cout << "2. Clear\n";
        cout << "3. Load Data\n";
        cout << "4. Print\n";
        cout << "5. Run\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (sim.single_step()) {
                    sim.single_step();
                } else {
                    cout << "You have reached your limits. Your machine is done!\n";
                    return 0;
                }
                break;
            case 2:
                sim.clear();
                break;
            case 3:
                sim.read_instructions_from_file("instructions.txt");
                break;
            case 4:
                sim.print();
                break;
            case 5:
                sim.execute_program();
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
