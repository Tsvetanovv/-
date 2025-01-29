
#include <iostream>
#include <fstream>

const int MAX_ORDERS = 100;
const int MAX_PROBLEMS = 10;
const int MAX_REPAIRS = 10;

struct Order {
    int orderNumber;
    int day;
    std::string client;
    std::string deviceType;
    std::string serialNumber;
    std::string clientProblem;
    std::string technicianName;
    std::string repairDescription;
    double price;
    int daysInService;
    std::string status;
};

// Lists of predefined problems and repairs
std::string problems[MAX_PROBLEMS] = {"Screen issue", "Battery problem", "Software error", "Hardware failure", "Other"};
std::string repairs[MAX_REPAIRS] = {"Replace component", "Software fix", "Hardware repair", "Cleaning", "Other"};

// Function prototypes
void displayMenu();
void addOrder(Order orders[], int& orderCount);
void displayAllOrders(const Order orders[], int orderCount);
void searchByDeviceType(const Order orders[], int orderCount);
void searchByStatus(const Order orders[], int orderCount);
void sortByDate(Order orders[], int orderCount);
void saveToFile(const Order orders[], int orderCount);
void loadFromFile(Order orders[], int& orderCount);
void separateAndSortByTechnician(const Order orders[], int orderCount);
void separateAndSortByProblem(const Order orders[], int orderCount);
void updateOrder(Order orders[], int orderCount);
void changeOrderStatus(Order orders[], int orderCount);

int main() {
    Order orders[MAX_ORDERS];
    int orderCount = 0;

    // Load data from file on startup
    loadFromFile(orders, orderCount);

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addOrder(orders, orderCount);
                break;
            case 2:
                displayAllOrders(orders, orderCount);
                break;
            case 3:
                searchByDeviceType(orders, orderCount);
                break;
            case 4:
                searchByStatus(orders, orderCount);
                break;
            case 5:
                sortByDate(orders, orderCount);
                break;
            case 6:
                saveToFile(orders, orderCount);
                break;
            case 7:
                separateAndSortByTechnician(orders, orderCount);
                break;
            case 8:
                separateAndSortByProblem(orders, orderCount);
                break;
            case 9:
                updateOrder(orders, orderCount);
                break;
            case 10:
                changeOrderStatus(orders, orderCount);
                break;
            case 0:
                std::cout << "Exiting program. Saving data to file...\n";
                // Save data to file before exiting
                saveToFile(orders, orderCount);
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

void displayMenu() {
    std::cout << "\n===== Service Center Information System Menu =====\n";
    std::cout << "1. Add new service order\n";
    std::cout << "2. Display all orders\n";
    std::cout << "3. Search by device type\n";
    std::cout << "4. Search by status\n";
    std::cout << "5. Sort by date\n";
    std::cout << "6. Save to file\n";
    std::cout << "7. Separate and sort by technician\n";
    std::cout << "8. Separate and sort by problem\n";
    std::cout << "9. Update order\n";
    std::cout << "10. Change order status\n";
    std::cout << "0. Exit\n";
}

void addOrder(Order orders[], int& orderCount) {
    if (orderCount < MAX_ORDERS) {
        std::cout << "Enter order details:\n";
        Order newOrder;
        // Get partial information from the user
        std::cout << "Order number: ";
        std::cin >> newOrder.orderNumber;
        std::cout << "Device type: ";
        std::cin >> newOrder.deviceType;
        std::cout << "Serial number: ";
        std::cin >> newOrder.serialNumber;
        // Add other fields as needed

        // Add the order to the array
        orders[orderCount++] = newOrder;

        std::cout << "Order added successfully!\n";
    } else {
        std::cout << "Maximum number of orders reached!\n";
    }
}

void displayAllOrders(const Order orders[], int orderCount) {
    std::cout << "\n===== All Service Orders =====\n";
    // Display orders in a formatted table
    // Modify this part based on your specific data structure and fields
    for (int i = 0; i < orderCount; ++i) {
        std::cout << "Order Number: " << orders[i].orderNumber << "\n";
        std::cout << "Device Type: " << orders[i].deviceType << "\n";
        // Add other fields as needed
        std::cout << "---------------------------\n";
    }
}

void searchByDeviceType(const Order orders[], int orderCount) {
    std::string targetDeviceType;
    std::cout << "Enter device type to search: ";
    std::cin >> targetDeviceType;

    std::cout << "\n===== Search Results =====\n";
    // Search and display orders with matching device type
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i].deviceType == targetDeviceType) {
            std::cout << "Order Number: " << orders[i].orderNumber << "\n";
            std::cout << "Device Type: " << orders[i].deviceType << "\n";
            // Add other fields as needed
            std::cout << "---------------------------\n";
        }
    }
}

void searchByStatus(const Order orders[], int orderCount) {
    std::string targetStatus;
    std::cout << "Enter status to search (accepted/rejected/completed): ";
    std::cin >> targetStatus;

    std::cout << "\n===== Search Results =====\n";
    // Search and display orders with matching status
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i].status == targetStatus) {
            std::cout << "Order Number: " << orders[i].orderNumber << "\n";
            std::cout << "Status: " << orders[i].status << "\n";
            // Add other fields as needed
            std::cout << "---------------------------\n";
        }
    }
}

void sortByDate(Order orders[], int orderCount) {
    // Bubble sort based on order date (day)
    for (int i = 0; i < orderCount - 1; ++i) {
        for (int j = 0; j < orderCount - i - 1; ++j) {
            if (orders[j].day > orders[j + 1].day) {
                // Swap orders
                Order temp = orders[j];
                orders[j] = orders[j + 1];
                orders[j + 1] = temp;
            }
        }
    }

    std::cout << "\n===== Orders Sorted by Date =====\n";
    // Display orders after sorting
    for (int i = 0; i < orderCount; ++i) {
        std::cout << "Order Number: " << orders[i].orderNumber << "\n";
        std::cout << "Day: " << orders[i].day << "\n";
        // Add other fields as needed
        std::cout << "---------------------------\n";
    }
}

void saveToFile(const Order orders[], int orderCount) {
    std::ofstream outFile("service_orders.txt");
    if (!outFile.is_open()) {
        std::cout << "Error opening file for writing.\n";
        return;
    }

    // Write orders to the file
    for (int i = 0; i < orderCount; ++i) {
        outFile << orders[i].orderNumber << " ";
        outFile << orders[i].day << " ";
        outFile << orders[i].client << " ";
        outFile << orders[i].deviceType << " ";
        outFile << orders[i].serialNumber << " ";
        outFile << orders[i].clientProblem << " ";
        outFile << orders[i].technicianName << " ";
        outFile << orders[i].repairDescription << " ";
        outFile << orders[i].price << " ";
        outFile << orders[i].daysInService << " ";
        outFile << orders[i].status << "\n";
        // Add other fields as needed
    }

    std::cout << "Data saved to file successfully.\n";
    outFile.close();
}

void loadFromFile(Order orders[], int& orderCount) {
    std::ifstream inFile("service_orders.txt");
    if (!inFile.is_open()) {
        std::cout << "File not found. Starting with an empty list.\n";
        return;
    }

    // Read orders from the file
    while (inFile >> orders[orderCount].orderNumber >> orders[orderCount].day >> orders[orderCount].client
           >> orders[orderCount].deviceType >> orders[orderCount].serialNumber >> orders[orderCount].clientProblem
           >> orders[orderCount].technicianName >> orders[orderCount].repairDescription >> orders[orderCount].price
           >> orders[orderCount].daysInService >> orders[orderCount].status) {
        orderCount++;
        if (orderCount >= MAX_ORDERS) {
            std::cout << "Maximum number of orders reached. Loading stopped.\n";
            break;
        }
    }

    std::cout << "Data loaded from file successfully.\n";
    inFile.close();
}

void separateAndSortByTechnician(const Order orders[], int orderCount) {
    // Display the results accordingly
    std::cout << "Separate and sort by technician functionality not implemented yet.\n";
}

void separateAndSortByProblem(const Order orders[], int orderCount) {
    // Display the results accordingly
    std::cout << "Separate and sort by problem functionality not implemented yet.\n";
}

void updateOrder(Order orders[], int orderCount) {
    int orderNumber;
    std::cout << "Enter order number to update: ";
    std::cin >> orderNumber;

    // Find the order with the given number
    int index = -1;
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i].orderNumber == orderNumber) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // Order found
        if (orders[index].status == "Accepted") {
            // Update repair information and calculate price
            std::cout << "Enter technician name: ";
            std::cin >> orders[index].technicianName;
            std::cout << "Enter repair description: ";
            std::cin >> orders[index].repairDescription;

            // Calculate price based on repair type
            // Add your logic here

            std::cout << "Order updated successfully!\n";
        } else {
            std::cout << "Order cannot be updated. It is already rejected/completed.\n";
        }
    } else {
        std::cout << "Order not found.\n";
    }
}

void changeOrderStatus(Order orders[], int orderCount) {
    int orderNumber;
    std::string newStatus;
    std::cout << "Enter order number: ";
    std::cin >> orderNumber;

    // Find the order with the given number
    int index = -1;
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i].orderNumber == orderNumber) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // Order found
        std::cout << "Enter new status (Accepted/Rejected/Completed): ";
        std::cin >> newStatus;

        if (orders[index].status == "Accepted") {
            // Status can be changed only if the order is still in the "Accepted" state
            orders[index].status = newStatus;
            std::cout << "Status updated successfully!\n";
        } else {
            std::cout << "Status cannot be changed. It is already rejected/completed.\n";
        }
    } else {
        std::cout << "Order not found.\n";
    }
}
