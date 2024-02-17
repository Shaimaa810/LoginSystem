#ifndef LOGINSYSTEM_LOGINFUNCTIONS_H
#define LOGINSYSTEM_LOGINFUNCTIONS_H

#include<bits/stdc++.h>
#include <conio.h>
using namespace std;

// main menu
int main_menu();

// function 5
bool is_valid_username();

// function 6
void password_format();

// function 9
void cover_password();

// function 8
void is_strong_password(string &password);

// function 4
bool is_valid_phone_number();

// function 3
void is_valid_email(string &email);

// function 7
void repeat_password();

// function 2
void is_email_repeated(string &email);

// affine cipher
string affine_cipher(string str);

// function 11
void encrypt_password(string &password);

// load users data in vector
void load_users_data_in_vector();

// function 1
void get_user_data();

// function 10
void add_user();

// function 14
void denied_access();

// function 12
bool is_success_login();

// function 13
void is_fail_login();

// function 15
void change_password();


#endif //LOGINSYSTEM_LOGINFUNCTIONS_H
