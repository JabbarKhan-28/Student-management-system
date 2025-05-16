#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_USERS = 100;
const int MAX_COURSES = 10;

struct SignUp {
    string user_name, father_name, email, password, reg_no, confirm_password;
    string role, address, gender, day, date, year, cnic, phone_number;
};

struct Course {
    string name, description, instructor;
};

struct Attendance {
    string name, date;
    string reg_no;
    bool present;
};

struct Marks {
    string course_name;
    string reg_no;
    double marks;
};

SignUp admins[MAX_USERS];
SignUp students[MAX_USERS];
Course courses[MAX_COURSES];
Attendance attendance_records[MAX_USERS];
Marks marks_records[MAX_USERS];

int admin_count = 0;
int student_count = 0;
int course_count = 0;
int attendance_count = 0;
int marks_count = 0;

void load_data();
void save_data();
void newuser();
void student_menu();
void main_page();
void admin_menu();
void admin_sign_up();
void student_signup();
void login_admin();
void login_student();
void add_course();
void remove_course();
void update_course();
void add_marks();
void show_marks();
void delete_marks();
void mark_attendance();
void display_attendance();
void remove_attendance();

void load_data() {
    // Load admin data
    ifstream admin_file("admin_data.txt");
    if (admin_file.is_open()) {
        while (admin_count < MAX_USERS && getline(admin_file, admins[admin_count].reg_no)) {
            getline(admin_file, admins[admin_count].user_name);
            getline(admin_file, admins[admin_count].father_name);
            getline(admin_file, admins[admin_count].address);
            getline(admin_file, admins[admin_count].email);
            getline(admin_file, admins[admin_count].password);
            getline(admin_file, admins[admin_count].role);
            getline(admin_file, admins[admin_count].cnic);
            getline(admin_file, admins[admin_count].phone_number);
            admin_count++;
        }
        admin_file.close();
    }

    // Load student data
    ifstream student_file("student_data.txt");
    if (student_file.is_open()) {
        while (student_count < MAX_USERS && getline(student_file, students[student_count].reg_no)) {
            getline(student_file, students[student_count].user_name);
            getline(student_file, students[student_count].father_name);
            getline(student_file, students[student_count].address);
            getline(student_file, students[student_count].email);
            getline(student_file, students[student_count].password);
            getline(student_file, students[student_count].role);
            getline(student_file, students[student_count].cnic);
            getline(student_file, students[student_count].phone_number);
            student_count++;
        }
        student_file.close();
    }

    // Load course data
    ifstream course_file("course_data.txt");
    if (course_file.is_open()) {
        while (course_count < MAX_COURSES && getline(course_file, courses[course_count].name)) {
            getline(course_file, courses[course_count].description);
            getline(course_file, courses[course_count].instructor);
            course_count++;
        }
        course_file.close();
    }

    // Load attendance data
    ifstream attendance_file("attendance_data.txt");
    if (attendance_file.is_open()) {
        while (attendance_count < MAX_USERS && getline(attendance_file, attendance_records[attendance_count].reg_no)) {
            getline(attendance_file, attendance_records[attendance_count].name);
            getline(attendance_file, attendance_records[attendance_count].date);
            attendance_file >> attendance_records[attendance_count].present;
            attendance_file.ignore(); // Ignore the newline character
            attendance_count++;
        }
        attendance_file.close();
    }

    // Load marks data
    ifstream marks_file("marks_data.txt");
    if (marks_file.is_open()) {
        while (marks_count < MAX_USERS && getline(marks_file, marks_records[marks_count].reg_no)) {
            getline(marks_file, marks_records[marks_count].course_name);
            marks_file >> marks_records[marks_count].marks;
            marks_file.ignore(); // Ignore the newline character
            marks_count++;
        }
        marks_file.close();
    }
}

void save_data() {
    // Save admin data
    ofstream admin_file("admin_data.txt");
    for (int i = 0; i < admin_count; i++) {
        admin_file << admins[i].reg_no << "\n" << admins[i].user_name << "\n" << admins[i].father_name << "\n"
                   << admins[i].address << "\n" << admins[i].email << "\n" << admins[i].password << "\n"
                   << admins[i].role << "\n" << admins[i].cnic << "\n" << admins[i].phone_number << "\n";
    }
    admin_file.close();

    // Save student data
    ofstream student_file("student_data.txt");
    for (int i = 0; i < student_count; i++) {
        student_file << students[i].reg_no << "\n" << students[i].user_name << "\n" << students[i].father_name << "\n"
                     << students[i].address << "\n" << students[i].email << "\n" << students[i].password << "\n"
                     << students[i].role << "\n" << students[i].cnic << "\n" << students[i].phone_number << "\n";
    }
    student_file.close();

    // Save course data
    ofstream course_file("course_data.txt");
    for (int i = 0; i < course_count; i++) {
        course_file << courses[i].name << "\n" << courses[i].description << "\n" << courses[i].instructor << "\n";
    }
    course_file.close();

    // Save attendance data
    ofstream attendance_file("attendance_data.txt");
    for (int i = 0; i < attendance_count; i++) {
        attendance_file << attendance_records[i].reg_no << "\n" << attendance_records[i].name << "\n"
                        << attendance_records[i].date << "\n" << attendance_records[i].present << "\n";
    }
    attendance_file.close();

    // Save marks data
    ofstream marks_file("marks_data.txt");
    for (int i = 0; i < marks_count; i++) {
        marks_file << marks_records[i].reg_no << "\n" << marks_records[i].course_name << "\n" << marks_records[i].marks << "\n";
    }
    marks_file.close();
}

void admin_sign_up() {
    SignUp admin;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Enter your detail below                                   == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    cout << "\n\t                           10. Enter your registration no::";
    cin >> admin.reg_no;

    cout << "\n\t                           01. Enter your name::";
    cin.ignore();
    getline(cin, admin.user_name);

    cout << "\n\t                           02. Enter your father name::";
    getline(cin, admin.father_name);

    cout << "\n\t                           03. Enter your address::";
    getline(cin, admin.address);

    cout << "\n\t                           08. Enter your Email::";
    getline(cin, admin.email);

    while (true) {
        cout << "\n\t                           09. Enter your Password::";
        getline(cin, admin.password);
        if (admin.password.length() >= 8) {
            break;
        } else {
            cout << "\n\t                           Password does not meet the requirement";
        }
    }

    while (true) {
        cout << "\n\t                           10. Enter your password again::";
        getline(cin, admin.confirm_password);
        if (admin.password == admin.confirm_password) {
            break;
        } else {
            cout << "\n\t                           Password does not match";
        }
    }

    cout << "\n\t                           09. Enter your Role in the department::";
    getline(cin, admin.role);

    while (true) {
        cout << "\n\t                           10. Enter your CNIC::";
        getline(cin, admin.cnic);
        if (admin.cnic.length() == 13) {
            break;
        } else {
            cout << "\n\t                           CNIC does not meet the requirement";
        }
    }

    while (true) {
        cout << "\n\t                           11. Enter your Phone Number::";
        cin >> admin.phone_number;
        if (admin.phone_number.length() == 11) {
            break;
        } else {
            cout << "\n\t                           Incorrect Phone number! please enter correct phone number::";
        }
    }

    cout << "\n\t                           13. Enter your Gender please::";
    cin.ignore();
    getline(cin, admin.gender);

    cout << "\n\t                           14. Enter your Date of birth please (day date year)::";
    cin >> admin.day >> admin.date >> admin.year;

    admins[admin_count++] = admin; // Store the new admin and increment the count
    save_data();

    cout << "\n\t                            Your account has been created successfully";
    cout << "\n\t ============================================================================================= " << "\n";
    cout << "\n\t                            Do you want to add more data.\n\t                            1. Yes\n\t                            2. No\n";
    int option;
    cout << "                                  Please select the option: ";
    cin >> option;

    if (option == 1) {
        admin_sign_up();
    } else {
        main_page();
    }
}

void student_signup() {
    SignUp student;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Enter your detail below                                   == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    cout << "\n\t                           01. Enter your registration no::";
    cin >> student.reg_no;

    cout << "\n\t                           02. Enter your name::";
    cin.ignore();
    getline(cin, student.user_name);

    cout << "\n\t                           03. Enter your father name::";
    getline(cin, student.father_name);

    cout << "\n\t                           04. Enter your address::";
    getline(cin, student.address);

    cout << "\n\t                           05. Enter your Email::";
    getline(cin, student.email);

    while (true) {
        cout << "\n\t                           06. Enter your Password (at least 8 characters)::";
        getline(cin, student.password);
        if (student.password.length() >= 8) {
            break;
        } else {
            cout << "\n\t                           Password does not meet the requirement";
        }
    }

    while (true) {
        cout << "\n\t                           07. Enter your password again::";
        getline(cin, student.confirm_password);
        if (student.password == student.confirm_password) {
            break;
        } else {
            cout << "\n\t                           Password does not match";
        }
    }

    cout << "\n\t                           08. Enter your Gender::";
    getline(cin, student.gender);

    while (true) {
        cout << "\n\t                           09. Enter your CNIC::";
        getline(cin, student.cnic);
        if (student.cnic.length() == 13) {
            break;
        } else {
            cout << "\n\t                           CNIC does not meet the requirement";
        }
    }

    while (true) {
        cout << "\n\t                           10. Enter your Phone Number::";
        getline(cin, student.phone_number);
        if (student.phone_number.length() == 11) {
            break;
        } else {
            cout << "\n\t                           Incorrect Phone number! please enter correct phone number";
        }
    }

    cout << "\n\t                           11. Enter your Date of birth (day date year)::";
    cin >> student.day >> student.date >> student.year;

    students[student_count++] = student; // Store the new student and increment the count
    save_data();

    cout << "\n\t                            Your account has been created successfully";
    cout << "\n\t ============================================================================================= " << "\n";
    cout << "\n\t                            Do you want to add more data.\n\t                            1. Yes\n\t                            2. No\n";
    int option;
    cout << "                                  Please select the option: ";
    cin >> option;
    if (option == 1) {
        student_signup();
    } else {
        return;
    }
}

void login_admin() {
    load_data();
    string input_email, input_password;
    cout << "\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Enter your detail below                               == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    cout << "\n\t                           01. Enter your email ::"; 
    cin.ignore();
    getline(cin, input_email);
    cout << "\n\t                           02. Enter your Password ::"; 
    getline(cin, input_password);

    for (int i = 0; i < admin_count; i++) {
        if (admins[i].email == input_email && admins[i].password == input_password) {
            cout << "\n\t                           Login successful!\n";
            admin_menu();
            return;
        }
    }
    cout << "\n\t                           Invalid email or password!\n";
}

void login_student() {
    load_data();
    string input_email, input_password;
    cout << "\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Enter your detail below                               == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    cout << "\n\t                           01. Enter your email ::"; 
    cin.ignore();
    getline(cin, input_email);
    cout << "\n\t                           02. Enter your Password ::"; 
    getline(cin, input_password);

    for (int i = 0; i < student_count; i++) {
        if (students[i].email == input_email && students[i].password == input_password) {
            cout << "\n\t                           Login successful!\n";
            student_menu();
            return;
        }
    }
    cout << "\n\t                           Invalid email or password!\n";
}

void main_page() {
    int option = 0;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                              Login to Main Menu                                         == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                        01. Administration account                                       == " << "\n";
    cout << "\n\t ==                        02. Student account                                              == " << "\n";
    cout << "\n\t ==                        03. New user                                                      == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";
    cout << "\n\t                                  Please Select the Option:  ";
    cin >> option;

    switch (option) {
        case 1:
            login_admin();
            break;
        case 2:
            login_student();
            break;
        case 3:
            newuser();
            break;
        default:
            cout << "\n\t                           Invalid option!\n";
            break;
    }
}

void newuser() {
    int option = 0;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Select Account Type                                   == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                        01. Administration account                                       == " << "\n";
    cout << "\n\t ==                        02. Student account                                              == " << "\n";
    cout << "\n\t ==                        03. Go Back                                                      == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";
    cout << "\n\t                                  Please Select the Option:  ";
    cin >> option;

    switch (option) {
        case 1:
            admin_sign_up();
            break;
        case 2:
            student_signup();
            break;
        case 3:
            main_page();
            break;
        default:
            cout << "\n\t                           Invalid option!\n";
            break;
    }
}

void admin_menu() {
    int option;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Admin Menu                                           == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";
    cout << "\n\t01. Add Course\n";
    cout << "\n\t02. Remove Course\n";
    cout << "\n\t03. Update Course\n";
    cout << "\n\t04. Add Marks\n";
    cout << "\n\t05. Show Marks\n";
    cout << "\n\t06. Delete Marks\n";
    cout << "\n\t07. Add User\n";
    cout << "\n\t08. Remove User\n";
    cout << "\n\t09. Add Attendance\n";
    cout << "\n\t10. Show Attendance\n";
    cout << "\n\t11. Remove Attendance\n";
    cout << "\n\t12. Logout\n";
    cout << "\n\t13. Exit\n";
    cout << "\n\t                                  Please Select the Option:  ";
    cin >> option;

    switch (option) {
        case 1:
            add_course();
            break;
        case 2:
            remove_course();
            break;
        case 3:
            update_course();
            break;
        case 4:
            add_marks();
            break;
        case 5:
            show_marks();
            break;
        case 6:
            delete_marks();
            break;
        case 7:
            newuser();
            break;
        case 8:
            // Remove user function
            break;
        case 9:
            mark_attendance();
            break;
        case 10:
            display_attendance();
            break;
        case 11:
            remove_attendance();
            break;
        case 12:
            main_page();
            break;
        case 13:
            exit(0);
            break;
        default:
            cout << "\n\t                           Invalid option!\n";
            break;
    }
}

void student_menu() {
    int option;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Student Menu                                         == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";
    cout << "\n\t01. Show Marks\n";
    cout << "\n\t02. Show Attendance\n";
    cout << "\n\t03. Logout\n";
    cout << "\n\t04. Exit\n";
    cout << "\n\t                                  Please Select the Option:  ";
    cin >> option;

    switch (option) {
        case 1:
            show_marks();
            break;
        case 2:
            display_attendance();
            break;
        case 3:
            main_page();
            break;
        case 4:
            exit(0);
            break;
        default:
            cout << "\n\t                           Invalid option!\n";
            break;
    }
}

void add_course() {
    Course course;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Add a New Course                                      == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    cout << "\n\t                           01. Enter Course Name::";
    cin.ignore();
    getline(cin, course.name);

    cout << "\n\t                           02. Enter Course Description::";
    getline(cin, course.description);

    cout << "\n\t                           03. Enter Instructor Name::";
    getline(cin, course.instructor);

    courses[course_count++] = course; // Store the new course and increment the count
    save_data();

    cout << "\n\t                           Course \"" << course.name << "\" added successfully!\n";
}

void remove_course() {
    string course_name;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Remove a Course                                      == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    cout << "\n\t                                      01. Enter Course Name::";
    cin.ignore();
    getline(cin, course_name);

    bool found = false;
    for (int i = 0; i < course_count; i++) {
        if (courses[i].name == course_name) {
            found = true;
            for (int j = i; j < course_count - 1; j++) {
                courses[j] = courses[j + 1]; // Shift courses left
            }
            course_count--; // Decrease the count
            break;
        }
    }

    if (found) {
        save_data();
        cout << "\n\t                           Course \"" << course_name << "\" removed successfully!\n";
    } else {
        cout << "\n\t                           Course \"" << course_name << "\" not found!\n";
    }
}

void update_course() {
    string course_name;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Update a Course                                      == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    cout << "\n\t                           01. Enter Course Name to Update::";
    cin.ignore();
    getline(cin, course_name);

    for (int i = 0; i < course_count; i++) {
        if (courses[i].name == course_name) {
            cout << "\n\t                           02. Enter New Course Description::";
            getline(cin, courses[i].description);
            cout << "\n\t                           03. Enter New Instructor Name::";
            getline(cin, courses[i].instructor);
            save_data();
            cout << "\n\t                           Course \"" << course_name << "\" updated successfully!\n";
            return;
        }
    }
    cout << "\n\t                           Course \"" << course_name << "\" not found!\n";
}

void add_marks() {
    Marks record;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Add Marks                                             == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    cout << "\n\t01. Enter your registration no::";
    cin >> record.reg_no;

    cout << "\n\t02. Enter Course Name::";
    cin.ignore();
    getline(cin, record.course_name);

    cout << "\n\t03. Enter Marks::";
    cin >> record.marks;

    marks_records[marks_count++] = record; // Store the new marks and increment the count
    save_data();

    cout << "\n\t                           Marks added successfully!\n";
}

void show_marks() {
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Show Marks                                            == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    string reg_no;
    cout << "\n\t01. Enter registration no::";
    cin >> reg_no;

    for (int i = 0; i < marks_count; i++) {
        if (marks_records[i].reg_no == reg_no) {
            cout << "\n\tCourse Name: " << marks_records[i].course_name;
            cout << "\n\tMarks: " << marks_records[i].marks;
            cout << "\n\t ============================================================================================= " << "\n";
        }
    }
}

void delete_marks() {
    string reg_no;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Delete Marks                                          == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    cout << "\n\t01. Enter registration no::";
    cin >> reg_no;

    bool found = false;
    for (int i = 0; i < marks_count; i++) {
        if (marks_records[i].reg_no == reg_no) {
            found = true;
            for (int j = i; j < marks_count - 1; j++) {
                marks_records[j] = marks_records[j + 1]; // Shift marks left
            }
            marks_count--; // Decrease the count
            break;
        }
    }

    if (found) {
        save_data();
        cout << "\n\t                     Marks deleted successfully!\n";
    } else {
        cout << "\n\t                     No marks found for registration no: " << reg_no << "\n";
    }
}

void mark_attendance() {
    Attendance record;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Mark Attendance                                      == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    cout << "\n\t                           01. Enter your registration no::";
    cin >> record.reg_no;

    cout << "\n\t                           02. Enter your name::";
    cin.ignore();
    getline(cin, record.name);

    cout << "\n\t                           03. Enter the date (dd-mm-yyyy)::";
    getline(cin, record.date);

    cout << "\n\t                           04. Present (1 for Yes, 0 for No)::";
    cin >> record.present;

    attendance_records[attendance_count++] = record; // Store the new attendance and increment the count
    save_data();

    cout << "\n\t                           Attendance marked successfully!\n";
}

void display_attendance() {
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   All Attendance Records                                == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    for (int i = 0; i < attendance_count; i++) {
        cout << "\n\t                           Registration No: " << attendance_records[i].reg_no;
        cout << "\n\t                           Name: " << attendance_records[i].name;
        cout << "\n\t                           Date: " << attendance_records[i].date;
        cout << "\n\t                           Present: " << (attendance_records[i].present ? "Yes" : "No") << "\n";
        cout << "\n\t ============================================================================================= " << "\n";
    }
}

void remove_attendance() {
    string reg_no;
    cout << "\n\n\t ============================================================================================= " << "\n";
    cout << "\n\t ==                                   Remove Attendance                                     == " << "\n";
    cout << "\n\t ============================================================================================= " << "\n";

    cout << "\n\t                           01. Enter registration no::";
    cin >> reg_no;

    bool found = false;
    for (int i = 0; i < attendance_count; i++) {
        if (attendance_records[i].reg_no == reg_no) {
            found = true;
            for (int j = i; j < attendance_count - 1; j++) {
                attendance_records[j] = attendance_records[j + 1]; // Shift attendance left
            }
            attendance_count--; // Decrease the count
            break;
        }
    }

    if (found) {
        save_data();
        cout << "\n\t                           Attendance removed successfully!\n";
    } else {
        cout << "\n\t                           No attendance record found for registration no: " << reg_no << "\n";
    }
}

int main() {
    load_data();
    main_page();
    return 0;
}
