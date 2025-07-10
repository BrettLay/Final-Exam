// Full Name: Brett
// Class: ITCS 2530 – C++ Programming
// GitHub Repo URL: https://github.com/BrettLay/Final-Exam
// One-Sentence Summary: A program that generates a custom workout plan based on a user’s goal and activity level.
// Your posted hobby or interest: Fitness and resistance training
// AI Tool(s) Used: ChatGPT (GPT-4)

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Struct to store user input data
struct UserProfile {
    string name;
    string activityLevel;
    string goal;
    double milesRun;
    double resistanceHours;
};

// Class to manage and store the workout plan
class WorkoutPlan {
private:
    string plan[10]; // static array
    int size;

public:
    WorkoutPlan() {
        size = 0;
    }

    void generate(const UserProfile& user) {
        size = 0;
        // Customize the plan based on the user's goal
        if (user.goal == "Gain Muscle") {
            plan[size++] = "Day 1: Chest + Triceps (4 sets x 10 reps)";
            plan[size++] = "Day 2: Back + Biceps (4 sets x 10 reps)";
            plan[size++] = "Day 3: Legs (4 sets x 12 reps)";
            plan[size++] = "Day 4: Shoulders + Core (4 sets x 12 reps)";
            plan[size++] = "Day 5: Full-body circuit training";
        }
        else if (user.goal == "Lose Fat") {
            plan[size++] = "Day 1: HIIT Cardio + Core";
            plan[size++] = "Day 2: Upper Body Strength Training";
            plan[size++] = "Day 3: Low-Intensity Steady-State Cardio";
            plan[size++] = "Day 4: Lower Body Strength Training";
            plan[size++] = "Day 5: Full-body HIIT";
        }
        else if (user.goal == "Improve Endurance") {
            plan[size++] = "Day 1: Long-distance running (5+ miles)";
            plan[size++] = "Day 2: Cross-training (cycling or rowing)";
            plan[size++] = "Day 3: Interval running (800m sprints)";
            plan[size++] = "Day 4: Resistance training (light weights)";
            plan[size++] = "Day 5: Recovery jog or yoga";
        }
        else {
            plan[size++] = "Invalid fitness goal. No plan generated.";
        }

        // Optional bonus recommendations
        if (user.milesRun < 5) {
            plan[size++] = "Recommendation: Increase running volume gradually.";
        }
        if (user.resistanceHours < 2) {
            plan[size++] = "Recommendation: Add at least 2 hours of resistance training weekly.";
        }
    }

    void printToConsole() {
        cout << "\nYour 5-Day Workout Plan:\n";
        for (int i = 0; i < size; i++) {
            cout << "  - " << plan[i] << endl;
        }
    }

    void writeToFile(const string& name) {
        ofstream outFile("WorkoutSchedule.txt");
        if (!outFile) {
            cout << "Error: Could not create output file.\n";
            return;
        }

        outFile << "Workout Plan for " << name << ":\n\n";
        for (int i = 0; i < size; i++) {
            outFile << plan[i] << endl;
        }

        outFile.close();
        cout << "Workout plan saved to WorkoutSchedule.txt\n";
    }
};

// Function declarations
bool readUserFromFile(const string& fileName, UserProfile& user);
void displayMenu();
void pause();

int main() {
    UserProfile user;
    WorkoutPlan plan;
    string inputFile = "UserInfo.txt";
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline character

        switch (choice) {
        case 1:
            if (readUserFromFile(inputFile, user)) {
                cout << "\nData successfully loaded from file.\n";
            }
            else {
                cout << "Failed to load data from file.\n";
            }
            pause();
            break;
        case 2:
            plan.generate(user);
            plan.printToConsole();
            pause();
            break;
        case 3:
            plan.writeToFile(user.name);
            pause();
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            pause();
        }

    } while (choice != 4);

    return 0;
}

// Reads user info from file into UserProfile struct
bool readUserFromFile(const string& fileName, UserProfile& user) {
    ifstream inFile(fileName);

    if (!inFile) {
        cout << "Error: Could not open " << fileName << endl;
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

// Prints menu options
void displayMenu() {
    cout << "\n===== Workout Planner Menu =====\n";
    cout << "1. Load user data from file\n";
    cout << "2. Generate and display workout plan\n";
    cout << "3. Save workout plan to file\n";
    cout << "4. Exit\n";
    cout << "================================\n";
}

// Pauses program until user hits Enter
void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
}
