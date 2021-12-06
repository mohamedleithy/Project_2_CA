//
//  integration.cpp
//  Project_2_CA
//
//  Created by Mohamed Ellethy on 06/12/2021.
//

#include "integration.hpp"


integration::integration(){
    
    //integration of our "computer"
    
    clock = 0; 
    dataMem mem;
    instQueue q;
    q.parseInst("empty");
    regStat rS;
    regFile rf;
    resvStation resvStations[12];
    
    vector<inst> Done;
    
    resvStations[0].setName("Lw1");
    resvStations[1].setName("Lw2");
    resvStations[2].setName("Sw1");
    resvStations[3].setName("Sw2");
    resvStations[3].setName("BEQ1");
    resvStations[5].setName("J1");
    resvStations[6].setName("ADD1");
    resvStations[7].setName("ADD2");
    resvStations[8].setName("ADD3");
    resvStations[9].setName("NEG1");
    resvStations[10].setName("ABS1");
    resvStations[11].setName("DIV1");
    
    
    
    
    
    
    
    //start
    
    
    
    while(1){
        
     issueInstructions( q, resvStations, rS, rf);
        
        clock++; 
    }
    
}


void integration::issueInstructions(instQueue &q, resvStation rS[], regStat regS, regFile rf){
    
    
    
    inst i = q.getInstruction();
    
    if(i.instName=="LW"){
        
        if(rS[0].getBusy()==false){
            rS[0].setBusy(true);
            rS[0].setOp('l');
            if(regS.getRegStat(i.rs1).first==0){
                rS[0].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rs1, "LW1", 1);
                q.popInstruction();
                
            }
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[0].setQj(i.rs1);
                q.popInstruction();
                
            }
            
        }
        
        else if(rS[1].getBusy()==false){
            rS[1].setBusy(true);
            rS[1].setOp('l');
            if(regS.getRegStat(i.rs1).first==0){
                rS[1].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rs1, "LW1", 1);
                q.popInstruction();
            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[1].setQj(i.rs1);
                q.popInstruction();
            }
        }
    
    }
    
    else if(i.instName=="SW"){
        
        
        
        
   
        
        
    }
    
    else if(i.instName=="BEQ"){
        
       
        
       
        
    }
    
    
    else if(i.instName=="JAL"){
        

    
        
        
        
        
    }
    else if(i.instName=="JALR"){
        
     
        
        
        
        
        
    }
    else if(i.instName=="ADD"){
        
      
        
        
        
        
        
    }
    else if(i.instName=="ADDI"){
        
        
        
        
        
        
        
    }
    else if(i.instName=="NEG"){
        
        
        
        
        
        
        
    }
    else if(i.instName=="ABS"){
        
        
        
        
        
        
        
    }
    
    else if(i.instName=="DIV"){
        
        
        
    }
    
    
}
