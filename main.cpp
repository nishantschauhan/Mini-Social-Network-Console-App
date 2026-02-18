#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// User structure
struct User {
    string username;
    string name;
};

// Message structure
struct Message {
    string sender;
    string receiver;
    string content;
};

// File paths
const string USERS_FILE = "users.txt";
const string MESSAGES_FILE = "messages.txt";

// Helper: Load users from file
vector<User> loadUsers() {
    vector<User> users;
    ifstream file(USERS_FILE);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        User u;
        getline(ss, u.username, ',');
        getline(ss, u.name, ',');
        users.push_back(u);
    }
    return users;
}

// Helper: Save users to file
void saveUsers(const vector<User>& users) {
    ofstream file(USERS_FILE);
    for (auto& u : users) {
        file << u.username << "," << u.name << "\n";
    }
}

// Helper: Load messages from file
vector<Message> loadMessages() {
    vector<Message> messages;
    ifstream file(MESSAGES_FILE);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Message m;
        getline(ss, m.sender, ',');
        getline(ss, m.receiver, ',');
        getline(ss, m.content, ',');
        messages.push_back(m);
    }
    return messages;
}

// Helper: Save messages to file
void saveMessages(const vector<Message>& messages) {
    ofstream file(MESSAGES_FILE);
    for (auto& m : messages) {
        file << m.sender << "," << m.receiver << "," << m.content << "\n";
    }
}

// Create a new user
void createUser() {
    User u;
    cout << "Enter username: ";
    cin >> u.username;
    cin.ignore();
    cout << "Enter full name: ";
    getline(cin, u.name);

    vector<User> users = loadUsers();
    for (auto& user : users) {
        if (user.username == u.username) {
            cout << "Username already exists!" << endl;
            return;
        }
    }
    users.push_back(u);
    saveUsers(users);
    cout << "User created successfully!" << endl;
}

// Send a message
void sendMessage() {
    string sender, receiver, content;
    cout << "Enter your username: ";
    cin >> sender;
    cin.ignore();

    vector<User> users = loadUsers();
    bool senderExists = false;
    for (auto& u : users) if (u.username == sender) senderExists = true;
    if (!senderExists) {
        cout << "Sender does not exist!" << endl;
        return;
    }

    cout << "Enter receiver username: ";
    cin >> receiver;
    cin.ignore();

    bool receiverExists = false;
    for (auto& u : users) if (u.username == receiver) receiverExists = true;
    if (!receiverExists) {
        cout << "Receiver does not exist!" << endl;
        return;
    }

    cout << "Enter message: ";
    getline(cin, content);

    Message m{sender, receiver, content};
    vector<Message> messages = loadMessages();
    messages.push_back(m);
    saveMessages(messages);
    cout << "Message sent!" << endl;
}

// View messages for a user
void viewMessages() {
    string username;
    cout << "Enter your username: ";
    cin >> username;
    cin.ignore();

    vector<Message> messages = loadMessages();
    bool found = false;
    cout << "========= Messages =========" << endl;
    for (auto& m : messages) {
        if (m.receiver == username) {
            cout << "From: " << m.sender << " -> " << m.content << endl;
            found = true;
        }
    }
    if (!found) cout << "No messages found." << endl;
}

// Display all users
void displayUsers() {
    vector<User> users = loadUsers();
    cout << "========= Users =========" << endl;
    for (auto& u : users) {
        cout << "Username: " << u.username << ", Name: " << u.name << endl;
    }
}

// Main menu
int main() {
    int choice;

    do {
        cout << "\n========= Mini Social Network =========" << endl;
        cout << "1. Create User" << endl;
        cout << "2. Display Users" << endl;
        cout << "3. Send Message" << endl;
        cout << "4. View Messages" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: createUser(); break;
            case 2: displayUsers(); break;
            case 3: sendMessage(); break;
            case 4: viewMessages(); break;
            case 5: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    return 0;
}
