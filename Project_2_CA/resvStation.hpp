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
    int qj;
    int qk;
    int a;
    
public:
    
    resvStation();
    
    void setBusy(bool);
    bool getBusy();
    
    void setName(string);
    string getName();
    
    
    void setOp(char);
    char getOp();
    
    void setVj(int);
    int getVj();
    
    
    void setVk(int);
    int getVk();
    
    
    
    void setQj(int);
    int getQj();
    
    
    
    void setQk(int);
    int getQk();
    
    
    
    void setA(int);
    int getA();
    
    
    
    
    
    
    
    
    
    
    
    
    
}; 





#endif /* resvStation_hpp */
