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
    int resvNum;
    int inst; 
    
};

class integration{

private:
    int clock;
    int branchCounter;
    int instIndex;
    int branchMissCounter;
    vector<wbQueue> writeBackQueue; //pair is value and address
    bool branchCame;
    bool jalCame;
    
   
    
    
public:
    
    integration();
    
    void issueInstructions(instQueue &q, resvStation rS[], regStat &regS, regFile &rf, vector<inst> &issued);
    
    void executeInstructions(instQueue &q , instQueue &p, resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem);
    
    wbQueue sortAndIssueWb(vector<wbQueue> writeBackQueue);
    
    void wB( resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem , int valueToWrite, int rd, int resvNum);
    
    
    void heapify(vector<wbQueue> &j, int n, int i);
    

    void build_heap(vector<wbQueue> &j);
  
    void heap_sort(vector<wbQueue> &j);
   
    void jal(instQueue &q, instQueue &p, resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem , int valueToWrite, int rd, int clk, int imm, int ind);
    
    void branch(instQueue &q, instQueue &p, resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem , int valueToWrite, int rd, int clk, int imm, int ind);

    void recoverQueue(instQueue &q, instQueue &pm, int index, int imm);
    
    bool checkExit(instQueue &q, resvStation rS[]);
    
    void printStats(vector<inst> &issued, int clock);
    
    void sW( dataMem &mem, int value, int add);
    
    
    
};

#endif /* integration_hpp */
