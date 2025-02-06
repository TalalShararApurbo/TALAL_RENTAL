#include <bits/stdc++.h>
using namespace std;

struct Car {
    string model;
    string brand;
    double costPerDay;
    bool isAvailable;
};

vector<Car> cars;
vector<Car> rentedCars;

Car createCar(const string& model, const string& brand, double cost) {
    Car car;
    car.model = model;
    car.brand = brand;
    car.costPerDay = cost;
    car.isAvailable = true;
    return car;
}

void saveCars() {
    ofstream file("cars.data", ios::trunc);
    if (!file) {
        cerr << "Error: Unable to open cars.data for writing.\n";
        return;
    }
    for (const auto& car : cars) {
        file << car.brand << " " << car.model << " " << car.costPerDay << " " << car.isAvailable << "\n";
    }
    file.close();
}

void loadCars() {
    ifstream file("cars.data");
    if (!file) {
        cerr << "Error: Unable to open cars.data for reading.\n";
        return;
    }
    string brand, model;
    double cost;
    bool isAvailable;
    while (file >> brand >> model >> cost >> isAvailable) {
        Car car = createCar(model, brand, cost);
        car.isAvailable = isAvailable;
        cars.push_back(car);
    }
    file.close();
}

void saveRentedCars() {
    ofstream file("rented_cars.data", ios::trunc);
    if (!file) {
        cerr << "Error: Unable to open rented_cars.data for writing.\n";
        return;
    }
    for (const auto& car : rentedCars) {
        file << car.brand << " " << car.model << " " << car.costPerDay << " " << car.isAvailable << "\n";
    }
    file.close();
}

void loadRentedCars() {
    ifstream file("rented_cars.data");
    if (!file) {
        cerr << "Error: Unable to open rented_cars.data for reading.\n";
        return;
    }
    string brand, model;
    double cost;
    bool isAvailable;
    while (file >> brand >> model >> cost >> isAvailable) {
        Car car = createCar(model, brand, cost);
        car.isAvailable = isAvailable;
        rentedCars.push_back(car);
    }
    file.close();
}

void addCar(const string& model, const string& brand, double cost) {
    try {
        Car car = createCar(model, brand, cost);
        cars.push_back(car);
        saveCars();
        cout << "A new car has been added.\n";
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
}

void removeCar(size_t index) {
    try {
        if (index < cars.size()) {
            cars.erase(cars.begin() + index);
            saveCars();
            cout << "A car has been removed.\n";
        } else {
            cerr << "Error: Invalid car index.\n";
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
}

void displayCars() {
    if (cars.empty()) {
        cout << "No cars available in the system.\n";
        return;
    }
    cout << "\n~~~~~AVAILABLE CARS~~~~~\n";
    for (size_t i = 0; i < cars.size(); ++i) {
        cout << i + 1 << ". " << cars[i].brand << " " << cars[i].model 
             << " - $" << cars[i].costPerDay << " per day"
             << (cars[i].isAvailable ? "" : " (Not Available)") << "\n";
    }
}

void displayRentedCars() {
    if (rentedCars.empty()) {
        cout << "No cars rented.\n";
        return;
    }
    cout << "\n~~~~~RENTED CARS~~~~~\n";
    for (size_t i = 0; i < rentedCars.size(); ++i) {
        cout << i + 1 << ". " << rentedCars[i].brand << " " << rentedCars[i].model 
             << " - $" << rentedCars[i].costPerDay << " per day\n";
    }
}

void searchCar(const string& query) {
    bool found = false;
    cout << "\n~~~~~SEARCH RESULTS~~~~~\n";
    for (size_t i = 0; i < cars.size(); ++i) {
        if (cars[i].model == query || cars[i].brand == query) {
            cout << i + 1 << ". " << cars[i].brand << " " << cars[i].model 
                 << " - $" << cars[i].costPerDay << " per day"
                 << (cars[i].isAvailable ? "" : " (Not Available)") << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Car not found.\n";
    }
}

void rentCar(size_t index) {
    try {
        if (index < cars.size() && cars[index].isAvailable) {
            cars[index].isAvailable = false;
            rentedCars.push_back(cars[index]);
            saveCars();
            saveRentedCars();
            cout << "Car has been rented.\n";
        } else {
            cerr << "Error: Car is not available for rent.\n";
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
}

class RentalSystem {
private:
    map<string, string> users;

    void loadUsers() {
        ifstream file("users.data");
        if (!file) {
            cerr << "Error: Unable to open users.data for reading.\n";
            return;
        }
        string username, password;
        while (file >> username >> password) {
            users[username] = password;
        }
        file.close();
    }

    void saveUser(const string& username, const string& password) {
        ofstream file("users.data", ios::app);
        if (!file) {
            cerr << "Error: Unable to open users.data for writing.\n";
            return;
        }
        file << username << " " << password << "\n";
        file.close();
    }

public:
    RentalSystem() {
        loadCars();
        loadRentedCars();
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
            cout << "4. View Rented Cars\n";
            cout << "5. Search Car\n";
            cout << "6. Logout\n";
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
                    if (!cars.empty()) {
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
                case 4:
                    displayRentedCars();
                    break;
                case 5: {
                    string query;
                    cout << "Enter car brand or model to search: ";
                    getline(cin, query);
                    searchCar(query);
                    break;
                }
                case 6:
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
                case 1: {
                    displayCars();
                    if (!cars.empty()) {
                        cout << "\nEnter the number of the car to rent: ";
                        size_t index;
                        cin >> index;
                        rentCar(index - 1);
                    }
                    break;
                }
                case 2: {
                    string query;
                    cout << "Enter car brand or model to search: ";
                    getline(cin, query);
                    searchCar(query);
                    if (!cars.empty()) {
                        cout << "\nEnter the number of the car to rent: ";
                        size_t index;
                        cin >> index;
                        rentCar(index - 1);
                    }
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
    system("color F3");
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
