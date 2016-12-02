#include <iostream>
#include <vector>
#include <stdio.h>
#include <iostream>
#pragma once

class SkipNode{
    
public:
    //constructor
    SkipNode(std::string key,int Page,int height);
    
    
    std::string Keyword;
    int level;
    int rec;
    
    SkipNode* next;
    std::vector<int> PageNum;
    std::vector<SkipNode*> UpperArray;
    
    
private:
    int randBit(void);
    int randHeight(void);
    
    
};

class SkipList{
    
private:
    
    SkipNode* head;

public:
    
 
    SkipList(void);
    ~SkipList(void);
    void PrintInOrder(char*);
    void Insert(std::string word,int PageNumber);
    bool Find(std::string word,int PageNumber);
        
    
};