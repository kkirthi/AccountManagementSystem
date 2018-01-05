//
//  File_handler.hpp
//  Final_Project_Programming_Finance
//
//  Created by kirthika on 28/11/17.
//  Copyright © 2017 kirthika. All rights reserved.
//

#ifndef File_handler_h
#define File_handler_h

#pragma once
#include <stdio.h>
#include <iostream>
#include <map>
#endif /* File_handler_hpp */
#include "LinkedList_krishnamurthy.h"
struct transaction{
    
    std::string event;
    std::string compSymbol;
    int         number;
    double      princePerShare;
    double      TotalValue;
    std::string date;
    std::string time;
    
    
};
//Wrapper design pattern is used here. It is used so that the file handling operations are handled here and only an abstracted function call is required from the classes for the file handling functions.


//This class handles all the file related operations. Any file related operation is passed to this class.
class FileHandler{
    
public:
    
    static double                       getInitialCashBalanceFromFile();
    static void                         commitTransactionToFile(struct transaction currentTransaction);
    static void                         printHistory(bool cash);
    static void                         commitCurrentPortfolioAndBalance(double cashl,LinkedList list);
    static void                         setLinkedListFromFile(LinkedList *list);
    static double                       getValueFromFile(std::string fileName,std::string comName);
    static std::map<std::string,double> getValuesFromFileAsMap(std::string fileName);
    static void                         recordCashTransaction(double cashB);
    static void                         reset();
    static std::map<double,double>      getPortfolioMap();
    static void                         commitPortFolioValueToHistory(double portfolioValue);
};
