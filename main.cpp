// FCAI - programming 1 - Assignment 4
// Program Name: Login System
// Last Modification Date: 10 / 5 / 2022
#include<bits/stdc++.h>
#include "LoginFunctions.h"

using namespace std;
int main()
{
    while (true) {
        int choice = main_menu();
        if(choice == 1)
        {
            get_user_data();
            add_user();
        }
        else if(choice == 2)
        {
            int login_trials = 0;
            while(!is_success_login())
            {
                login_trials++;
                if(login_trials == 3)
                {
                    denied_access();
                    break;
                }
                is_fail_login();
            }
        }
        else if(choice == 3)
        {
            change_password();
        }
        else if(choice == 4)
        {
            exit(1);
        }
    }

    return 0;
}


