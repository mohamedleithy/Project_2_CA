//
//  resvStation.hpp
//  Project_2_CA
//
//  Created by Mohamed Ellethy on 02/12/2021.
//

#ifndef resvStation_hpp
#define resvStation_hpp

#include <iostream>

using namespace::std;

#include <stdio.h>

class resvStation{


private:
    string name; 
    bool busy;
    char op;
    int vj;
    int vk;
    string qj;
    string qk;
    int a;
    int clock;
    int imm;
    int rd;
    int startExec;
    int endExec;
    int ind; 
    
    
public:
    
    resvStation();
    
    void setBusy(bool);
    bool getBusy();
    void flush(string name); 
    
    void setName(string);
    string getName();
    
    
    void setOp(char);
    char getOp();
    
    void setVj(int);
    int getVj();
    
    
    void setVk(int);
    int getVk();
    
    
    
    void setQj(string);
    string getQj();
    
    
    
    void setQk(string);
    string getQk();
    
    
    
    void setA(int);
    int getA();
    
    
    void setClock(int clock);
    int getClock();
    
    void setImm(int imm);
    int getImm();
    
    
    
    void setRd(int rd);
    int getRd();
    
    
    
    void setStartExec(int startExec);
    int getStartExec();
    
    
    
    void setEndExec(int endExec);
    int getEndExec();
   
    void setIndex(int i);
    int getIndex();
    
    
    

    
    
}; 





#endif /* resvStation_hpp */
