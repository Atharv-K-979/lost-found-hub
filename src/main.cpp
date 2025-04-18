//Starting code
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Item
{
private:
    string name;
    string description;
    string status;
    string owner;

public:
    Item(const string &name, const string &description, const string &status, const string &owner)
        : name(name), description(description), status(status), owner(owner) {}

    string getName() const { return name; }
    string getDescription() const { return description; }
    string getStatus() const { return status; }
    string getOwner() const { return owner; }
    void setStatus(const string &newStatus) { status = newStatus; }
};

class Hub
{
protected:
    vector<Item> items;

public:
    Hub()
    {
        items.push_back(Item("Phone", "near lipton", "lost", "Atharv"));
    }

    void listItems() const
    {
        if (items.empty())
        {
            cout << "\nNo items found." << endl;
            return;
        }
        cout << "\n=== List of Items ===" << endl;
        cout << left << setw(10) << "Name" << setw(30) << "Description" << setw(30) << "Status" << setw(8) << "Owner" << setw(20) << "Reported At" << endl;
        cout << string(100, '-') << endl;
        for (const auto &item : items)
        {
            cout << left << setw(20) << item.getName()
                 << setw(30) << item.getDescription()
                 << setw(20) << item.getStatus()
                 << setw(15) << item.getOwner()<< endl;
        }
    }
};

class User : public Hub//inheriting from Hub class
{
public:
    void reportLostItem(const string &name, const string &description, const string &owner)
    {
        items.push_back(Item(name, description, "lost", owner));
        cout << "\nLost item added" << endl;
    }

    void reportFoundItem(const string &name, const string &description, const string &owner)
    {
        items.push_back(Item(name, description, "found", owner));
        cout << "\nFound item added" << endl;
    }

    void searchItemByName(const string &name) const
    {
        for (const auto &item : items)
        {
            if (item.getName() == name)
            {
                cout << "\nItem found: " << item.getName() << " - " << item.getDescription() << " (" << item.getStatus() << ")" << endl;
                return;
            }
        }
        cout << "\nItem not found." << endl;
    }

    void claimItem(const string &name)
    {
        for (auto &item : items)
        {
            if (item.getName() == name && item.getStatus() == "found")
            {
                item.setStatus("claimed");
                cout << "\nItem claimed successfully." << endl;
                return;
            }
        }
        cout << "\nItem not available for claiming." << endl;
    }
};

class Admin : public Hub //inheriting from Hub class
{
public:
    void addUserItem(const Item &item) { items.push_back(item); }
    void deleteItem(const string &name)
    {
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            if (it->getName() == name)
            {
                items.erase(it);
                cout << "\nItem '" << name << "' has been removed." << endl;
                return;
            }
        }
        cout << "\nItem not found." << endl;
    }

    void verifyClaims()
    {
        cout << "\nVerifying claims..." << endl;
        for (const auto &item : items)
        {
            if (item.getStatus() == "claimed")
            {
                cout << "Claim verified: " << item.getName() << " - " << item.getOwner() << endl;
            }
        }
    }
};

// Main Function
int main()
{
    User user;
    Admin admin;
    int choice;

    while (true)
    {
        cout << "\n1. Report Lost Item";
        cout << "\n2. Report Found Item";
        cout << "\n3. List Items";
        cout << "\n4. Search Item by Name";
        cout << "\n5. Claim Item";
        cout << "\n6. Delete Item For Admin";
        cout << "\n7. Verify Claims For Admin";
        cout << "\n8. Exit";
        cout << "\nChoose an option: ";
        cin >> choice;

        if (choice == 8)
            break;

        string name, description, owner;
        switch (choice)
        {
        case 1:
            cout << "Enter item name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Enter description: ";
            getline(cin, description);
            cout << "Enter your name: ";
            getline(cin, owner);
            user.reportLostItem(name, description, owner);
            break;
        case 2:
            cout << "Enter item name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Enter description: ";
            getline(cin, description);
            cout << "Enter your name: ";
            getline(cin, owner);
            user.reportFoundItem(name, description, owner);
            break;
        case 3:
            user.listItems();
            break;
        case 4:
            cout << "Enter item name to search: ";
            cin >> ws;
            getline(cin, name);
            user.searchItemByName(name);
            break;
        case 5:
            cout << "Enter item name to claim: ";
            cin >> ws;
            getline(cin, name);
            user.claimItem(name);
            break;
        case 6:
            cout << "Enter item name to delete: ";
            cin >> ws;
            getline(cin, name);
            admin.deleteItem(name);
            break;
        case 7:
            admin.verifyClaims();
            break;
        default:
            cout << "Invalid choice. Try again.";
        }
    }
    return 0;
}
