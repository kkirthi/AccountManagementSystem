//
//  File_handler.cpp
//  Final_Project_Programming_Finance
//
//  Created by kirthika on 28/11/17.
//  Copyright © 2017 kirthika. All rights reserved.
//

#include "File_handler_krishnamurthy.h"
#include <fstream>
#include <vector>
#include <time.h>
double FileHandler::getInitialCashBalanceFromFile(){
    //This function is to get the initial balance.
    std::ifstream data_file;
    data_file.open("Current_Portfolio.txt");
    if(data_file.good()){
        //std::cout<<"\nfile created";

    std::string name;
    std::string cashl;
    if(data_file.is_open()){
        //std::cout<<"\nIn opening file";

        while (data_file >> name) {
            if(name == "cash"){
            data_file >> cashl;
                break;
            }
        }
    }
        data_file.close();
        return stof(cashl);
        
    }
    else{
        //std::cout<<"In creating file";
        std::ofstream outfile ("Current_Portfolio.txt");
        
        outfile << "cash 10000" << std::endl;
        
        outfile.close();
        
        return 10000.00;
        
    }
    
    
}

void FileHandler::commitTransactionToFile(struct transaction currentTransaction){
    //this function is to commit the transaction to the file.
    std::fstream data_file;
    data_file.open("History_Transactions.txt",std::ios::ate||std::ios::out) ;
    if(data_file.good()){
       // std::cout<<"\nfile created";
        
        if(data_file.is_open()){
            data_file << currentTransaction.event <<" " <<currentTransaction.compSymbol <<" " <<currentTransaction.number <<" " <<currentTransaction.princePerShare<<" " << currentTransaction.TotalValue<<" " << currentTransaction.date<<" " << currentTransaction.time<<std::endl;
        }
        data_file.close();
        
    }
    else{
        //std::cout<<"In creating file";
        std::ofstream outfile ("History_Transactions.txt");
        
        outfile << currentTransaction.event <<" " <<currentTransaction.compSymbol <<" " <<currentTransaction.number <<" " <<currentTransaction.princePerShare<<" " << currentTransaction.TotalValue<<" " << currentTransaction.date<<" " << currentTransaction.time<<std::endl;
        
        outfile.close();
        
        
    }
}

void FileHandler::printHistory(bool cash){
    //This function is used to print history of transaction. cash is set means bank account.
    std::ifstream data_file;
    data_file.open("History_Transactions.txt");
    if(data_file.good()){
       // std::cout<<"\nfile created";
        struct transaction temp;
        
        if(data_file.is_open()){
            //std::cout<<"\n opening file\n";
            std::cout.width(10);
            std::cout<<std::left<<"Event";
            std::cout.width(11);
            std::cout<<std::left<<"CompSymbol";
            std::cout.width(9);
            std::cout<<std::left<<"Number";
            std::cout.width(16);
            std::cout<<std::left<<"PricePerShare";
            std::cout.width(13);
            std::cout<<std::left<<"TotalValue";
            std::cout.width(12);
            std::cout<<std::left<<"Date";
            std::cout.width(12);
            std::cout<<std::left<<"Time";
            std::cout<<std::endl;
            while (data_file >> temp.event) {
                data_file>>temp.compSymbol;
                data_file>>temp.number;
                data_file>>temp.princePerShare;
                data_file>>temp.TotalValue;
                data_file>>temp.date;
                data_file>>temp.time;
                if(!cash){
                    if(temp.compSymbol=="Cash")
                        continue;
                }
                std::cout.width(10);
                std::cout<<std::left<<temp.event;
                std::cout.width(11);
                std::cout<<std::left<<temp.compSymbol;
                if(temp.number == -1){
                    std::cout.width(9);
                    std::cout<<std::left<<"Nil";
                }
                else{
                std::cout.width(9);
                std::cout<<std::left<<temp.number;
                }if(temp.princePerShare == -1){
                    std::cout.width(16);
                    std::cout<<std::left<<"Nil";
                }
                else{
                    std::cout.width(16);
                    std::cout<<std::left<<temp.princePerShare;
                }
                std::cout.width(13);
                std::cout<<std::left<<temp.TotalValue;
                std::cout.width(12);
                std::cout<<std::left<<temp.date;
                std::cout.width(12);
                std::cout<<std::left<<temp.time;
                std::cout<<std::endl;

                
                }
            }
        data_file.close();
        
        
    }
    else{
        //std::cout<<"\nNo history available";
        
    }
    
    //std::cout<<"\nHistory printing done\n";
}
void resetFiles(){
    
    
    
}
void FileHandler::commitCurrentPortfolioAndBalance(double cashl,LinkedList list){
    
    std::ofstream data_file;
    data_file.open("Current_Portfolio.txt");
    if(data_file.good()){
       // std::cout<<"\nfile created";
        
        if(data_file.is_open()){
         // std::cout<<"\n opening file\n";
            data_file<<"cash"<<" "<<cashl<<std::endl;
            
        }
        
        Node * temp = list.getHead();
        while (temp!=NULL) {
            
            data_file<<temp->compSymbol<<" "<<temp->numberOfShares<<std::endl;
            
            temp = temp->next;
        }
    
        data_file.close();

    }
    else{
        //std::cout<<"\nError in commiting history";
    }
}

void FileHandler::setLinkedListFromFile(LinkedList *list){
    
    
    std::ifstream data_file;
    data_file.open("Current_Portfolio.txt");
    if(data_file.good()){
        //std::cout<<"\nfile created";
        
        
        if(data_file.is_open()){
            std::string name;
            std::string cashl;
            //std::cout<<"\nIn opening file";
            data_file>>name>>cashl;
            std::string compSymbol;
            std::string numberOfShares;
            while (data_file>>compSymbol) {
                // std::cout<<"\ninside insertion of nodes";
                data_file>>numberOfShares;
                
                Node newNode;
                
                newNode.numberOfShares = stoi(numberOfShares);
                newNode.compSymbol = compSymbol;
                list->insertNode(newNode);
                
            }
            
            
        }

        data_file.close();
        return;
        
    }
    
}
void FileHandler::recordCashTransaction(double cashB){
    
    //The structure object contains the neccesary deatils of the cash transaction
    struct Port{
        std::string compSym;
        int number;
    };
    std::vector<Port> v1;
    
    std::ifstream data_file;
    data_file.open("Current_Portfolio.txt");
    if(data_file.good()){
        if(data_file.is_open()){
            std::string name;
            std::string cashl;
            //std::cout<<"\nIn opening file";
            data_file>>name>>cashl;
            std::string compSymbol;
            std::string numberOfShares;
            while (data_file>>compSymbol) {
                
                data_file>>numberOfShares;
                
                Port port1;
                port1.number = stoi(numberOfShares);
                port1.compSym = compSymbol;
                v1.push_back(port1);
            }
        }
        data_file.close();
    }
    std::ofstream data_file1;
    data_file1.open("Current_Portfolio.txt");
    if(data_file1.good()){
       // std::cout<<"\nfile created";
        if(data_file1.is_open()){
           // std::cout<<"\n opening file\n";
            data_file1<<"cash"<<" "<<cashB<<std::endl;
        }
        int i = 0;
        while (i<v1.size()) {
            data_file1<<v1[i].compSym<<" "<<v1[i].number<<std::endl;
             i++;
        }
        data_file1.close();
    }
}
double FileHandler::getValueFromFile(std::string fileName, std::string comName){
    
    
    std::ifstream data_file;
    data_file.open(fileName);
    if(data_file.good()){
        
        std::string name;
        std::string comVal;
        std::string date;
        if(data_file.is_open()){
            
            while (data_file >> name) {
                if(name == comName){
                    //std::cout<<"\nIn the company name match";
                    data_file >> comVal;
                    data_file.close();

                    return stof(comVal);
                  }
                data_file >> comVal;
                data_file >> date;
            }
        }
        
    }

    return -1.0;
}

std::map<std::string,double>FileHandler::getValuesFromFileAsMap(std::string fileName){
    
    std::map<std::string,double> listStcok;
    
    std::ifstream data_file;
    data_file.open(fileName);
    if(data_file.good()){
        std::string name;
        std::string comVal;
        std::string date;
        if(data_file.is_open()){
            
            while (data_file >> name) {
                data_file >> comVal;
                listStcok[name] = stof(comVal);
                data_file >> date;
            }
        }
        data_file.close();
    }
  return listStcok;
}

std::map<double,double> FileHandler::getPortfolioMap(){
    //gets the portfolio value as a map.
    std::map<double,double> listStcok;
    
    std::ifstream data_file;
    data_file.open("Portfolio_History.txt");
    if(data_file.good()){
        //std::cout<<"\n data is good";
        std::string timSeconds;
        std::string  portfolio_value;
        if(data_file.is_open()){
            //std::cout<<"\n data is open";

            while (data_file >> timSeconds) {
                data_file >> portfolio_value;
                //std::cout<<"\n portfolio "<<portfolio_value;
                listStcok[stof(timSeconds)] = stof(portfolio_value);
            }
        }
        data_file.close();
    }
    else
        std::cout<<"file not good";
    return listStcok;
}


void FileHandler::commitPortFolioValueToHistory(double portfolioValue){
    //Commits the history of the porfolio values for the plot
    time_t timer;
    struct tm y2k = {0};
    double seconds;
    
    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
    
    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    
    seconds = difftime(timer,mktime(&y2k));
    
    //printf ("%.f seconds since January 1, 2000 in the current timezone", seconds);
    
    std::fstream data_file;
    data_file.open("Portfolio_History.txt",std::ios::ate||std::ios::out) ;
    if(data_file.good()){
        // std::cout<<"\nfile created";
        
        if(data_file.is_open()){
            data_file << seconds <<" " <<portfolioValue<<std::endl;
        }
        data_file.close();
        
    }
    else{
        //std::cout<<"In creating file";
        std::ofstream outfile ("Portfolio_History.txt");
        
        outfile << seconds <<" " <<portfolioValue<<std::endl;
        
        outfile.close();
        
        
    }

}

void FileHandler::reset(){
    //resets all the files. This is only for testing purpose.
    if(remove("Current_Portfolio.txt"))
        std::cout<<"\nRemove successfull ";
    if(remove("History_Transactions.txt"))
       std::cout<<"\nRemove successfull";
    if(remove("Portfolio_History.txt"))
        std::cout<<"\nRemove successfull";

    
    
    
}




