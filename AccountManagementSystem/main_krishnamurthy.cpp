//
//  main.cpp
//  Final_Project_Programming_Finance
//
//  Created by kirthika on 27/11/17.
//  Copyright © 2017 kirthika. All rights reserved.
//

#include <iostream>
#include "BankAccount_krishnamurthy.h"
#include "StockAccount_krishnamurthy.h"

using namespace std;
void display(){
    
    
    cout << "\nPlease select an account to access:";
    cout << "\n1. Stock Portfolio Account";
    cout << "\n2. Bank Account";
    cout << "\n3. Exit\n";

    
}
void diplayStockMenu(){
    cout << "\nPlease select an option:";
    cout << "\n1. Display the value of a stock";
    cout << "\n2. Display the current portfolio";
    cout << "\n3. Buy shares";
    cout << "\n4. Sell shares";
    cout << "\n5. View a graph for the portfolio value";
    cout << "\n6. View transaction history";
    cout << "\n7. Return to previous menu\n";
}


void displayBankMenu(){
    cout << "\nPlease select an option";
    cout << "\n1. View Account Balance";
    cout << "\n2. Deposit money";
    cout << "\n3. Withdraw money";
    cout << "\n4. Print out history";
    cout << "\n5. Return to previous menu\n";
    
    
}

int getValidInputForStock(int min,int max, std::string error){
    int input;
    cin>>input;
    
    while (input<min||input>max) {
        std::cout<<error;
        cin>>input;

    }
    return input;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    
    display();//Displays the menu
    BankAccount baccount;//for bank account object
//    FileHandler::reset();
//
//    return 9;

    StockAccount saccount;//for stock account object
    
    
    int choice=0;
    choice = getValidInputForStock(1, 3, "\nPlease enter a choice from 1 to 3:");
    
    while (choice) {
        
    if(choice == 1){
        diplayStockMenu();
        int accChoice;
        saccount.readBalance();
        accChoice = getValidInputForStock(1, 7, "\nPlease enter a choice from 1 to 7:");
        //Each choice is handled by the corresponding class.
        while (accChoice!=7) {
            switch (accChoice) {
          
                case 1:
                    saccount.displayValueOfStock();
                    break;
                case 2:
                    saccount.displayCurrentPortfolio();
                    break;
                case 3:
                    saccount.buyShares();
                    break;
                case 4:
                    saccount.sellShares();
                    break;
                case 5:
                    saccount.viewAGraph();
                    break;
                case 6:
                    saccount.transactionHistory();
                    break;
                default:
                    break;
        }
            diplayStockMenu();
            accChoice = getValidInputForStock(1, 7, "\nPlease enter a choice from 1 to 7:");
        }
    }
    else if(choice == 2){
        displayBankMenu();
        int accChoice;
        accChoice = getValidInputForStock(1, 5, "\nPlease enter a choice from 1 to 5:");
        baccount.readBalance();
        //Each choice is handled by the corresponding class.

        while (accChoice!=5){
        switch (accChoice) {
            case 1:
                baccount.viewAccountBalance();
                break;
            case 2:
                baccount.depositMoney();
                break;
            case 3:
                baccount.withdrawMoney();
                break;
            case 4:
                baccount.printTransactionHistory();
                break;
    }
            accChoice = getValidInputForStock(1, 5, "\nPlease enter a choice from 1 to 5:");
    }
    }
    else if(choice == 3){
        //while exit we save the portfolio history value in a file for plotting.
        std::cout<<"In the third case";
        saccount.readBalance();
        saccount.savePortfolioHistory();
        break;
        
    }
        display();
        cin>>choice;

    }
        return 0;
}
