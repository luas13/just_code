/*
1. More general with extra features of
    a. Removing an account easily.
    b. Use of double pointer so matter of playing with pointer
*/

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
  
const int TABLE_SIZE= 128;

class Account{
private:
    string name;
    string address;
    float acc_bal;
    int acc_no;
    int type;

public:
    Account()
    {
        acc_bal = 0.0;
        type = -1;
    }
    
    Account(string const& n, string const& ad, float bal, int no, int t)
    {
        name = n;
        address = ad;
        acc_bal = bal;
        acc_no = no;
        type = t;
    }

    int getAccNo()
    {
        return acc_no;
    }

    int getAccBal()
    {
        return acc_bal;
    }

    int getType()
    {
        return type;
    }

    void getDetails()
    {
        cout << "Name: " << name;
        cout << "\nAddress: " << address;
        cout << "\nAcc No: " << acc_no;
        cout << "\nAccount Type: " << type;
        cout << "\nAccount Balance: $" << acc_bal << endl;
    }

    void deposit(float d)
    {
        acc_bal += d;
    }

    void withdraw(float d)
    {
        acc_bal -= d;
    }
};

class Bank{
private:
    Account **bankTable;
public:
    Bank()
    {
        // Pointer to Account or array of Account objects
        // default Account objects gets added
        // whose bal = 0.0 & type is -1
        bankTable = new Account*[TABLE_SIZE];
        for(int i=0; i<TABLE_SIZE; i++)
            bankTable[i] = NULL;
    }

    void addAccount(Account* acc)
    {
        for(int i=0; i<TABLE_SIZE; i++)
        {
            if (bankTable[i] == NULL)
            {
                bankTable[i] = acc;
                return;
            }
        }

        cout<<"No space in Bank database"<<endl;
    }
    
    void bRemoveAccount(Account* acc)
    {
        int ano = acc->getAccNo();
        for(int i=0; i<TABLE_SIZE; i++)
        {
            if (bankTable[i]->getAccNo() == ano)
            {
                Account* tmp = bankTable[i];
                bankTable[i] = NULL;
                delete tmp;
                // Segmentation fault if break is not present
                break;
            }
        }
    }
    
    void bDeposit(Account* acc, int v)
    {
        int accno = acc->getAccNo();
        bankTable[accno]->deposit(v);
    }

    void bWithdraw(Account* acc, int v)
    {
        int accno = acc->getAccNo();
        int bal = bankTable[accno]->getAccBal();
        if (v > bal)
            cout<<"Withdrawal can't process. Less cash in account !!!"<<endl;
        else
            bankTable[accno]->withdraw(v);
    }

    void bAccDetails(Account* acc)
    {
        int accno = acc->getAccNo();
        if (bankTable[accno] == NULL)
        {
            cout<<endl<<"Account details not present. ";
            cout<<"Account with acc no: "<<accno<<" does not exist !!!"<<endl;
            return;
        }
        bankTable[accno]->getDetails();
    }

    void bTransfer(Account* acc1, Account* acc2, int v)
    {
        int accno1 = acc1->getAccNo();
        int accno2 = acc2->getAccNo();

        int bal1 = bankTable[accno1]->getAccBal();
        int bal2 = bankTable[accno2]->getAccBal();

        if (v > bal1)
            cout<<"Less cash in Account with accno: "<<accno1<<" to transfer !!!"<<endl;
        else
        {
            bankTable[accno1]->withdraw(v);
            bankTable[accno2]->deposit(v);
        }
    }

    ~Bank()
    {
        for(int i=0; i<TABLE_SIZE; i++)
        {
            if(bankTable[i] != NULL)
                delete bankTable[i];
        }
        delete[] bankTable;
    }
};


int main()
{
    Bank b;

    Account* acc1 = new Account("Abhi", "Tempe", 500, 0, 0);
    Account* acc2 = new Account("Bala", "Cali", 600, 1, 0);

    b.addAccount(acc1);
    b.addAccount(acc2);

    int v = 60;
    b.bAccDetails(acc1);
    b.bDeposit(acc1, v);
    cout<<endl<<"After deposits of amount: "<<v<<endl;
    b.bAccDetails(acc1);

    b.bTransfer(acc1, acc2, 100);
    cout<<endl<<"After transfer of amount: 100 from acc "<<acc1->getAccNo()<<" to acc "<<acc2->getAccNo()<<endl;
    b.bAccDetails(acc1);
    cout<<endl;
    b.bAccDetails(acc2);
    
    b.bRemoveAccount(acc2);
    b.bAccDetails(acc2);
    
    return 0;
}


/*
Output

Name: Abhi
Address: Tempe
Acc No: 0
Account Type: 0
Account Balance: $500

After deposits of amount: 60
Name: Abhi
Address: Tempe
Acc No: 0
Account Type: 0
Account Balance: $560

After transfer of amount: 100 from acc 0 to acc 1
Name: Abhi
Address: Tempe
Acc No: 0
Account Type: 0
Account Balance: $460

Name: Bala
Address: Cali
Acc No: 1
Account Type: 0
Account Balance: $700

Account details not present. Account with acc no: 1 does not exist !!!

*/
