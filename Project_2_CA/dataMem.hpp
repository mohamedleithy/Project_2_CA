//
//  dataMem.hpp
//  Project_2_CA
//
//  Created by Mohamed Ellethy on 02/12/2021.
//


#ifndef dataMem_hpp
#define dataMem_hpp

#include <stdio.h>


class dataMem{


private:
    
    
    int Mem[10000];
    
    
    
    
public:
    
    
    
    dataMem();
    void dataSetter(int address, int value);
    int dataGetter(int address);
    
    
    
    
    
    
    
    
    
};






#endif /* dataMem_hpp */
