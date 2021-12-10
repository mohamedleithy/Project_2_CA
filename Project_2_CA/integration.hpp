//
//  integration.hpp
//  Project_2_CA
//
//  Created by Mohamed Ellethy on 06/12/2021.
//

#ifndef integration_hpp
#define integration_hpp

#include <stdio.h>
#include "dataMem.hpp"
#include "instQueue.hpp"
#include "dataMem.hpp"
#include "regStat.hpp"
#include "regFile.hpp"
#include "t.hpp"





struct wbQueue{

    int value;
    int index;
    int clock;
    
};

class integration{

private:
    int clock;
   
    vector<wbQueue> writeBackQueue; //pair is value and address
    
    
public:
    
    integration();
    
    void issueInstructions(instQueue &q, resvStation rS[], regStat &regS, regFile &rf, vector<inst> &issued);
    
   
    
    void executeInstructions( resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem);
    
    
    
    
    void wB( resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem , int valueToWrite);
    
    
    
    
};

#endif /* integration_hpp */
