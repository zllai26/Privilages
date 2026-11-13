#include <iostream>
#include <string>
#include <set>
#include <cstdlib>

using namespace std;


//I created 2 classes: User an Root. they both have different functions
class User {
protected:
    int type;
    char code;
    string password;
    set<string> commands = {"cd", "ls", "grep"};

public:
    // Constructor sets the default User password automatically
    User() {
        password = "ILdHV6Ejs7IKf3Cjgkia";
    }

    bool can(const string& cmd) const {
        return commands.count(cmd) > 0;
    }

    void setPasswd(const string& newValue) {
        password = newValue;
    }

    bool checkPasswd(const string& input) const {
        return password == input;
    }
};

class Root : public User {
private:
    set<string> excommands = {"rm", "touch", "shutdown"};

public:
    // Constructor sets the default Root password automatically
    Root() {
        password = "1wRqn5O0qzgY8zjHkKsWU3yqxdBa75aC";
    }

    bool can(const string& cmd) const {
        return commands.count(cmd) > 0 || excommands.count(cmd) > 0;
    }
};

int main() {
    User user1;
    Root root1;

    string userinput;
    string choose;
    string passwd;
    int x = 1;
    int y = 1;
    bool loggedIn = false;

    while (x == 1) {
        cout << "root or user? ";
        cin >> choose;

        if (choose != "root" && choose != "user") {
            cout << "The account you gave doesn't exist.\n";
        } else {
            x = 0;
        }
    }

    while (y <= 3) {
        cout << "Enter your password: ";
        cin >> passwd;

        bool valid = (choose == "root") ? root1.checkPasswd(passwd) : user1.checkPasswd(passwd);

        if (valid) {
            cout << "Login successful!\n";
            loggedIn = true;
            break;
        } else {
            cout << "Wrong password. Attempts left: " << (3 - y) << "\n";
            y++;
        }
    }
   if (!loggedIn) {
        cout << "Too many failed attempts. Exiting.\n";
        return 1;
    }

    cout << "Enter a command: ";
    cin >> userinput;

    bool commandcan = (choose == "root") ? root1.can(userinput) : user1.can(userinput);

    if (commandcan) {
        cout << "Command Accepted\n";
        system(userinput.c_str());
    } else {
        cout << "Command Not Accepted\n";
    }

    return 0;
}
