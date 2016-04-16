//*****************************************************************************************
//  Program Filename   : Classes Task #3
//  Version           :1.0
//  Author             :Adrianna Chang
//  Purpose            :Interactive banking system for user, making use of classes
//  Date               :October 8th, 2015
//  Input from         :Keyboard
//  Output to           :Console
//*****************************************************************************************

//Preprocessor Directives
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <string.h>
using namespace std;

#define FILE_IN "King.dat" //Reading from and writing to the same file
#define FILE_OUT "King.dat"

//Declaration of class checking_Account
class checking_Account
{
	protected:		
		double account_balance;
	
	public:		
		
       float getBalance()
       {
       		return account_balance;
	   }	
};

//class joint_Account is derived from class checking_Account; inheritance is public
class joint_Account: public checking_Account
{
	//Protected members of the class include the two SSNs
	protected: 
		char owner_ssn[12], joint_owner_ssn[12];	
};

class account_owners: public joint_Account
{
	private:
		char owner_name[20], joint_owner_name[20], account_number[14], account_password[8];
		
	public:		 
		account_owners(char accountNum[14], char accountPass[8])
		{
			//Variable Declarations	
			ifstream input;
			input.open(FILE_IN, ios::in| ios::binary); 
			
			//READ BINARY FILE AND COMPARE TWO ITEMS HERE
			input.read((char*) &account_number, sizeof(char[14]));
			input.read((char*) &account_password, sizeof(char[8]));
			
			while (strcmp(accountNum,account_number) != 0 || strcmp(accountPass,account_password) != 0)
			{
				cout<<endl<<"ERROR: Account number or password is incorrect."<<endl<<endl<<"Please enter account number: ";
				cin>>accountNum;
				cout<<"Please enter account password: ";
				cin>>accountPass;
			}
			
			cout<<endl<<"Accessing account..."<<endl<<endl;
			input.close();
		}		
		void getInfo()
		{
			ifstream input;
			input.open(FILE_IN, ios::in| ios::binary); 
			
			input.seekg(22, ios::beg);
			input.read((char*) &owner_name, sizeof(char[20]));
			input.read((char*) &joint_owner_name, sizeof(char[20]));
			input.read((char*) &owner_ssn, sizeof(char[12]));
			input.read((char*) &joint_owner_ssn, sizeof(char[12]));
			input.read((char*) &account_balance, sizeof(double));
			input.close();	
		}

		void printInfo()
		{
			//Forces floats to be shown as decimals
			cout<<setiosflags(ios::fixed);
			//Sets # of decimals to be displayed to 2
			cout<<setprecision(2);
			
			cout<<endl<<"**ACCOUNT INFORMATION**"<<endl<<endl<<"Owner name: "<<owner_name<<endl<<"Joint owner name: "<<joint_owner_name<<endl;
			cout<<"Owner SSN: "<<owner_ssn<<endl<<"Joint owner SSN: "<<joint_owner_ssn<<endl<<endl<<"Account Balance: $"<<account_balance<<endl<<endl;
		
		}
			
		void input_transaction(char transaction_type, float transaction_amount)
		{
			//If withdrawal was selected
			if (transaction_type == 'W' || transaction_type == 'w')
			{
				//Account balance = account balance - transaction amount
				//User is notified of successful transaction
				account_balance -= transaction_amount;
				cout<<endl<<"Withdrawal Successful!"<<endl<<endl;
			}
			
			//Otherwise, if deposit was selected
			else
			{
				//Account balance = account balance + transaction amount
				//User is notified of successful transaction
				account_balance += transaction_amount;
				cout<<endl<<"Deposit Successful!"<<endl<<endl;
			}	
			
			writeInfo();	
		}
		void changeInfo(int choice)
		{

			if (choice == 1)
			{
				//Variable Declarations
				int selection, selection2;
				
				//Body
				cout<<endl<<"Would you like to..."<<endl<<"\t1)Remove joint owner\n\t2)Add joint owner\n\t3)Change joint owner\n\nChoice: ";
				cin>>selection;
				
				while (selection < 1 || selection > 3)
				{
					cout<<"Error: Invalid Entry."<<endl<<"Would you like to..."<<endl<<"\t1)Remove joint owner\n\t2)Add joint owner\n\t3)Change joint owner\n\nChoice: ";
					cin>>selection;
				}
				
				if (selection == 1)
				{
					if (strcmp(joint_owner_name,"N/A") == 0)
					{
						cout<<endl<<"Error: There is currently no joint owner for this account."<<endl<<endl;
					}
					
					else
					{
						cout<<endl<<"Confirm removal of joint owner "<<joint_owner_name<<"?"<<endl<<endl<<"1)Yes\n2)No"<<endl<<endl<<"Choice: ";
						cin>>selection2;
						
						while (selection2 != 1 && selection2 != 2)
						{
							cout<<"Error: Invalid Entry."<<endl<<"Confirm removal of joint owner "<<joint_owner_name<<"?"<<endl<<endl<<"1)Yes\n2)No"<<endl<<endl<<"Choice: ";
							cin>>selection2;
						}
						
						if (selection2 == 1)
						{
							strcpy(joint_owner_name, "N/A");
						}
						cout<<endl<<"Joint owner removed!"<<endl<<endl;
						
					}
				}
				
				else if (selection == 2)
				{
					if (strcmp(joint_owner_name,"N/A") != 0)
					{
						cout<<endl<<"Error: There is already a joint owner for this account."<<endl<<endl;
					}
					else
					{
						cout<<endl<<"Please enter name of new joint owner: ";
						cin.ignore(100, '\n');
						cin.getline(joint_owner_name, 20, '\n');
						cout<<endl<<"Joint owner added!"<<endl<<endl;
					}
				}
				else
				{
					cout<<endl<<"Enter new name for joint owner: ";
					cin.ignore(100, '\n');
					cin.getline(joint_owner_name, 20, '\n');
					cout<<endl<<"Joint owner name updated!"<<endl<<endl;
				}
				
			}
			
			else if (choice == 2)
			{
				//Variable Declarations
				int selection, selection2;
				
				//Body
				cout<<endl<<"Would you like to..."<<endl<<"\t1)Change owner's SSN\n\t2)Change joint owner's SSN\n\nChoice: ";
				cin>>selection;
				
				while (selection < 1 || selection > 2)
				{
					cout<<"Error: Invalid Entry."<<endl<<"Would you like to..."<<endl<<"\t1)Change owner's SSN\n\t2)Change joint owner's SSN\n\nChoice:";
					cin>>selection;
				}
				
				if (selection == 1)
				{
					cout<<endl<<"Please enter new SSN for owner: ";
					cin>>owner_ssn;
					cout<<endl<<"Owner's SSN successfully updated!"<<endl<<endl;
				}
				
				else
				{
					cout<<endl<<"Please enter new SSN for joint owner: ";
					cin>>joint_owner_ssn;
					cout<<endl<<"Joint owner's SSN successfully updated!"<<endl<<endl;
				}
			}
			
			else
			{
				//Variable Declarations
				char testPassword[8];
				
				cout<<endl<<"Please enter new 7-character password: ";
				cin>>account_password;
				cout<<"Reenter password to confirm: ";
				cin>>testPassword;
				
				while (strcmp(account_password, testPassword) != 0)
				{
					cout<<"Error: Passwords do not match."<<endl<<"Please enter new 7-character password: ";
					cin>>account_password;
					cout<<"Reenter password to confirm: ";
					cin>>testPassword;
				}
				
				cout<<endl<<"Password successfully changed!"<<endl<<endl;
			}
			
			writeInfo();
			
		}
		
	void writeInfo()
	{
		//Writes all information back into file with updated balance		
		ofstream output;
		output.open(FILE_OUT,ios::out | ios::binary);
		output.write((char*) &account_number, sizeof(char[14]));
		output.write((char*) &account_password, sizeof(char[8]));
		output.write((char*) &owner_name, sizeof(char[20]));
		output.write((char*) &joint_owner_name, sizeof(char[20]));
		output.write((char*) &owner_ssn, sizeof(char[12]));
		output.write((char*) &joint_owner_ssn, sizeof(char[12]));
		output.write((char*) &account_balance, sizeof(double));
		output.close();
	}
};

int main()
{
     //Variable Declarations:
     char accountNum[14], accountPass[8];
     int choice, selection;
     char transaction_choice;
     float currBalance, transaction_amount;

    //Function Body
    //Welcomes user to the program
    cout<<"Welcome to the Marauder Bank of Canada!"<<endl<<endl;
    
    cout<<"Please enter account number: ";
    cin>>accountNum;
    cout<<"Please enter account password: ";
    cin>>accountPass;
	
	account_owners account(accountNum, accountPass);   
	account.getInfo();
	
	cout<<"Would you like to..."<<endl<<"\t1)Display account information\n\t2)Process a transaction\n\t3)Edit account information\n\t4)Exit Program\n\nChoice: ";
	cin>>choice;
    
    while(choice < 1 || choice > 4)
    {
    	cout<<"Error: Invalid Entry."<<endl<<"Would you like to..."<<endl<<"\t1)Display account information\n\t2)Process a transaction\n\t3)Edit account information\n\t4)Exit Program\n\nChoice: ";
    	cin>>choice;
	}
	
	while (choice != 4)
	{
		if (choice == 1)
		{
			account.printInfo();
		}
		
        else if (choice == 2)
		{
			//User prompted to enter whether they'd like to make a withdrawal or a deposit
            cout<<endl<<"Would you like to..."<<endl<<"\tW - Make a withdrawal"<<endl<<"\tD - Make a deposit"<<endl<<endl<<"Choice: ";
		    cin>>transaction_choice;
		    
		    //If entry is invalid, user is notified of error and prompted to reenter choice
            while (transaction_choice != 'W' && transaction_choice != 'w' && transaction_choice != 'D' && transaction_choice != 'd')
		    {
		    	cout<<"Error: Invalid Entry."<<endl<<"Would you like to..."<<endl<<"\tW - Make a withdrawal"<<endl<<"\tD - Make a deposit"<<endl<<endl<<"Choice: ";
		   	    cin>>transaction_choice;
			}
		    
		    //If withdrawal was selected, user is prompted to enter withdrawal amount
            if (transaction_choice == 'W' || transaction_choice == 'w')
		    {
		    	cout<<endl<<"Enter withdrawal amount: $";
		    	cin>>transaction_amount;
		    	    	
				//Sets float currBalance to returned value from getBalance (member function associated with class object account)
				currBalance = account.getBalance();
		    	
		    	//if the current balance is less than the transaction amount, user is notified that there is not enough money in their account and is prompted to reenter withdrawal amount
				while (currBalance < transaction_amount)
		    	{
		    		cout<<"Error: Insufficient funds."<<endl<<endl<<"Enter withdrawal amount: $";
		    		cin>>transaction_amount;
				}
			}
			//Otherwise, user is prompted to enter deposit amount
			//No matter which option was selected (D or W), transaction amount is taken into the same variable (transaction_amount)
            else
			{
				cout<<endl<<"Enter deposit amount: $";
				cin>>transaction_amount;
			}	
			//Calls on member function input_transaction associated with class object account; sends transaction choice and the transaction amount to the function
            account.input_transaction(transaction_choice, transaction_amount); 
 	
		}
		
		else if (choice == 3)
		{			
			cout<<endl<<"Would you like to..."<<endl<<"\t1)Remove, add or change joint owner\n\t2)Change SSN number\n\t3)Change password\n\nChoice: ";
			cin>>selection;
			
			while (selection < 1 || selection > 3)
			{
				cout<<"Error: Invalid Entry."<<endl<<"Would you like to..."<<endl<<"\t1)Remove, add or change joint owner\n\t2)Change SSN number\n\t3)Change password\n\nChoice: ";
				selection;
			}
			
			account.changeInfo(selection);
			
		}
		cout<<"Would you like to..."<<endl<<"\t1)Display account information\n\t2)Process a transaction\n\t3)Edit account information\n\t4)Exit Program\n\nChoice: ";
		cin>>choice;
	    
	    while(choice < 1 || choice > 4)
	    {
	    	cout<<"Error: Invalid Entry."<<endl<<"Would you like to..."<<endl<<"\t1)Display account information\n\t2)Process a transaction\n\t3)Edit account information\n\t4)Exit Program\n\nChoice: ";
	    	cin>>choice;
		}
	}
 
    //Closing statement to user
    cout<<endl<<"Thanks for using the program! Goodbye."<<endl<<endl;
	
      system("PAUSE");
      return 0;
}
//end function main

