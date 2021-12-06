//
//  regFile.hpp
//  Project_2_CA
//
//  Created by Mohamed Ellethy on 06/12/2021.
//

#ifndef regFile_hpp
#define regFile_hpp

#include <stdio.h>

class regFile{
    
private:
 
    
    int regF[8];
    
    
    
    
public:
    
    
    regFile();
    void setRegFile(int value, int address);
    int getRegFile(int address);
    
    
};

#endif /* regFile_hpp */
