#include <iostream>
#include <string>
#include <assert.h>
#include <cstdlib>
#include "RBTree.h"
#include "DRT.h"
#include "PG5.h"
#include "Database.h"
#include "RBHelper.h"

using namespace std;

Database* Studs;

int main(int argc, char** argv) {

    Studs = new RBTree();
    while (ProcessCommand());
    delete Studs;
    return 0;
}

bool ProcessCommand() {

    string cmd;
    getline(cin, cmd);
    if (cmd == "EXIT") return false;
    if (cmd == "PRINT") Print();
    else if (cmd == "RPRINT") RPrint();
    else if (cmd.substr(0, 3) == "ADD") AddCommand(cmd);
    else if (cmd.substr(0, 6) == "REMOVE") RemoveCommand(cmd);
    else if (cmd.substr(0, 6) == "LOOKUP") LookupCommand(cmd);
    else if (cmd.substr(0, 4) == "EDIT") EditCommand(cmd);
    else cout << "Invalid Command!" << endl;
    return true;
}

void Print() {

    cout << "Printing list forwards:" << endl;
    DRT* T = Studs->search("");
    string k = T->getnext();
    while (k != "") {
        delete T;
        T = Studs->search(k);
        cout << "Name:  " << k << "\tGPA:  " << T->getdata() << endl;
        k = T->getnext();
    }
    delete T;
    cout << endl;
}

void RPrint() {

    cout << "Printing list backwards:" << endl;
    DRT* T = Studs->search("");
    string k = T->getprev();
    while (k != "") {
        delete T;
        T = Studs->search(k);
        cout << "Name:  " << k << "\tGPA:  " << T->getdata() << endl;
        k = T->getprev();
    }
    delete T;
    cout << endl;
}

void AddCommand(string cmd) {
    int q1, q2, q3;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    for (q3 = q2 + 1; cmd[q3] != ' '; q3++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    DRT* S = Studs->search(k);
    if (S->getdata() != "")
        cout << "This student already exists!" << endl;
    else {
        string d = cmd.substr(q3 + 1, cmd.length() - 1);
        DRT* N = Studs->modify(k, d);
        cout << k << " was added to the database." << endl;
        cout << "Previous Student: " << S->getprev() << endl;
        cout << "Next Student: " << S->getnext() << endl;

    }
}

void RemoveCommand(string cmd) {

    int q1, q2;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    DRT* T = Studs->search(k);
    if (T->getdata() == "") {
        cout << "\"" << k << "\" does not exist in the database!" << endl;
    }
    else {
        delete T;
        T = Studs->modify(k, "");
        cout << "\"" << k << "\" has been removed from the database!"
            << endl;
    }
    delete T;
}

void LookupCommand(string cmd) {
    int q1, q2;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    DRT* T = Studs->search(k);
    if (T->getdata() == "") {
        cout << "\"" << k << "\" does not exist in the database!" << endl;
        cout << "Next student: " + T->getnext() << endl;
        cout << "Previous student: " + T->getprev() << endl;
    }
    else {
        cout << "Student: " << k << endl;
        cout << "GPA: " << T->getdata() << endl;
        cout << "Previous: " << T->getprev() << endl;
        cout << "Next: " << T->getnext() << endl;
    }
    delete T;

}

void EditCommand(string cmd) {
    int q1, q2, q3;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    for (q3 = q2 + 1; cmd[q3] != ' '; q3++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    DRT* S = Studs->search(k);
    if (S->getdata() == "")
        cout << "\"" << k << "\" does not exist in the database." << endl;
    else {
        string gpa = S->getdata();
        string d = cmd.substr(q3 + 1, cmd.length() - 1);

        DRT* T = Studs->modify(k, d);
        cout << "Old GPA: " << gpa << endl;
        cout << "New GPA: " << T->getdata() << endl;
    }

}