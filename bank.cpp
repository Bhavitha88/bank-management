#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

struct Account{
   string AccountNumber;
   string name;
   string password;
   double balance;
   Account *next;
};
class BankManagement{
private : 
   Account *head;
   string datafile;
public :
   BankManagement() : head(NULL) ,datafile("accounts.txt"){
   }
   void addAccount(){
      Account *newaccount = new Account;
      cout << "Enter Account number :";
      cin >> newaccount->AccountNumber;
      if(isAccountnumberUnique(newaccount->AccountNumber)){
         cout << "Enter Name :";
         cin >> newaccount->name;
         cout << "Set Password :";
         cin >> newaccount->password;
         cout << "Intial Balance :";
         cin >> newaccount->balance;
         newaccount->next = NULL;
         if(head == NULL){
           head = newaccount;
         } 
         else{
            Account *curr = head;
            while(curr->next != NULL){
               curr = curr->next;
            }
            curr->next = newaccount;
         }
         cout << "Added Account successfully "<<endl;
         saveAccountsToFile();
      }
      else{
         cout << "Account number is not unique"<<endl;
         delete newaccount;
      }
   }
   bool isAccountnumberUnique(const string &accountNumber){
      Account *curr = head;
      while(curr != NULL){
         if(curr->AccountNumber == accountNumber){
            return false;
         }
         curr = curr->next;
      }
      return true;
   }
   Account *findAccount(const string &accountNumber,const string &password){
   Account *curr = head;
   while(curr != NULL){
      if(curr->AccountNumber == accountNumber && curr->password == password){
         return curr;
      }
      curr = curr->next;
   }
   return NULL;
   }
   void searchAccount(){
   string accountNumber;
   cout << "Enter the account number :";
   cin >> accountNumber;
   string password;
   cout << "Enter Password :";
   cin >> password;
   Account *account = findAccount(accountNumber,password);
   if(account != NULL){
      cout << "\nAccount number : "<<account->AccountNumber<<endl;
      cout<<"Name : "<<account->name<<endl;
      cout<<"Balance : "<<account->balance<<endl;
   }
   else{
      cout << "Account not found or Invalid Password\n";
   }
   }
   void depositAmount(){
      string accountNumber;
      cout << "Enter account number : ";
      cin >> accountNumber;
      string password;
      cout << "Enter password : ";
      cin >> password;
      Account *account = findAccount(accountNumber,password);
      if(account != NULL){
         double amount;
         cout << "Enter the amount to be deposited : ";
         cin >> amount;
         account->balance += amount;
         cout <<"Amount deposited successfully !!\n";
         saveAccountsToFile();
      }
      else{
         cout << "Account not found or Invalid Password\n";
      }
   }
   void withdrawAmount(){
      string accountNumber;
      cout << "Enter account number : ";
      cin >> accountNumber;
      string password;
      cout << "Enter password : ";
      cin >> password;
      Account *account = findAccount(accountNumber,password);
      if(account != NULL){
        double amount;
         cout << "Enter the withdrawal amount: ";
         cin >> amount;
         if(account->balance >= amount){
            account->balance -= amount;
            cout<<"Withdrawal successful"<<endl;
            saveAccountsToFile();
         } 
         else{
            cout << "Insufficient Balance"<<endl;
         }
      }
      else{
         cout << "Account not found or Invalid Password\n";
      }
   }
   void displayAccounts(){
      Account *curr = head;
      cout<<"---All Accounts----"<<endl;
      while(curr != NULL){
         cout<<"Account number : "<<curr->AccountNumber<<endl;
         cout<<"Name : "<<curr->name<<endl;
         cout<<"Balance : "<<curr->balance<<endl;
         curr = curr->next;
      }
      cout << endl;
   }
   void saveAccountsToFile(){
      ofstream outputFile(datafile.c_str());
      if(outputFile.is_open()){
         Account * curr = head;
         while(curr != NULL){
            outputFile << curr->AccountNumber<<","<<curr->name<<","<<curr->password<<","<<curr->balance<<endl;
            curr = curr->next;
         }
         cout << "\nAccounts are saved to files"<<endl;
      }
      else{
         cout << "\n Error : Unable to open file"<<endl;
      }

   }
   void loadAccountsFromFile(){
      ifstream inputFile(datafile.c_str());
      if(inputFile.is_open()){
         string line;
         while(getline(inputFile,line)){
            stringstream ss(line);
            string accountNumber,name,password;
            double balance;

            getline(ss,accountNumber,',');
            getline(ss,name,',');
            getline(ss,password,',');
            ss >> balance;
            Account *newaccount = new Account;
            newaccount->AccountNumber = accountNumber;
            newaccount->name = name;
            newaccount->password = password;
            newaccount->balance = balance;
            newaccount->next = NULL;
            if(head == NULL){
               head = newaccount;
            }
            else{
               Account *curr = head;
            while (curr->next != NULL)
            {
               curr = curr->next;
            }
            curr->next = newaccount;
            }
         }
         inputFile.close();
         cout << "Accounts loaded from file :" << datafile<<endl;
      }
      else{
         cout<<"Error : Unable to open file"<<endl;
      }
   }
   void menu(){
      loadAccountsFromFile();
      int choice;
      while(true){
         cout << "\n ----Bank Management---- "<<endl;
         cout << "1.Add account"<<endl;
         cout << "2.Search account"<<endl;
         cout << "3.Deposit Funds"<<endl;
         cout << "4.Withdrawal Funds"<<endl;
         cout << "5.Display All Accounts"<<endl;
         cout << "6.Exit"<<endl;
         cout << "Enter your choice"<<endl;
         cin >> choice;

         switch(choice){
            case 1:
               addAccount();
               break;
            case 2:
               searchAccount();
               break;
            case 3:
               depositAmount();
               break;
            case 4:
               withdrawAmount();
               break;
            case 5:
               displayAccounts();
               break;
            case 6:
               return;
            default:
               cout << "Invalid choice"<<endl;
         }


      }
   }
};

int main(){
  BankManagement bankSystem;
  bankSystem.menu();
  return 0;
}