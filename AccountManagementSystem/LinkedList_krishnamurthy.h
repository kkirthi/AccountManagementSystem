//
//  LinkedList.hpp
//  Final_Project_Programming_Finance
//
//  Created by kirthika on 28/11/17.
//  Copyright © 2017 kirthika. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h
#pragma once
#include <stdio.h>
#include <iostream>
#include <map>
#endif /* LinkedList_hpp */
struct Node{
    std::string compSymbol;
    int numberOfShares;
    Node* previous;
    Node* next;
};
class LinkedList{
    
    Node* head;
    Node* tail;
    int count;
    
    
private:
    static bool instanceFlag;//Singleton design pattern. Only one instance of linkedlist is need to keep it in sync. Hence Singleton designpattern is used.
    static LinkedList *list;
    LinkedList();
    void deleteNode(std::string compSymbol);
    void swapNode(Node** temp1p,Node **temp2p);

    
public:
    static LinkedList* getInstance();
    void method();
    ~LinkedList();
    Node* getHead();
    void setHead(Node * nd);
    Node* getTail();
    int getCount();
    void setCount(int cn);
    void setTail(Node *nd);
    void addChangesToPortfolio(std::string compSymbol,int newDiff);
    void printList(std::map<std::string, double> priceStock);
    int getNumberOfShares(std::string compSymbol1);
    void insertNode(Node node);
    double getTotalPortfolioValue(std::map<std::string, double> priceStock);
    void bubblesortList(std::map<std::string, double> priceStock);
    void selectionSort(std::map<std::string, double> priceStock);
    void insertinSort(std::map<std::string, double> priceStock);
     
    
};
