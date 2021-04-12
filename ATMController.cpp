#include "stdafx.h"
#include <iostream>
#include <string>

// STRUCTS
struct ATMMachine_t {
	bool cardInserted;
	int userID;
	int pin; 
	int accountType; // 1-"Checking" 2-"Saving"  
	int actionType; // 1-"Balance" 2-"Deposit" 3-"Withdraw"
} ATMMachine;

// FUNCTIONS
void controllerMenu(ATMMachine_t &ATMMachine);
void account(ATMMachine_t &ATMMachine);

using namespace std;
string AccountType[] = {"", "CHECKINGS", "SAVINGS"};
string response;

int AccountDetails[] = {
	1234,		// pin number
	100,		// checking account balance
	600,		// savings account balance
};

bool isPINValid(int pin) {
	if (pin == AccountDetails[0]) {
		return true;
	} else {
		return false;
	}
}

bool proceed(string response) {
	if(response =="y" || response == "Y"){
		return true;
	} else if(response == "n" || response == "N"){
		string exit;
		cout << "\n\n\n\t Thank you.";
		cin >> exit;
		return false;
	}

}

class AccountSettings {
	private:
		int type;		// account type
		int balance;	// account balance
	public:
		AccountSettings(ATMMachine_t &ATMMachine) {
			// type 1 = checkings
			// type 2 = savings
			this->type = ATMMachine.accountType;
			this->balance = AccountDetails[this->type];
		}
		int getWithdraw() {
			int withdrawAmount;
			cout << "Please enter amount to withdrawn:\n " << endl;
			cin >> withdrawAmount;

			// get account type
			if(withdrawAmount <= this->balance){
				int AccountBalance = this->balance -= withdrawAmount;
				cout << "Dispensing... ";
				cout << "$"<< withdrawAmount << endl;
				
				// update the account balance
				AccountDetails[this->type] = AccountBalance;
				getBalance();

			} else {
				cout << "Insufficent funds" << endl;
				getBalance();
			}

			return 0;
		}

		int getDeposit() {
			int depositAmount;
			cout << "Please enter an amount to deposit:\n" << endl;
			cin >> depositAmount;

			int AccountBalance = this->balance += depositAmount;

			// update the account balance
			AccountDetails[this->type] = AccountBalance;

			cout << "\t$" << depositAmount << " was deposited into your account";
			getBalance();
			 
			return 0;
		}

		int getBalance() {
			string confirmBalance;
			// get the account type, and return balance
			cout << "Would you like to check your "<< AccountType[this->type] << " account balance? (y/n)\n" << endl;
			cin >> confirmBalance;
			if(confirmBalance=="y" || confirmBalance=="Y"){
				cout << "Your account balance is: $" << this->balance << endl;
			} 
			
			cout << "\n\nWould you like to continue (y/n)?\n";
			cin >> response;

			if (proceed(response)) {
				account(ATMMachine); // return to account menu
			}

			return 0;
		}
};

void account(ATMMachine_t &ATMMachine) {
		// account option = 1 (checkings)
		// account option = 2 (savings)
			cout << "\n\n" <<AccountType[ATMMachine.accountType] << "--\n\t1. Check balance"
				<<"\n\t2. Withdraw from " << AccountType[ATMMachine.accountType] 
				<<"\n\t3. Deposit to " << AccountType[ATMMachine.accountType] 
				<<"\n\t4. --Return to Menu." << endl;

		// Pass in account type
		AccountSettings Account(ATMMachine); 

		cout<<"\tAction Type :: ";
		cin>>ATMMachine.actionType;
		
		switch(ATMMachine.actionType){
			case 1:
				cout << Account.getBalance();
				break;
			case 2: 
				cout << Account.getWithdraw();
				break;
			case 3: 
				cout << Account.getDeposit();
				break;
			case 4:
				controllerMenu(ATMMachine); // return to main menu
				break;
			default:
				cout << "Would you like to continue (y/n)\n";
				cin >> response;
				proceed(response);
			
				if (proceed(response)) {
					controllerMenu(ATMMachine); // return to main menu
				} 
				break;
		}
}

void controllerMenu(ATMMachine_t &ATMMachine) {
	
	cout<<"\tAccount Type :: ";
	cin>>ATMMachine.accountType;
	switch(ATMMachine.accountType){
		case 1: account(ATMMachine); // checkings
			break;
		case 2: account(ATMMachine); // savings
			break;
		default:
			cout << "Would you like to continue (y/n)\n";
			cin >> response;
			proceed(response);
			
			if (proceed(response)) {
				controllerMenu(ATMMachine);
			} 
			break;
	}
}


// Begin MAIN

int main(){ 
	
	cout<< "Welcome to ATM Controller Program.\nPlease enter your card to proceed."<<endl;
	
	cout<<" ATM Machine Inputs:"<<endl;
	cout<<"\tCard Inserted :: ";
	cin>>ATMMachine.cardInserted;
	cout<<"\tUser ID :: ";
	cin>>ATMMachine.userID;
	
	if(ATMMachine.cardInserted){
		do {
			cout<<"\tPIN :: ";
			cin>>ATMMachine.pin;
			
			if(isPINValid(ATMMachine.pin)){
				controllerMenu(ATMMachine);
			}
			else{
				cout<<"Please Enter a Valid PIN"<<endl;
			}
		} while(!isPINValid(ATMMachine.pin));
	}	
	
	return 0;
}			