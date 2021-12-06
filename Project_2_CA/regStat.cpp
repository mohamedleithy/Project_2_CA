//
//  regStat.cpp
//  Project_2_CA
//
//  Created by Mohamed Ellethy on 03/12/2021.
//

#include "regStat.hpp"


regStat::regStat(){
    
    
    for(int i=0; i<8; i++){
        
        regS[i].first =0;
        regS[i].second = ""; 
        
    }
    
    
    
}



pair<int, string> regStat::getRegStat(int index){
    
    
    return regS[index];
    
    
    
}


void regStat::modifyRegS(int index, string S, int busyBit){
    
    regS[index].first = busyBit;
    regS[index].second = S;
    
}
