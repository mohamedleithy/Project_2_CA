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
    int branchCounter;
    int branchMissCounter;
    vector<wbQueue> writeBackQueue; //pair is value and address
    bool branchCame;
    bool jalCame;
   
    
    
public:
    
    integration();
    
    void issueInstructions(instQueue &q, resvStation rS[], regStat &regS, regFile &rf, vector<inst> &issued);
    
    void executeInstructions(instQueue &q ,resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem);
    
    wbQueue sortAndIssueWb(vector<wbQueue> writeBackQueue);
    
    void wB( resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem , int valueToWrite, int rd);
    
    
    void heapify(vector<wbQueue> &j, int n, int i);
    

    void build_heap(vector<wbQueue> &j);
  
    void heap_sort(vector<wbQueue> &j);
   
    void jal(instQueue &q, resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem , int valueToWrite, int rd, int clk, int imm, int ind);
    
    void branch(instQueue &q, resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem , int valueToWrite, int rd, int clk, int imm, int ind);

    
    
    
};

#endif /* integration_hpp */
