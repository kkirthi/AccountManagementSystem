//
//  LinkedList.cpp
//  Final_Project_Programming_Finance
//
//  Created by kirthika on 28/11/17.
//  Copyright © 2017 kirthika. All rights reserved.
//

#include "LinkedList_krishnamurthy.h"



bool LinkedList::instanceFlag = false;
LinkedList* LinkedList::list = NULL;
LinkedList* LinkedList::getInstance()
{
    if(! instanceFlag)
    {
        list = new LinkedList();
        instanceFlag = true;
        return list;
    }
    else
    {
        return list;
    }
}
LinkedList::LinkedList(){
    
    head = NULL;
    tail = NULL;
    count = 0;
};
void LinkedList::insertNode(Node node){
    Node* temp = new Node();
    temp->compSymbol = node.compSymbol;
    temp->numberOfShares = node.numberOfShares;
    
    if(head == NULL){
        
        head = temp;
        tail = temp;
        
        head->next = NULL;
        head->previous = NULL;
        
        
        tail->next = NULL;
        tail->previous = NULL;
        
        
        count++;
        
    }
    else{
        Node *temptraversal;
        temp->next = NULL;
        temptraversal = head;
        while (temptraversal->next!=NULL) {
        temptraversal = temptraversal->next;
     }
        temptraversal->next = temp;
        temp->previous = temptraversal;
        tail = temp;
        
    }
}


void LinkedList::deleteNode(std::string compSymbol1){
    
    Node * temp = head;
    while (temp->compSymbol != compSymbol1) {
        temp = temp->next;
    }
        if(temp == head){
            if(temp->next!=NULL){
             head = temp ->next;
             head->previous = NULL;
            
        }
            else{
                head = NULL;
                tail = NULL;
            }
    }
        else{
            if(temp == tail){
                tail = temp->previous;
                tail->next = NULL;
            
            }
            
            else{
                
                temp->previous->next = temp ->next;
                temp->next->previous = temp->previous;
                
            }
        }
    delete temp;
}

int LinkedList::getNumberOfShares(std::string compSymbol1){
    
    Node * temp;
    temp = head;
    if(temp==NULL)
        return -1;
    while (temp->compSymbol!=compSymbol1) {
        temp = temp->next;
    }
    if(temp!=NULL)
     return temp->numberOfShares;
    else
     return -1;
    
}


Node* LinkedList::getHead(){
    
    return head;
}

void LinkedList::selectionSort(std::map<std::string, double> priceStock){
    

    Node *temp1,*temp2;
    
    if(head == NULL)
        return;
    if(head ->next == NULL)
        return;
    
    temp1 = head;
    
    while (temp1!=NULL) {
        Node *ttemp = temp1;
        temp2 = temp1->next;
        while (temp2!=NULL) {
            if(temp2->numberOfShares*priceStock[temp2->compSymbol]>temp1->numberOfShares*priceStock[temp1->compSymbol])
            {
                swapNode(&temp1, &temp2);
                ttemp = temp2;
                temp2 = temp1->next;
                temp1 = ttemp;
            
            }
            else
                temp2 = temp2->next;
            
        }
        temp1 = ttemp->next;
    
    
}
}


double LinkedList::getTotalPortfolioValue(std::map<std::string, double> priceStock){
    double total = 0.0;
    Node *temp = head;
    while (temp!=NULL) {
        total = total+ temp->numberOfShares*priceStock[temp->compSymbol];
        temp = temp->next;
    }
    return total;
    
    
}



void LinkedList::addChangesToPortfolio(std::string compSymbol, int newDiff){
    Node * temp;
    temp = head;
    if(temp == NULL){

        Node newNode = {compSymbol,newDiff};
        insertNode(newNode);
        return;

    }
        
    while (temp!=NULL) {
        if(temp->compSymbol == compSymbol)
            break;
        temp = temp->next;
    }
    if(temp == NULL&&newDiff>0){
        Node newNode = {compSymbol,newDiff};
        
        insertNode(newNode);
        return;
        
    }else{
    temp->numberOfShares = temp->numberOfShares + newDiff;
    if(temp->numberOfShares<=0){
        deleteNode(compSymbol);
    }
    }
}

void LinkedList::setHead(Node * nd){
    head = nd;
}

void LinkedList::setTail(Node *nd){
    tail = nd;
}

Node* LinkedList::getTail(){
    return tail;
}


int LinkedList::getCount(){
    return count;
}

void LinkedList::setCount(int cn){
    count  = cn;
}

void LinkedList::printList(std::map<std::string, double> priceStock)
{
    if(head == NULL){
        std::cout<<"\nThe portfolio is empty.\n";
    return;
    }
    std::cout<<"\n";
    std::cout.width(11);
    std::cout<<std::left<<"CompSymbol";
    std::cout.width(9);
    std::cout<<std::left<<"Number";
    std::cout.width(16);
    std::cout<<std::left<<"PricePerShare";
    std::cout.width(13);
    std::cout<<std::left<<"TotalValue";
    std::cout.width(12);
    std::cout<<std::endl;
    
    Node * temp = head;
    
    while (temp!=NULL) {
        std::cout.width(11);
        std::cout<<std::left<<temp->compSymbol;
        
           std::cout.width(9);
            std::cout<<std::left<<temp->numberOfShares;
       
            std::cout.width(16);
            std::cout<<std::left<<priceStock[temp->compSymbol];
        std::cout.width(13);
        std::cout<<std::left<<temp->numberOfShares*priceStock[temp->compSymbol];
        std::cout<<"\n";
        temp = temp->next;

        }

    
    
    
}

void LinkedList::insertinSort(std::map<std::string, double> priceStock){
    Node *temp1;
    Node *temp2;
    if(head == NULL)
        return;
    if(head->next == NULL)
        return;
    temp1 = head->next;

    while (temp1!=NULL) {
        Node *ttemp = temp1;
        bool flag = true;
        double totalValue = temp1->numberOfShares*priceStock[temp1->compSymbol];
       // std::cout<<"\ntotal value "<<totalValue<<" "<<temp1->compSymbol;

        temp2 = temp1 ->previous;
            while(temp2->numberOfShares*priceStock[temp2->compSymbol]<totalValue){
                if(flag)
                ttemp = temp2;
                flag = false;
                if(temp1 == tail){
                    temp1->previous->next = NULL;
                    tail = temp1->previous;
                }
                else{
                    temp1 ->previous->next = temp1->next;
                    temp1->next->previous = temp1->previous;
                }
                
                if(temp2 == head){
                    head = temp1;
                    temp1->next = temp2;
                    temp2->previous= temp1;
                    temp1->previous = NULL;
                
                }
                else{
                    temp2->previous->next = temp1;
                    temp1->next = temp2;
                    temp1->previous = temp2->previous;
                    temp2->previous = temp1;
                    
                }
                
                temp2 = temp1->previous;
                if(temp2 ==NULL){
                    //std::cout<<"\n Null break;";
                    break;
                }
            
        }
        temp1 = ttemp -> next;
        //std::cout<<"\nAfter iteration 1 "<<temp1->compSymbol;
    }
}

void LinkedList::bubblesortList(std::map<std::string, double> priceStock){
    
    //bubbleSort
    
    Node *temp1 ;
    Node *temp2 ;
    Node *temp3;
    temp1 = head;
    if(head == NULL)
        return;
    
    while (temp1!=NULL) {
        if(temp1->next == NULL)
            break;
        temp2 = head;
        while (temp2!=NULL) {
            temp3 = temp2->next;
             if(temp3==NULL)
                 break;
            
             if(temp2->numberOfShares*priceStock[temp2->compSymbol]<temp3->numberOfShares*priceStock[temp3->compSymbol])
             {
                 //swap temp2 and temp3
                 swapNode(&temp2, &temp3);
                 temp2 = temp2->previous;
               
        }
            temp2=temp2->next;
        }
        
        temp1 = temp1->next;
    }
    

}
void LinkedList::swapNode(Node **temp1p, Node **temp2p){
    Node *temp2 = *temp1p;
    Node *temp3 = *temp2p;
    
    Node *tempSwapPrev,*tempSwapNext;
    tempSwapPrev = temp3->previous;
    tempSwapNext = temp3->next;
   
    if(temp2==head){
        temp3->previous = NULL;
        head = temp3;
        if(temp2->next == temp3){
            temp3->next = temp2;
        }
        else{
        temp3->next = temp2->next;
        temp2 ->next->previous = temp3;
        }
        
    }
    else{
        temp3 ->previous = temp2->previous;
        if(temp2->next==temp3){
        temp3->next = temp2;
            
        }
        else{
            temp3->next = temp2->next;
            temp2->next->previous = temp3;

        }
        temp2->previous->next = temp3;

        }
    
    if(temp3==tail){
        tail = temp2;
        temp2->next = NULL;
        if(tempSwapPrev == temp2){
            temp2->previous = temp3;
        }
        else{
            tempSwapPrev->next = temp2;
            temp2->previous = tempSwapPrev;
            
        }
    }
    else{
        if(tempSwapPrev == temp2){
            temp2->previous = temp3;
            temp2->next = tempSwapNext;
            tempSwapNext ->previous = temp2;
        }
        else{
            temp2->previous = tempSwapPrev;
            temp2->next = tempSwapNext;
            tempSwapNext->previous = temp2;
            tempSwapPrev->next = temp2;

        }
    }
}

LinkedList::~LinkedList(){
    instanceFlag = false;
}
