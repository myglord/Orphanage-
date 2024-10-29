#include <iostream>
#include <vector>
#include <string>
#include <limits>


class Child {
public:
    std::string name;
    int age;
    std::string gender;

    Child(const std::string& n, int a, const std::string& g) : name(n), age(a), gender(g) {}
    void display() const {
        std::cout << "Name: " << name << ", Age: " << age << ", Gender: " << gender << '\n';
    }
};


class Donation {
public:
    std::string donorName;
    double amount;

    Donation(const std::string& dn, double amt) : donorName(dn), amount(amt) {}
    void display() const {
        std::cout << "Donor: " << donorName << ", Amount: $" << amount << '\n';
    }
};


class Orphanage {
private:
    std::vector<Child> children;
    std::vector<Donation> donations;

    int getValidInt(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            if (std::cin.fail() || value < 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a positive integer.\n";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
    }

    double getValidDouble(const std::string& prompt) {
        double value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            if (std::cin.fail() || value <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a positive amount.\n";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
    }

public:
    void addChild() {
        std::string name, gender;
        int age;
        std::cout << "\n--- Add New Child ---\n";
        std::cout << "Enter child's name: ";
        std::getline(std::cin, name);
        age = getValidInt("Enter child's age: ");
        
        while (true) {
            std::cout << "Enter child's gender (M/F): ";
            std::getline(std::cin, gender);
            if (gender == "M" || gender == "F") break;
            std::cout << "Invalid input. Please enter 'M' for male or 'F' for female.\n";
        }

        children.emplace_back(name, age, gender);
        std::cout << "Child added successfully.\n";
    }

    void viewChildren() const {
        std::cout << "\n--- Children in the Orphanage ---\n";
        if (children.empty()) {
            std::cout << "No children registered yet.\n";
            return;
        }
        for (const auto& child : children) {
            child.display();
        }
    }

    void addDonation() {
        std::string donorName;
        double amount;
        std::cout << "\n--- Add New Donation ---\n";
        std::cout << "Enter donor's name: ";
        std::getline(std::cin, donorName);
        amount = getValidDouble("Enter donation amount: $");

        donations.emplace_back(donorName, amount);
        std::cout << "Donation recorded successfully.\n";
    }

    void generateReport() const {
        std::cout << "\n--- Orphanage Report ---\n";
        std::cout << "\nChildren:\n";
        viewChildren();

        std::cout << "\nDonations:\n";
        if (donations.empty()) {
            std::cout << "No donations recorded yet.\n";
        } else {
            for (const auto& donation : donations) {
                donation.display();
            }
        }
    }
};


int main() {
    Orphanage orphanage;
    int choice;

    do {
        std::cout << "\n=================================\n";
        std::cout << "      Orphanage Management       \n";
        std::cout << "=================================\n";
        std::cout << "1. Add Child\n";
        std::cout << "2. View Children\n";
        std::cout << "3. Add Donation\n";
        std::cout << "4. Generate Report\n";
        std::cout << "5. Exit\n";
        std::cout << "=================================\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        switch (choice) {
            case 1:
                orphanage.addChild();
                break;
            case 2:
                orphanage.viewChildren();
                break;
            case 3:
                orphanage.addDonation();
                break;
            case 4:
                orphanage.generateReport();
                break;
            case 5:
                std::cout << "Exiting system. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
