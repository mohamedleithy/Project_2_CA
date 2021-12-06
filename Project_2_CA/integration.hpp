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

class integration{
    
private:
    int clock;

public:
    
    integration();
    
    void issueInstructions(instQueue &q, resvStation rS[], regStat regS, regFile rf);
    
};

#endif /* integration_hpp */
