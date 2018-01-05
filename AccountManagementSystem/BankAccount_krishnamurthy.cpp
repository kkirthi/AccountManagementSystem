//
//  BankAccount.cpp
//  Final_Project_Programming_Finance
//
//  Created by kirthika on 27/11/17.
//  Copyright © 2017 kirthika. All rights reserved.
//

#include "BankAccount_krishnamurthy.h"
#include <iostream>
#include "File_handler_krishnamurthy.h"
BankAccount::BankAccount(){
    //std::cout<<"\nIn bank account constructor";
    
    
}

void BankAccount::printTransactionHistory(){
    FileHandler::printHistory(true);
}
void BankAccount::readBalance(){
    //to read the bank account balance.
    cashBalance = FileHandler::getInitialCashBalanceFromFile();
    
}
void BankAccount::viewAccountBalance(){
    std::cout<<"\nThe account balance is "<<cashBalance;
}

void BankAccount::depositMoney(){
    
    std::cout<<"\nEnter the amount to be deposited ";
    double inCash;
    std::cin>>inCash;
    while (inCash<=0) {
        std::cout<<"\nEnter a positive amount ";
        std::cin>>inCash;


    }
    cashBalance  = cashBalance + inCash;
    
    struct transaction tempTranst;
    tempTranst.event = "Deposit";
    tempTranst.compSymbol = "Cash";
    tempTranst.number = -1;
    tempTranst.princePerShare = -1;
    tempTranst.TotalValue = inCash;
   
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    tempTranst.date = std::to_string(now->tm_mon+1)+"/"+std::to_string(now->tm_mday)+"/"+std::to_string(now->tm_year
                                                                                                        +1900);
    tempTranst.time = std::to_string(now->tm_hour)+":"+std::to_string(now->tm_min)+":"+std::to_string(now->tm_sec);
    
    FileHandler::commitTransactionToFile(tempTranst);
    
    FileHandler::recordCashTransaction(cashBalance);
    std::cout<<"\nCash Deposited. The balance is "<<cashBalance;
}


void BankAccount::withdrawMoney(){
    
    std::cout<<"\nEnter the amount to be withdrawn ";
    double inCash;
    std::cin>>inCash;
    while (inCash<=0) {
        std::cout<<"\nEnter a positive amount ";
        std::cin>>inCash;
        
        
    }
    if(cashBalance - inCash >0){
    cashBalance  = cashBalance - inCash;
        struct transaction tempTranst;
        tempTranst.event = "Withdraw";
        tempTranst.compSymbol = "Cash";
        tempTranst.number = -1;
        tempTranst.princePerShare = -1;
        tempTranst.TotalValue = inCash;
        
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        
        tempTranst.date = std::to_string(now->tm_mon+1)+"/"+std::to_string(now->tm_mday)+"/"+std::to_string(now->tm_year+1900);
        tempTranst.time = std::to_string(now->tm_hour)+":"+std::to_string(now->tm_min)+":"+std::to_string(now->tm_sec);
        
        FileHandler::commitTransactionToFile(tempTranst);
        FileHandler::recordCashTransaction(cashBalance);
        std::cout<<"\nCash Withdrawn. The balance is "<<cashBalance;


    }
    else
    {
    std::cout<<"\nSufficient funds not available";
    }
}

void BankAccount::commitPortfolio(){
    //FileHandler::commitCurrentPortfolioAndBalance(cashBalance);
}
