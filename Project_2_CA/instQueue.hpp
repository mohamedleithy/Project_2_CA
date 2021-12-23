//
//  instQueue.hpp
//  Project_2_CA
//
//  Created by Mohamed Ellethy on 02/12/2021.
//

#ifndef instQueue_hpp
#define instQueue_hpp
#include <string>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct inst{
    
    string instName;
    int rs1;
    int  rs2;
    int rd;
    int imm;
    int issueTime;
    int startExec;
    int endExec;
    int writeBack;
    int index; 
    
};

using namespace std;
class instQueue{

private:
    
    vector<inst> iQueue;
    int counter; 
public:
    
    instQueue();
    
    void parseInst(string filePath);
    
    inst getInstruction();
    
    void popInstruction();
    
    vector<inst> getQueue();
    
    void setQueue(vector<inst> q);
    
    
    void parseInstLabel(string filePath);
    
    

    
    
}; 
#endif /* instQueue_hpp */
