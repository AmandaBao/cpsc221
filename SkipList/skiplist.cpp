//This cpp file implements functions for SkipList and SkipNode Class

#include <iostream>
#include <stdlib.h>
#include "skiplist.hpp"
#include <cstdlib>
#include <ctime> 
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdio.h>
#define MAX_HEIGHT 7


//This is a constructor for SkipNode
SkipNode::SkipNode(std::string word,int Page,int height){
    
    //Initialize a skipnode
    //set the initial occurrance to 1,record the page number and keyword
    next = nullptr;
    rec = 1;
    Keyword = word;
    PageNum.push_back(Page);
    
    //When setting the first node,the height will be MAX_HEIGHT
    //if this is not the first Node,get a random height for this node
    //otherwise the height should be set to zero but the height will be updated here to get
    //a random value between 1-MAX_HEIGHT
    if(height == 0){
        level = randHeight();
    }else{
        level = height;
    }
    
    //intialize the UpperArray to be all NULL
    for(int index=0;index<level;index++){
        UpperArray.emplace_back(nullptr);
    }
   
    
    
}

//generate a random bit
int SkipNode::randBit(void){
    
        static int bitsUpperBd=0;
        static int bits;
        if( bitsUpperBd == 0 ) {
            
            bitsUpperBd = RAND_MAX;
            bits = rand();
        }
        int b = bits & 1;
        bits >>= 1;
        bitsUpperBd >>= 1;
        return b;
    
}

//generate a random bit
int SkipNode::randHeight(void){
    
    int h =1;
    int i;
    for( i=1; i<MAX_HEIGHT; ++i ) {
        if( randBit() == 1 ){
            break;
        }
    }
    h = i;
    return h;
}


SkipList::SkipList(){
    
    //make head points to the first node
    head = new SkipNode("head",NULL,MAX_HEIGHT);

}

/*destructor*/
SkipList::~SkipList () {
    
    delete head;

}

//Print the whole skipList
void SkipList::PrintInOrder(char* Name){
    
    std::ofstream myfile;
    myfile.open (Name);

    //tmp points to the first word-node in the skiplist
    SkipNode* tmp = head->UpperArray.at(0);
    //loop
    while (tmp!= nullptr){
        
        //Print the word and occurance
        myfile << tmp->Keyword;
        myfile << " ";
        myfile << "(" << tmp->rec << ")";
        myfile << " ";
        
        //Print the page number
        long size =tmp->PageNum.size();
        for(int j=0;(unsigned)j<size;j++){
            
            
            int temp = j;
            //Check if the page number is successive
            while(temp+1<size && (unsigned)tmp->PageNum[temp]+1 == tmp->PageNum[temp+1]){
                temp++;
            }
             
            if(j != temp){
                myfile<< tmp->PageNum[j];
                myfile<<"-";
                myfile<< tmp->PageNum[temp];
                j = temp;
                if(temp!=size-1){
                   myfile<< ",";
                }
            }
            //If No successive pagenumber,just print the single number
            else{
               myfile<< tmp->PageNum[j];
               if(temp!=size-1){
                    myfile<< ",";
               }
            }
        
            
            
        }
        
        myfile <<std::endl;
        tmp = tmp->UpperArray.at(0);
    }
    myfile.close();

    
}


//Find an Element in SkipList,return true or false
bool SkipList::Find(std::string word,int PageNumber){
    
    
    //found flag
    bool found = false;
    SkipNode* finder;
    finder = head;
    int n=MAX_HEIGHT-1;
    
    //traver the upperarray to find word
    while(n>=0 && finder != nullptr && !found){
        
        //If it points,go down to the lower level
        if(finder->UpperArray.at(n) == nullptr){
            
                       n--;
            
        }
        //If it points to a keyword that is larger than word,still go down to the lower level
        else if(finder->UpperArray.at(n)-> Keyword > word){
            
         
                       n--;
            
            
        }
        
        //If finder points to a smaller word,finder moves to that smaller word but remain in that level
        else if(finder->UpperArray.at(n)-> Keyword < word){
            
            finder = finder->UpperArray.at(n);

        }
        
        //none of above,means we have found the word
        else{
            
            //update the occurance
            finder->UpperArray.at(n)->rec++;
            //update the found flag to stop the while loop
            found = true;
            
            //update pagenumber,if that page is already in the list,do not push that number agai
            if(finder->UpperArray.at(n)->PageNum.back()!=PageNumber){
                finder->UpperArray.at(n)->PageNum.push_back(PageNumber);
            }
        }
        
    }
    return found;
}

//insert an a new SkipNode into the SkipList
void SkipList::Insert(std::string word,int PageNumber){
    
    int n=MAX_HEIGHT-1;
    
    SkipNode* finder=head;
    
    SkipNode* newNode = new SkipNode(word,PageNumber,0);
    
    //A vector to keep record of changed pointers
    std::vector<SkipNode*> Update(head->UpperArray.size());
    
    while(n>=0 && finder != nullptr){
        
        
        //finder points to null ,move the lower level
        if(finder->UpperArray.at(n) == nullptr){
            
            Update[n]=finder;
            n--;
            
        }
        
        //found a keyword larger than word,move to the lower level
        else if(finder->UpperArray.at(n)-> Keyword > word){
            
            Update[n]=finder;
            n--;

            
        }
        
        else
        {
            //found a keyword smaller than word,move to that node and remain in the same level
            finder = finder->UpperArray.at(n);
            Update[n]=finder;

        }
        
    }
    

    
    //update the connections between newnode and oldnodes
    for(int index=0;index < newNode->level;index++){
        
        newNode->UpperArray.at(index) = Update.at(index)->UpperArray.at(index);
        Update.at(index)->UpperArray.at(index)= newNode;
    }
    
    
    
}
    
    
    
    
    
    
    
    
    
    
    
    
    


