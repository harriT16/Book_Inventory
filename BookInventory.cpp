#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp> 

using json = nlohmann::json;

class Book {
public:
    std::string title;
    std::string author;
    int count;

    Book(std::string t, std::string a, int c) : title(t), author(a), count(c) {}
};

void displayBooks(const std::vector<Book>& books) {
    std::cout << "Inventory:\n";
    for (const auto& book : books) {
        std::cout << "Title: " << book.title << ", Author: " << book.author << ", Count: " << book.count << '\n';
    }
}

int main() {
    std::vector<Book> inventory;

    // Load books from JSON file
    std::ifstream i("books.json");
    json j;
    i >> j;

    for (auto& book : j) {
        inventory.push_back(Book(book["title"], book["author"], book["count"]));
    }

    while (true) {
        std::cout << "1. Display Books\n2. Add Book\n3. Buy Book\n4. Exit\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            displayBooks(inventory);
        } else if (choice == 2) {
            std::string title, author;
            int count;
            std::cout << "Enter book title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Enter book author: ";
            std::getline(std::cin, author);
            std::cout << "Enter book count: ";
            std::cin >> count;

            inventory.push_back(Book(title, author, count));
        } else if (choice == 3) {
            std::string title;
            std::cout << "Enter the title of the book you want to buy: ";
            std::cin.ignore();
            std::getline(std::cin, title);

            for (auto& book : inventory) {
                if (book.title == title) {
                    if (book.count > 0) {
                        book.count--;
                        std::cout << "Book purchased successfully!\n";
                    } else {
                        std::cout << "Sorry, the book is out of stock.\n";
                    }
                    break;
                }
            }
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
