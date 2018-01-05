//
//  StockAccount.cpp
//  Final_Project_Programming_Finance
//
//  Created by kirthika on 28/11/17.
//  Copyright © 2017 kirthika. All rights reserved.
//

#include "StockAccount_krishnamurthy.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"
#include <map>

StockAccount::StockAccount(){
    list = LinkedList::getInstance();
    
    FileHandler::setLinkedListFromFile(list);
    
    //list.printList(FileHandler::getValuesFromFileAsMap("/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_1.txt"));
    
}

void StockAccount::displayValueOfStock(){
    //funcition to display thr value of stck.
    std::string stockName;
    std::cout<<"\nEnter the symbol of the company:";
    std::cin>>stockName;
    int ran = rand()%1;//random number decides which file to use.
    std::string fileName;
    fileName = ran == 0?"/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_1.txt":"/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_2.txt";
    double stockPrice = FileHandler::getValueFromFile(fileName, stockName);
    if(stockPrice == -1)
        std::cout<<"\nError Symbol not found";
    else
    std::cout<<"\nThe value is "<<stockPrice<<"\n";
    
}


void StockAccount::displayCurrentPortfolio(){
    //to display the current potfolio
    int ran = rand()%2;
    std::string fileName;
    fileName = ran == 0?"/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_1.txt":"/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_2.txt";
    //random number decides which file to use.
    
    std::cout<<"Enter your choice of sorting the stocks:\n1.Bubble Sort.\n2.Selection Sort.\n3.Insertion Sort\n";
    int choice;
    std::cin>>choice;
    while (choice>3||choice<1) {
        std::cout<<"\nEnter a valid choice\n";
        std::cin>>choice;
    }
    std::map<std::string,double> listStock = FileHandler::getValuesFromFileAsMap(fileName);//template design pattern. Map is used to pair the key and values in the results file. File handler packs it and sends it as a map.

    switch (choice) {
        case 1:
            list->bubblesortList(listStock);
            break;
        case 2:
            list->insertinSort(listStock);
        case 3:
            list->selectionSort(listStock);
            
        default:
            break;
    }
    
    
    
    std::cout<<"\nCash Balance = "<<"$"<<cashBalance;
    
    list->printList(listStock);
    
    std::cout<<"Total Portfolio Value = "<<list->getTotalPortfolioValue(listStock)+cashBalance<<"\n";
    
}

void StockAccount::buyShares(){
    //to buy shares.
    std::string comName;
    int number;
    double price;
    std::cout<<"\nEnter the company symbol";
    std::cin>>comName;
    int ran = rand()%2;
    std::string fileName;
    fileName = ran == 0?"/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_1.txt":"/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_2.txt";

    price = FileHandler::getValueFromFile(fileName, comName);
    if(price == -1.0){
        std::cout<<"\nCompany not found.";
        return;
    }
    std::cout<<"\nEnter the number of shares you want to buy: ";
    std::cin>>number;
    std::cout<<"\nEnter the total value you are willing to spend a share: ";
    double maxAllowed;
    std::cin>>maxAllowed;
    if(maxAllowed<price)
    {
        std::cout<<"\nThe price of the share is greater than the amout you are ready to spare";
        return;
    }
    
    std::cout<<"\nThe value of each share is "<<price<<" and total value is "<<number*price;
    
    if(cashBalance >= number*price){
        
        std::cout<<"\nBuy successful";
        cashBalance = cashBalance - number*price;
        list->addChangesToPortfolio(comName, number);
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        
        std::string date = std::to_string(now->tm_mon+1)+"/"+std::to_string(now->tm_mday)+"/"+std::to_string(now->tm_year+1900);
        std::string time = std::to_string(now->tm_hour)+":"+std::to_string(now->tm_min)+":"+std::to_string(now->tm_sec);
        
        
        struct transaction trans={"Buy",comName,number,price,price*number,date,time};
        FileHandler::commitTransactionToFile(trans);
        FileHandler::commitCurrentPortfolioAndBalance(cashBalance, *list);
        list->bubblesortList(FileHandler::getValuesFromFileAsMap(fileName));
    }
    else{
        std::cout<<"\nSufficient funds not available";

    }
    
        
    
}
void StockAccount::readBalance(){
    cashBalance = FileHandler::getInitialCashBalanceFromFile();
}
void StockAccount::sellShares(){
    
    std::string comName;
    int number;
    std::cout<<"\nEnter the company symbol";

    std::cin>>comName;
    double price;
    int ran = rand()%2;
    std::string fileName;
    fileName = ran == 0?"/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_1.txt":"/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_2.txt";
    
    price = FileHandler::getValueFromFile(fileName, comName);
    if(price == -1.0){
        std::cout<<"\nCompany not found.";
        return;
    }
    std::cout<<"\nEnter the minimum value you are willing to sell a share: ";
    double minAllowed;
    std::cin>>minAllowed;
    if(minAllowed>price)
    {
        std::cout<<"\nThe price of the share is lesser than the minimum amout ";
        return;
    }

    std::cout<<"\nEnter the number of shares you want to sell: ";
    std::cin>>number;

    std::cout<<"\nThe value of each share is "<<price<<" and total value of the share in portfolio is "<<number*price;
    
    if(list->getNumberOfShares(comName) >= number){
        
        std::cout<<"\nSell successful";
        cashBalance = cashBalance + number*price;
        list->addChangesToPortfolio(comName, -number);
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        
        std::string date = std::to_string(now->tm_mon+1)+"/"+std::to_string(now->tm_mday)+"/"+std::to_string(now->tm_year+1900);
        std::string time = std::to_string(now->tm_hour)+":"+std::to_string(now->tm_min)+":"+std::to_string(now->tm_sec);
        
        std::cout<<"\ndate "<<date;
        struct transaction trans={"Sell",comName,number,price,price*number,date,time};
        FileHandler::commitTransactionToFile(trans);
        FileHandler::commitCurrentPortfolioAndBalance(cashBalance, *list);

    }
    else{
        std::cout<<"\nSufficient shares not available";
    }
    list->bubblesortList(FileHandler::getValuesFromFileAsMap(fileName));
   
    
    
    
}

void StockAccount::viewAGraph(){
    
        // pointer to the engine
    std::map<double,double> lstPortfolio;
    lstPortfolio = FileHandler::getPortfolioMap();
    int ran = rand()%2;
    std::string fileName;
    fileName = ran == 0?"/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_1.txt":"/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_2.txt";
    std::map<std::string,double> listStock = FileHandler::getValuesFromFileAsMap(fileName);
    
    
    int count = (int)lstPortfolio.size() + 1;
    double currentValue = cashBalance+ list->getTotalPortfolioValue(listStock);
    time_t timer;
    struct tm y2k = {0};
    double seconds;
    
    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
    
    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    
    seconds = difftime(timer,mktime(&y2k));
    double portfolio_val[count];
    int i = 0;
    for(std::map<double,double>::iterator it = lstPortfolio.begin(); it != lstPortfolio.end(); ++it) {
        portfolio_val[i++] = it->second;
        
        
    }
    portfolio_val[i] = currentValue;
        Engine *N;
        N = engOpen("/Applications/MATLAB_R2016b.app/bin/./matlab");
        // if matlab engine is not opened.
        if (N == NULL)
        {
            std::cout << "Error." << std::endl;
            exit(1);
        }
                std::cout << "\n Plotting MATLAB graph. Please wait...";
        mxArray *M;
        M = mxCreateDoubleMatrix(1, count, mxREAL); // creat a matrix
        memcpy((void *)mxGetPr(M), (void *)portfolio_val, count * sizeof(double)); // allocate memory space
        engPutVariable(N, "set", M);
        engEvalString(N, "plot(set);"); // plot the value
        engEvalString(N, "title('Change In Portfolio Value');");
        mxDestroyArray(M);// deallocate matrix M
    
}
void StockAccount::savePortfolioHistory(){
    int ran = rand()%2;
    std::string fileName;
    fileName = ran == 0?"/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_1.txt":"/Users/kirthika/Desktop/Inclass-9/Final_Project_Programming_Finance/Final_Project_Programming_Finance/Result_2.txt";
    std::map<std::string,double> listStock = FileHandler::getValuesFromFileAsMap(fileName);

    double currentValue = cashBalance+ list->getTotalPortfolioValue(listStock);
    FileHandler::commitPortFolioValueToHistory(currentValue);
    
}
void StockAccount::transactionHistory(){
    FileHandler::printHistory(false);
}

void StockAccount::commitPortfolio(){
    FileHandler::commitCurrentPortfolioAndBalance(cashBalance,*list);
}

