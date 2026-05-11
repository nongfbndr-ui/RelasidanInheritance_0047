#include <iostream>
#include <vector>
using namespace std;

class user {
protected:
    static int globalId;
    int id;
    string nama;
    string email;

public:
    user(string pNama, string pEmail) : nama(pNama), email(pEmail) {
        id = generateId();
    }

    static int generateId() {
        return ++globalId;
    }

    int getId() { return id; }
    string getNama() { return nama; }
    string getEmail() { return email; }
};

int user::globalId = 0;


class member : public user {
private:
    bool status; 

public:
    member(string nama, string email)
        : user(nama, email), status(true) {}

    void setStatus(bool s) {
        status = s;
    }

    bool getStatus() {
        return status;
    }

    void showProfile() {
        cout << "ID     : " << id << endl;
        cout << "Nama   : " << nama << endl;
        cout << "Email  : " << email << endl;
        cout << "Status : " << (status ? "Aktif" : "Nonaktif") << endl;
        cout << "------------------------\n";
    }
};


class admin : public user {
public:
    admin(string nama, string email) : user(nama, email) {}

    void showAllMember(vector<member*> &listMember) {
        for (auto m : listMember) {
            m->showProfile();
        }
    }

    void toggleActivationMember(member* m) {
        m->setStatus(!m->getStatus());
    }
};


int main() {
    vector<member*> daftarMember;

    member* m1 = new member("Andi", "andi@mail.com");
    member* m2 = new member("Budi", "budi@mail.com");

    daftarMember.push_back(m1);
    daftarMember.push_back(m2);

    admin* admin1 = new admin("Admin", "admin@mail.com");

    cout << "=== Semua Member ===\n";
    admin1->showAllMember(daftarMember);

    cout << "\n=== Toggle Status Member Andi ===\n";
    admin1->toggleActivationMember(m1);

    cout << "\n=== Setelah Diubah ===\n";
    admin1->showAllMember(daftarMember);

    delete m1;
    delete m2;
    delete admin1;

    return 0;
}