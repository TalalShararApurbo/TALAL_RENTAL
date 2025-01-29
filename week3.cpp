#include <bits/stdc++.h>
using namespace std;

struct Car {
    string model;
    string brand;
    double costPerDay;
    bool isAvailable;
    Car* next;
};

Car* head = NULL;

Car* createCar(const string& model, const string& brand, double cost) {
    Car* car = new Car();
    car->model = model;
    car->brand = brand;
    car->costPerDay = cost;
    car->isAvailable = true;
    car->next = NULL;
    return car;
}

void saveCars() {
    ofstream file("cars.data", ios::trunc);
    Car* temp = head;
    while (temp != NULL) {
        file << temp->brand << " " << temp->model << " " << temp->costPerDay << " " << temp->isAvailable << "\n";
        temp = temp->next;
    }
    file.close();
}

void loadCars() {
    ifstream file("cars.data");
    if (!file) return;
    string brand, model;
    double cost;
    bool isAvailable;
    while (file >> brand >> model >> cost >> isAvailable) {
        Car* car = createCar(model, brand, cost);
        car->isAvailable = isAvailable;
        if (head == NULL) {
            head = car;
        } else {
            Car* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = car;
        }
    }
    file.close();
}

void addCar(const string& model, const string& brand, double cost) {
    Car* car = createCar(model, brand, cost);
    if (head == NULL) {
        head = car;
    } else {
        Car* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = car;
    }
    saveCars();
    cout << "A new car has been added.\n";
}

void removeCar(size_t index) {
    if (head == NULL) return;
    Car* temp = head;
    if (index == 0) {
        head = head->next;
        delete temp;
    } else {
        Car* prev = NULL;
        for (size_t i = 0; i < index && temp != NULL; i++) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != NULL) {
            prev->next = temp->next;
            delete temp;
        }
    }
    saveCars();
    cout << "A car has been removed.\n";
}

void displayCars() {
    if (head == NULL) {
        cout << "No cars available in the system.\n";
        return;
    }
    Car* temp = head;
    int count = 1;
    cout << "\n~~~~~AVAILABLE CARS~~~~~\n";
    while (temp != NULL) {
        cout << count << ". " << temp->brand << " " << temp->model 
             << " - $" << temp->costPerDay << " per day"
             << (temp->isAvailable ? "" : " (Not Available)") << "\n";
        temp = temp->next;
        count++;
    }
}

void searchCar(const string& query) {
    Car* temp = head;
    bool found = false;
    int count = 1;
    while (temp != NULL) {
        if (temp->model == query || temp->brand == query) {
            cout << count << ". " << temp->brand << " " << temp->model 
                 << " - $" << temp->costPerDay << " per day"
                 << (temp->isAvailable ? "" : " (Not Available)") << "\n";
            found = true;
            count++;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "Car not found.\n";
    }
}

class RentalSystem {
private:
    map<string, string> users;

    void loadUsers() {
        ifstream file("users.data");
        if (!file) return;
        string username, password;
        while (file >> username >> password) {
            users[username] = password;
        }
        file.close();
    }

    void saveUser(const string& username, const string& password) {
        ofstream file("users.data", ios::app);
        file << username << " " << password << "\n";
        file.close();
    }

public:
    RentalSystem() {
        loadCars();
        loadUsers();
    }

    bool loginUser(const string& username, const string& password) {
        if (username == "apurbo" && password == "admin123") {
            return true;
        }
        return users.find(username) != users.end() && users[username] == password;
    }

    void registerUser(const string& username, const string& password) {
        if (users.find(username) == users.end()) {
            users[username] = password;
            saveUser(username, password);
            cout << "Registration successful!\n";
        } else {
            cout << "Username already exists!\n";
        }
    }

    void adminMenu() {
        while (true) {
            system("cls");
            cout << "\n-_-_-_TALAL RENTAL ADMIN MENU_-_-_-\n";
            cout << "1. Add New Car\n";
            cout << "2. Remove Car\n";
            cout << "3. View All Cars\n";
            cout << "4. Search Car\n";
            cout << "5. Logout\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            cin.ignore();
            switch (choice) {
                case 1: {
                    string model, brand;
                    double cost;
                    cout << "Enter car brand: ";
                    getline(cin, brand);
                    cout << "Enter car model: ";
                    getline(cin, model);
                    cout << "Enter cost per day: $";
                    cin >> cost;
                    addCar(model, brand, cost);
                    break;
                }
                case 2: {
                    displayCars();
                    if (head != NULL) {
                        cout << "\nEnter the number of the car to remove: ";
                        size_t index;
                        cin >> index;
                        removeCar(index - 1);
                    }
                    break;
                }
                case 3:
                    displayCars();
                    break;
                case 4: {
                    string query;
                    cout << "Enter car brand or model to search: ";
                    getline(cin, query);
                    searchCar(query);
                    break;
                }
                case 5:
                    return;
                default:
                    cout << "Invalid choice!\n";
            }
            cout << "Press Enter to continue...";
            cin.ignore();
        }
    }

    void customerMenu() {
        while (true) {
            system("cls");
            cout << "\n`````RENT A CAR`````\n";
            cout << "1. View Available Cars\n";
            cout << "2. Search Car\n";
            cout << "3. Logout\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            cin.ignore();
            switch (choice) {
                case 1:
                    displayCars();
                    break;
                case 2: {
                    string query;
                    cout << "Enter car brand or model to search: ";
                    getline(cin, query);
                    searchCar(query);
                    break;
                }
                case 3:
                    return;
                default:
                    cout << "Invalid choice!\n";
            }
            cout << "Press Enter to continue...";
            cin.ignore();
        }
    }
};

int main() {
    system("color 03");
    RentalSystem rentalSystem;
    string username, password;
    while (true) {
        system("cls");
        cout << "\n_________________________________       ______________________   _____________________ ";
        cout << "\n___  __/__    |__  /___    |__  /       ___  __ |__  ____/__  | / /__  __/__    |__  / ";
        cout << "\n__  /  __  /| |_  / __  /| |_  /        __  /_/ /_  __/  __   |/ /__  /  __  /| |_  /  ";
        cout << "\n_  /   _  ___ |  /___  ___ |  /___      _  _, _/_  /___  _  /|  / _  /   _  ___ |  /___";
        cout << "\n/_/    /_/  |_/_____/_/  |_/_____/      /_/ |_| /_____/  /_/ |_/  /_/    /_/  |_/_____/\n";
        cout << "\n                         FASTEST CAR RENTAL SERVICE IN THE WORLD\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                if (rentalSystem.loginUser(username, password)) {
                    if (username == "apurbo") {
                        rentalSystem.adminMenu();
                    } else {
                        rentalSystem.customerMenu();
                    }
                } else {
                    cout << "Invalid credentials!\n";
                }
                break;
            }
            case 2: {
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                rentalSystem.registerUser(username, password);
                break;
            }
            case 3:
                cout << "Thank you for using TALAL RENTAL!\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
        cout << "Press Enter to continue...";
        cin.ignore();
    }
    return 0;
}
