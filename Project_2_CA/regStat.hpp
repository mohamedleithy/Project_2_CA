//
//  regStat.hpp
//  Project_2_CA
//
//  Created by Mohamed Ellethy on 03/12/2021.
//

#ifndef regStat_hpp
#define regStat_hpp

#include "resvStation.hpp"

class regStat{
 
private:
    
    pair<int, string> regS[8];
    
public:
    
    
    
    
    regStat();
    void modifyRegS(int index, string S, int busyBit);

    pair<int, string> getRegStat(int index); 

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

#endif /* regStat_hpp */
