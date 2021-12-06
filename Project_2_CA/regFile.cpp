//
//  regFile.cpp
//  Project_2_CA
//
//  Created by Mohamed Ellethy on 06/12/2021.
//

#include "regFile.hpp"
regFile::regFile(){
    
    for(int i=0; i<8; i++){
        
        regF[i] = 0;
    
    }
    
    
}
void regFile::setRegFile(int value, int address){
    
    
    
    if(address!=0){
        
        regF[address] = value;
        
        
    }
    
    
}
int regFile::getRegFile(int address){
    
    return regF[address];

}
