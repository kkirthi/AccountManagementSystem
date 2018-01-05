//
//  Account.cpp
//  Final_Project_Programming_Finance
//
//  Created by kirthika on 27/11/17.
//  Copyright © 2017 kirthika. All rights reserved.
//

#include "Account_krishnamurthy.h"
#include <iostream>
#include "File_handler_krishnamurthy.h"

Account::Account(){
//the base class constructor.
    cashBalance =  FileHandler::getInitialCashBalanceFromFile();
    
}

void Account::setBalance(double cashB){
    
    cashBalance = cashB;
    
    
}

double Account::getBalance(){
    return cashBalance;
}
