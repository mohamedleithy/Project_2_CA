//
//  dataMem.cpp
//  Project_2_CA
//
//  Created by Mohamed Ellethy on 02/12/2021.
//

#include "dataMem.hpp"



dataMem::dataMem(){
    
    for(int i=0; i<256; i++){
        
        Mem[i] = 0;
    
}
}
    
void dataMem::dataSetter(int address, int value){
        
    Mem[address] = value;
    
}
    
int dataMem::dataGetter(int address){
        
        
        
    return Mem[address];
        
        
}
