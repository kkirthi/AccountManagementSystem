//
//  StockAccount.hpp
//  Final_Project_Programming_Finance
//
//  Created by kirthika on 28/11/17.
//  Copyright © 2017 kirthika. All rights reserved.
//

#ifndef StockAccount_h
#define StockAccount_h

#include <stdio.h>

#endif /* StockAccount_hpp */

#include "Account_krishnamurthy.h"
#include "LinkedList_krishnamurthy.h"
#include  <iostream>
#include  "File_handler_krishnamurthy.h"

class StockAccount:Account{
    
    LinkedList *list;
public:
    StockAccount();
    void displayValueOfStock();
    void displayCurrentPortfolio();
    void buyShares();
    void sellShares();
    void viewAGraph();
    void transactionHistory();
    void commitPortfolio();
    void readBalance();
    void savePortfolioHistory();
    
};
