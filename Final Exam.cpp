#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

// Struct to hold user data
struct UserProfile {
    string name;
    string activityLevel;
    string goal;
    double milesRun;
    double resistanceHours;
};

// Class to manage workout plan
class WorkoutPlan {
private:
    string plan[10];
    int size;

public:
    WorkoutPlan() { size = 0; }

    void generate(const UserProfile& user) {
        size = 0;
        string goal = user.goal;
        for (char& c : goal) c = tolower(c); // make lowercase for comparison

        if (goal == "gain muscle") {
            plan[size++] = "Day 1: Chest + Triceps (4x10)";
            plan[size++] = "Day 2: Back + Biceps (4x10)";
            plan[size++] = "Day 3: Legs (4x12)";
            plan[size++] = "Day 4: Shoulders + Core (4x12)";
            plan[size++] = "Day 5: Full-body circuit";
        }
        else if (goal == "lose fat") {
            plan[size++] = "Day 1: HIIT + Core";
            plan[size++] = "Day 2: Upper Body Strength";
            plan[size++] = "Day 3: LISS Cardio";
            plan[size++] = "Day 4: Lower Body Strength";
            plan[size++] = "Day 5: Full-body HIIT";
        }
        else if (goal == "improve endurance") {
            plan[size++] = "Day 1: Long run";
            plan[size++] = "Day 2: Cross-training";
            plan[size++] = "Day 3: Interval sprints";
            plan[size++] = "Day 4: Light resistance training";
            plan[size++] = "Day 5: Recovery jog";
        }
        else {
            plan[size++] = "Unknown goal. No plan generated.";
        }

        if (user.milesRun < 5)
            plan[size++] = "Tip: Try to increase running distance weekly.";

        if (user.resistanceHours < 2)
            plan[size++] = "Tip: Add more resistance training to build strength.";
    }

    void printToConsole() {
        cout << "\n--- Your Workout Plan ---\n";
        for (int i = 0; i < size; ++i)
            cout << " - " << plan[i] << endl;
    }

    void writeToFile(const string& userName) {
        ofstream outFile("WorkoutSchedule.txt");
        if (!outFile) {
            cout << "Error writing file.\n";
            return;
        }
        outFile << "Workout Plan for " << userName << ":\n\n";
        for (int i = 0; i < size; ++i)
            outFile << plan[i] << endl;
        outFile.close();
        cout << "\nPlan saved to WorkoutSchedule.txt\n";
    }
};

// Reads user info from file
bool readUserFromFile(const string& fileName, UserProfile& user) {
    ifstream inFile(fileName);
    if (!inFile) {
        cout << "Error: Cannot open file.\n";
        return false;
    }

    getline(inFile, user.name);
    getline(inFile, user.activityLevel);
    getline(inFile, user.goal);
    inFile >> user.milesRun;
    inFile >> user.resistanceHours;

    inFile.close();
    return true;
}

// Menu
void showMenu() {
    cout << "\n--- Workout Planner Menu ---\n";
    cout << "1. Load user data\n";
    cout << "2. Generate and show workout\n";
    cout << "3. Save workout to file\n";
    cout << "4. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    UserProfile user;
    WorkoutPlan plan;
    int choice;
    string fileName = "UserInfo.txt";
    bool dataLoaded = false;

    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // flush newline

        switch (choice) {
        case 1:
            if (readUserFromFile(fileName, user)) {
                cout << "\nUser data loaded.\n";
                dataLoaded = true;
            }
            else {
                cout << "Failed to load data.\n";
            }
            break;
        case 2:
            if (dataLoaded) {
                plan.generate(user);
                plan.printToConsole();
            }
            else {
                cout << "Please load user data first.\n";
            }
            break;
        case 3:
            if (dataLoaded) {
                plan.writeToFile(user.name);
            }
            else {
                cout << "Please load user data first.\n";
            }
            break;
        case 4:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
        }

    } while (true);

    return 0;
}
