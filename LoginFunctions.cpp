#include "LoginFunctions.h"

ifstream instream;
ofstream outstream;

string username, password, email, phone_number, ID, temp;
vector <string> userData;
//----------------------------------------------------------------------------------------------------------------------
// main menu
int main_menu()
{
    int choice;
    cout << "Enter number of your choice:\n";
    cout << "1 - Register\n";
    cout << "2 - Login\n";
    cout << "3 - Change Password\n";
    cout << "4 - Exit\n";
    cin >> choice;
    return choice;
}
//----------------------------------------------------------------------------------------------------------------------
// function 5
bool is_valid_username()
{
    regex valid("[A-Z|a-z|_]+");
    return regex_match(username, valid);
}
//---------------------------------------------------------------------------------------------------------------------
// function 6
void password_format()
{
    cout << "password format rules\n";
    cout << "Mixture of uppercase and lowercase letters\n";
    cout << "Mixture of letters and numbers and underscore\n";
    cout << "Number of characters must be greater than 6\n";
    cout << "pls, enter your password according to the previous rules\n";
}
//----------------------------------------------------------------------------------------------------------------------
// function 9
void cover_password()
{
    password = "";
    char ch;
    while((ch = _getch()) != 13)
    {
        if(ch == 8)
        {
            password.pop_back();
            cout << "\b\b";
        }
        else
        {
            password += ch;
            cout << "*";
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------
// function 8
void is_strong_password(string &password)
{
    int cnt_ =0, cnt_uppercase = 0, cnt_lowercase = 0, cnt_num = 0;
    for(int i = 0; i < password.size(); ++i)
    {
        if(isalpha(password[i]))
        {
            if(isupper(password[i]))
                cnt_uppercase++;
            else if(islower(password[i]))
                cnt_lowercase++;
        }
        else if(isdigit(password[i]))
            cnt_num++;
        else if(password[i] == '_')
            cnt_++;
    }
    if(!((cnt_ + cnt_num + cnt_uppercase + cnt_lowercase) == password.size() && cnt_ > 0 && cnt_num >0 && cnt_uppercase > 0 && cnt_lowercase > 0))
    {
        cout << "This is not strong password. pls, enter the password again:\n";
        cover_password();
        is_strong_password(password);
    }
}
//---------------------------------------------------------------------------------------------------------------------
// function 4
bool is_valid_phone_number()
{
    regex valid ("01[0125]{1}[0-9]{8}");
    return regex_match(phone_number, valid);
}
//---------------------------------------------------------------------------------------------------------------------
// function 3
void is_valid_email(string &email)
{
    int cnt_at_symbol = 0;
    for(int i =0; i < email.size(); ++i)
    {
        if(email[i] == '@')
            cnt_at_symbol++;
    }
    if(cnt_at_symbol == 1)
    {
        int id = email.find('@');
        int cnt_local_part = 0;
        for(int i = 0; i < id; ++i)
        {
            if(isalpha(email[i]) || isdigit(email[i]) || ispunct(email[i]))
                cnt_local_part++;
            if(email[i] == '.' && email[i+1] == '.')
            {
                cnt_local_part = -1;
                break;
            }
        }
        int cnt_domain_part = 0, cnt_numbers_in_domain = 0;
        for(int i = id+1; i < email.size(); ++i)
        {
            if(isdigit(email[i]))
                cnt_numbers_in_domain++;
            if(isalpha(email[i]) || isdigit(email[i]) || email[i] == '-' || email[i] == '.')
                cnt_domain_part++;
        }
        if(cnt_local_part == -1 || email[0] == '.' || email[email.size()-1] == '.' || cnt_local_part != id ||
           cnt_numbers_in_domain == email.size()-id - 1 || cnt_domain_part != email.size() - id - 1 || email[id+1] == '-' ||
           email[email.size()-1] == '-')
        {
            cout << "invalid email. try again\n";
            cin >> email;
            is_valid_email(email);
        }
    }
    else
    {
        cout << "invalid email. try again\n";
        cin >> email;
        is_valid_email(email);
    }
}
//----------------------------------------------------------------------------------------------------------------------
// function 7
void repeat_password()
{
    cout << "\npls, repeat your password:\n";
    cover_password();
    if(temp != password)
        repeat_password();
}
//---------------------------------------------------------------------------------------------------------------------
// function 2
void is_email_repeated(string &email)
{
    if(find(userData.begin(), userData.end(), email) != userData.end())
    {
        cout << "This email refused, pls try again:\n";
        cin >> email;
        is_valid_email(email);
        is_email_repeated(email);
    }
}
//----------------------------------------------------------------------------------------------------------------------
// affine cipher
string affine_cipher(string str)
{
    int x = 0, exp = 0;
    for(int i = 0; i < str.size(); ++i)
    {
        if(isalpha(str[i]))
        {
            if(isupper(str[i]))
            {
                x = int(str[i]) - 65;
                exp = ((5 * x) + 8) % 26;
                str[i] = exp + 65;
            }
            else
            {
                x = int(str[i]) - 97;
                exp = ((5 * x) + 8) % 26;
                str[i] = exp + 97;
            }
        }
    }
    return str;
}
//----------------------------------------------------------------------------------------------------------------------
// function 11
void encrypt_password(string &password)
{
    password = affine_cipher(password);
}
//----------------------------------------------------------------------------------------------------------------------
// load users data in vector
void load_users_data_in_vector()
{
    instream.open("userdata.txt");
    while(!instream.eof())
    {
        string str;
        getline(instream, str);
        userData.push_back(str);
    }
    instream.close();
}
//----------------------------------------------------------------------------------------------------------------------
// function 1
void get_user_data()
{
    outstream.open("userdata.txt", ios :: app);
    outstream.close();

    load_users_data_in_vector();

    // enter username
    cout << "pls, enter your username containing letters and underscore only:";
    cin >> username;
    while(!is_valid_username())
    {
        cout << "invalid username\n";
        cout << "pls, enter your username containing letters and underscore only:";
        cin >> username;
    }

    // enter phone number
    cout << "pls, enter your phone number:";
    cin >> phone_number;
    while(!is_valid_phone_number())
    {
        cout << "This phone number is not valid. try again:\n";
        cin >> phone_number;
    }

    // enter password
    password_format();
    cover_password();
    is_strong_password(password);
    temp = password;
    repeat_password();
    encrypt_password(password);

    // enter email
    cout << "\npls, enter your email:";
    cin >> email;
    is_valid_email(email);
    is_email_repeated(email);
}
//---------------------------------------------------------------------------------------------------------------------
// function 10
void add_user()
{
    outstream.open("userdata.txt", ios :: app);
    cout << "pls, enter your ID:";
    cin >> ID;
    outstream << username << "\n";
    outstream << phone_number << "\n";
    outstream << password << "\n";
    outstream << email << "\n";
    outstream << ID << "\n";
    outstream.close();
}
//----------------------------------------------------------------------------------------------------------------------
// function 14
void denied_access()
{
    cout << "\nYou are denied access to the system\n";
}
//----------------------------------------------------------------------------------------------------------------------
// function 12
bool is_success_login()
{
    load_users_data_in_vector();
    cout << "Enter your ID:";
    cin >> ID;
    cout << "Enter your password:";
    cover_password();
    password = affine_cipher(password);
    bool b1, b2;
    b1 = find(userData.begin(), userData.end(), ID) != userData.end();
    b2 = find(userData.begin(), userData.end(), password) != userData.end();
    if(b1 && b2)
    {
        cout << "\nSuccessful Login, Welcome";
        return true;
    }
    else
    {
        return false;
    }
}
//----------------------------------------------------------------------------------------------------------------------
// function 13
void is_fail_login()
{
    cout << "\nFailed Login. Try again\n";
}
//----------------------------------------------------------------------------------------------------------------------
// function 15
void change_password()
{
    cout << "Enter your old password:";
    cover_password();
    encrypt_password(password);
    load_users_data_in_vector();

    // check if the password exist in the vector or not
    if(find(userData.begin(), userData.end(), password) != userData.end())
    {
        vector<string> :: iterator it = find(userData.begin(), userData.end(), password);
        int index = distance(userData.begin(), it);

        // enter new password
        password_format();
        cout << "Enter your new password:";
        cover_password();
        is_strong_password(password);
        temp = password;
        repeat_password();
        encrypt_password(password);

        userData[index] = password; // add the new password in vector
        outstream.open("userdata.txt");
        outstream.close();
        // add the new password in the file
        outstream.open("userdata.txt", ios :: app);
        for(int i = 0; i < userData.size(); ++i)
        {
            outstream << userData[i] << "\n";
        }
        outstream.close();
    }
    else
        cout << "This password is wrong\n";

}

