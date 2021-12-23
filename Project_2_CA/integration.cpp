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
    instQueue p;
    q.parseInstLabel("empty");
    p.parseInstLabel("empty");
    regStat rS;
    regFile rf;
    instIndex = 0;
    resvStation resvStations[12];
    
    vector<inst> issued;
    
    mem.dataSetter(0, 0);
    mem.dataSetter(1, 1);
    mem.dataSetter(2, 2);
    mem.dataSetter(3, 3);
    mem.dataSetter(4, 4);
    mem.dataSetter(5, 5);
    mem.dataSetter(6, 6);
    mem.dataSetter(7, 7);
    mem.dataSetter(32, 8);
    mem.dataSetter(44, 7);
    
    
    rf.setRegFile(44, 6);
    rf.setRegFile(1, 1);
    rf.setRegFile(1, 2);
    rf.setRegFile(1, 3);
    rf.setRegFile(44, 6);
    rf.setRegFile(4, 1);
    rf.setRegFile(0, 2);
    
    resvStations[0].setName("LW1");
    resvStations[1].setName("LW2");
    resvStations[2].setName("SW1");
    resvStations[3].setName("SW2");
    resvStations[4].setName("BEQ1");
    resvStations[5].setName("JAL");
    resvStations[6].setName("ADD1");
    resvStations[7].setName("ADD2");
    resvStations[8].setName("ADD3");
    resvStations[9].setName("NEG1");
    resvStations[10].setName("ABS1");
    resvStations[11].setName("DIV1");
    
    
    
    
    
    
    
    //start
    
    
    
    while(1){
        
        if(q.getQueue().size()!=0){
     issueInstructions( q, resvStations, rS, rf, issued);
        }
       
    executeInstructions( q, p, resvStations, rS, rf, issued, mem);

        
    
     wbQueue b =  sortAndIssueWb(writeBackQueue);
        if(writeBackQueue.size()!=0){
        issued[b.inst].writeBack = clock+1;
        wB(resvStations,rS, rf, issued, mem, b.value, b.index, b.resvNum);
            writeBackQueue.erase(writeBackQueue.begin());
        }
        
        if(q.getQueue().size()==0){
        if(checkExit(q, resvStations)&&(clock!=0)){
            goto term;
        }
        }
        
        clock++;
        
    
    }
    
    
    
term:
    
    
    printStats(issued, clock);
    
    return;
    
    
    
    
}



//issueing only

void integration::issueInstructions(instQueue &q, resvStation rS[], regStat &regS, regFile &rf, vector<inst> &issued){
    
    
    
    inst i = q.getInstruction();
    
    
    //LW requires rd rs1 and add
    // there are two reservation stations for LW
    // which are rS[0] and rS[1]
    
    if(i.instName=="LW"){
    
        if(rS[0].getBusy()==false){
            rS[0].setBusy(true);
            rS[0].setOp('l');
            rS[0].setIndex(instIndex);
            instIndex++;
            if(regS.getRegStat(i.rs1).first==0){
                rS[0].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "LW1", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[0].setClock(clock);
                i.index = rS[0].getIndex();
                issued.push_back(i);
                rS[0].setImm(i.imm);
                rS[0].setRd(i.rd);
                
                rS[0].setStartExec(-1);
                
            }
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[0].setQj(regS.getRegStat(i.rs1).second);
                regS.modifyRegS(i.rd, "LW1", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[0].setClock(clock);
                i.index = rS[0].getIndex();
                issued.push_back(i);
                rS[0].setImm(i.imm);
                rS[0].setRd(i.rd);
                rS[0].setStartExec(-1);
                
            }
            
        }
        
        else if(rS[1].getBusy()==false){
            rS[1].setBusy(true);
            rS[1].setOp('l');
            rS[1].setIndex(instIndex);
            instIndex++;
            if(regS.getRegStat(i.rs1).first==0){
                rS[1].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "LW2", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[1].setClock(clock);
                i.index = rS[1].getIndex();
                issued.push_back(i);
                rS[1].setImm(i.imm);
                rS[1].setRd(i.rd);
                
                rS[1].setStartExec(-1);
            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[1].setQj(regS.getRegStat(i.rs1).second);
                regS.modifyRegS(i.rd, "LW2", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[1].setClock(clock);
                i.index = rS[1].getIndex();
                issued.push_back(i);
                rS[1].setImm(i.imm);
                rS[1].setRd(i.rd);
              
                rS[1].setStartExec(-1);
            }
        }
    
    }
    
    
    //sw requires rs1 rs2 and add
    // reservation stations for SW are rS[2] and rS[3]
    
    
    else if(i.instName=="SW"){
        
        
        
        //rS[2] check
        
        
        
        if(rS[2].getBusy()==false){
            rS[2].setBusy(true);
            rS[2].setOp('s');
            rS[2].setIndex(instIndex);
            instIndex++;
            if(regS.getRegStat(i.rs1).first==0){
                rS[2].setVj(rf.getRegFile(i.rs1));
               
                q.popInstruction();
                i.issueTime = clock;
                rS[2].setClock(clock);
                i.index = rS[2].getIndex();
                issued.push_back(i);
                rS[2].setImm(i.imm);
                rS[2].setRd(i.rd);
               
                rS[2].setStartExec(-1);
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[2].setQj(regS.getRegStat(i.rs1).second);
                q.popInstruction();
                i.issueTime = clock;
                rS[2].setClock(clock);
                i.index = rS[2].getIndex();
                issued.push_back(i);
                rS[2].setImm(i.imm);
                rS[2].setRd(i.rd);
                
                rS[2].setStartExec(-1);
                
            }
            
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[2].setVk(rf.getRegFile(i.rs2));
                rS[2].setImm(i.imm);
                rS[2].setRd(i.rd);
                
                rS[2].setStartExec(-1);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[2].setQk(regS.getRegStat(i.rs2).second);
                rS[2].setImm(i.imm);
                rS[2].setRd(i.rd);
               
                rS[2].setStartExec(-1);
               
            }
            
            
            
            
            
        }
        
        
        
        
        //rS[3] check
        else if(rS[3].getBusy()==false){
            rS[3].setBusy(true);
            rS[3].setOp('s');
            rS[3].setIndex(instIndex);
            instIndex++;
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[3].setVj(rf.getRegFile(i.rs1));
                
                rS[3].setImm(i.imm);
                rS[3].setRd(i.rd);
               
                rS[3].setStartExec(-1);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[3].setQj(regS.getRegStat(i.rs1).second);
                rS[3].setImm(i.imm);
                rS[3].setRd(i.rd);
                
                rS[3].setStartExec(-1);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[3].setVk(rf.getRegFile(i.rs2));
               
                q.popInstruction();
                i.issueTime = clock;
                rS[3].setClock(clock);
                i.index = rS[3].getIndex();
                issued.push_back(i);
                rS[3].setImm(i.imm);
                rS[3].setRd(i.rd);
                
                rS[3].setStartExec(-1);
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[3].setQk(regS.getRegStat(i.rs2).second);
                q.popInstruction();
                i.issueTime = clock;
                rS[3].setClock(clock);
                i.index = rS[3].getIndex();
                issued.push_back(i);
                rS[3].setImm(i.imm);
                rS[3].setRd(i.rd);
               
                rS[3].setStartExec(-1);
            }
            
            
        }
        
        
    }
    
    
    
    
    
    //beq requires rs1, rs2 and imm
    //reservation station of BEQ
    // rS[4]
    
    else if(i.instName=="BEQ"){
        
        
        
        
        if(rS[4].getBusy()==false){
            rS[4].setBusy(true);
            rS[4].setOp('b');
            rS[4].setIndex(instIndex);
            instIndex++;
            if(regS.getRegStat(i.rs1).first==0){
                rS[4].setVj(rf.getRegFile(i.rs1));
                
                q.popInstruction();
                i.issueTime = clock;
                rS[4].setClock(clock);
                i.index = rS[4].getIndex();
                issued.push_back(i);
                rS[4].setImm(i.imm);
                rS[4].setRd(i.rd);
            
                rS[4].setStartExec(-1);
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[4].setQj(regS.getRegStat(i.rs1).second);
                q.popInstruction();
                i.issueTime = clock;
                rS[4].setClock(clock);
                i.index = rS[4].getIndex();
                issued.push_back(i);
                rS[4].setImm(i.imm);
                rS[4].setRd(i.rd);
              
                rS[4].setStartExec(-1);
                
            }
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[4].setVk(rf.getRegFile(i.rs2));
               
                rS[4].setImm(i.imm);
                rS[4].setRd(i.rd);
            
                rS[4].setStartExec(-1);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[4].setQk(regS.getRegStat(i.rs2).second);
                rS[4].setImm(i.imm);
                rS[4].setRd(i.rd);
                
                rS[4].setStartExec(-1);
               
            }
            
            
            
            
            
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
       
        
       
        
    }
    
    // Jal requires rd and imm
    // rS[5]
    else if(i.instName=="JAL"){
        
        if(rS[5].getBusy()==false){
            rS[5].setBusy(true);
            rS[5].setOp('j');
            rS[5].setIndex(instIndex);
            instIndex++;
            regS.modifyRegS(i.rd, "JAL", 1);
            q.popInstruction();
            i.issueTime = clock;
            rS[5].setClock(clock);
            i.index = rS[5].getIndex();
            issued.push_back(i);
            rS[5].setImm(-2); //Raga3oooooooooooooooo 
            rS[5].setRd(i.rd);
         
            rS[5].setStartExec(-1);
        }
        
        
    }
    // Jalr requires rd and rs1
    else if(i.instName=="JALR"){
        
     
        
        
        if(rS[5].getBusy()==false){
            rS[5].setBusy(true);
            rS[5].setOp('b');
            rS[5].setIndex(instIndex);
            instIndex++;
            if(regS.getRegStat(i.rs1).first==0){
                rS[5].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "JALR", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[5].setClock(clock);
                i.index = rS[5].getIndex();
                issued.push_back(i);
                rS[5].setImm(i.imm);
                rS[5].setRd(i.rd);
               
                rS[5].setStartExec(-1);
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[5].setQj(regS.getRegStat(i.rs1).second);
                regS.modifyRegS(i.rd, "JALR", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[5].setClock(clock);
                i.index = rS[5].getIndex();
                issued.push_back(i);
                rS[5].setImm(i.imm);
                rS[5].setRd(i.rd);
              
                rS[5].setStartExec(-1);
                
            }
        
        
    
    }
    }
    
    //add requires rs1 rs2 and rd
    else if(i.instName=="ADD"){
        
        
        
        
        
        if(rS[6].getBusy()==false){
            rS[6].setBusy(true);
            rS[6].setOp('a');
            rS[6].setIndex(instIndex);
            instIndex++;
            if(regS.getRegStat(i.rs1).first==0){
                rS[6].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "ADD1", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[6].setClock(clock);
                i.index = rS[6].getIndex();
                issued.push_back(i);
                rS[6].setImm(i.imm);
                rS[6].setRd(i.rd);
               
                rS[6].setStartExec(-1);
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[6].setQj(regS.getRegStat(i.rs1).second);
                regS.modifyRegS(i.rd, "ADD1", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[6].setClock(clock);
                i.index = rS[6].getIndex();
                issued.push_back(i);
                rS[6].setImm(i.imm);
                rS[6].setRd(i.rd);
               
                rS[6].setStartExec(-1);
                
            }
            
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[6].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "ADD1", 1);
                rS[6].setImm(i.imm);
                rS[6].setRd(i.rd);
             
                rS[6].setStartExec(-1);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[6].setQk(regS.getRegStat(i.rs2).second);
                rS[6].setImm(i.imm);
                rS[6].setRd(i.rd);
                
                rS[6].setStartExec(-1);
               
            }
            
            
            
            
            
        }
        
        
        
        
        //rS[7] check
        else if(rS[7].getBusy()==false){
            rS[7].setBusy(true);
            rS[7].setOp('s');
            rS[7].setIndex(instIndex);
            instIndex++;
           
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[7].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "ADD2", 1);
                rS[7].setImm(i.imm);
                rS[7].setRd(i.rd);
                
                rS[7].setStartExec(-1);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[7].setQj(regS.getRegStat(i.rs1).second);
                rS[7].setImm(i.imm);
                rS[7].setRd(i.rd);
                
                rS[7].setStartExec(-1);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[7].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "ADD2", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[7].setClock(clock);
                i.index = rS[7].getIndex();
                issued.push_back(i);
                rS[7].setImm(i.imm);
                rS[7].setRd(i.rd);
               
                rS[7].setStartExec(-1);
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[7].setQk(regS.getRegStat(i.rs2).second);
                regS.modifyRegS(i.rd, "ADD2", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[7].setClock(clock);
                i.index = rS[7].getIndex();
                issued.push_back(i);
                rS[7].setImm(i.imm);
                rS[7].setRd(i.rd);
             
                rS[7].setStartExec(-1);
            }
            
            
        }
        
        
        
        
        else if(rS[8].getBusy()==false){
            rS[8].setBusy(true);
            rS[8].setOp('s');
            rS[8].setIndex(instIndex);
            instIndex++;
           
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[8].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "ADD3", 1);
                rS[8].setImm(i.imm);
                rS[8].setRd(i.rd);
               
                rS[8].setStartExec(-1);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[8].setQj(regS.getRegStat(i.rs1).second);
                rS[8].setImm(i.imm);
                rS[8].setRd(i.rd);
                
                rS[8].setStartExec(-1);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[8].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "ADD3", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[8].setClock(clock);
                i.index = rS[8].getIndex();
                issued.push_back(i);
                rS[8].setImm(i.imm);
                rS[8].setRd(i.rd);
              
                rS[8].setStartExec(-1);
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[8].setQk(regS.getRegStat(i.rs2).second);
                regS.modifyRegS(i.rd, "ADD3", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[8].setClock(clock);
                i.index = rS[8].getIndex();
                issued.push_back(i);
                rS[8].setImm(i.imm);
                rS[8].setRd(i.rd);
                
                rS[8].setStartExec(-1);
            }
            
            
        }
      
        
        
        
        
        
    }
    
    //addi requires rd rs1 and imm
    else if(i.instName=="ADDI"){
        
        
        
        if(rS[6].getBusy()==false){
            rS[6].setBusy(true);
            rS[6].setOp('a');
            rS[6].setIndex(instIndex);
            instIndex++;
            if(regS.getRegStat(i.rs1).first==0){
                rS[6].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "ADD1", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[6].setClock(clock);
                i.index = rS[6].getIndex();
                issued.push_back(i);
                rS[6].setImm(i.imm);
                rS[6].setVk(i.imm);
                
                rS[6].setRd(i.rd);
              
                rS[6].setStartExec(-1);
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[6].setQj(regS.getRegStat(i.rs1).second);
                regS.modifyRegS(i.rd, "ADD1", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[6].setClock(clock);
                i.index = rS[6].getIndex();
                issued.push_back(i);
                rS[6].setImm(i.imm);
                rS[6].setVk(i.imm);
                rS[6].setRd(i.rd);
               
                rS[6].setStartExec(-1);
                
            }
            
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[6].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "ADD1", 1);
                rS[6].setImm(i.imm);
                rS[6].setVk(i.imm);
                rS[6].setRd(i.rd);
            
                rS[6].setStartExec(-1);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[6].setQk(regS.getRegStat(i.rs2).second);
                rS[6].setImm(i.imm);
                rS[6].setVk(i.imm);
                rS[6].setRd(i.rd);
                
                rS[6].setStartExec(-1);
               
            }
            
            
            
            
            
        }
        
        
        
        
        //rS[7] check
        else if(rS[7].getBusy()==false){
            rS[7].setBusy(true);
            rS[7].setOp('s');
            rS[7].setImm(i.imm);
            rS[7].setVk(i.imm);
            rS[7].setIndex(instIndex);
            instIndex++;
            
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[7].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "ADD2", 1);
                rS[7].setImm(i.imm);
                rS[7].setVk(i.imm);
                rS[7].setRd(i.rd);
                
                rS[7].setStartExec(-1);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[7].setQj(regS.getRegStat(i.rs1).second);
                rS[7].setImm(i.imm);
                rS[7].setVk(i.imm);
                rS[7].setRd(i.rd);
               
                rS[7].setStartExec(-1);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[7].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "ADD2", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[7].setClock(clock);
                i.index = rS[7].getIndex();
                issued.push_back(i);
                rS[7].setImm(i.imm);
                rS[7].setVk(i.imm);
                rS[7].setRd(i.rd);
              
                rS[7].setStartExec(-1);
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[7].setQk(regS.getRegStat(i.rs2).second);
                regS.modifyRegS(i.rd, "ADD2", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[7].setClock(clock);
                i.index = rS[7].getIndex();
                issued.push_back(i);
                rS[7].setImm(i.imm);
                rS[7].setVk(i.imm);
                rS[7].setVk(i.imm);
                rS[7].setRd(i.rd);
               
                rS[7].setStartExec(-1);
            }
            
            
        }
        
        //rS[8] check
        else if(rS[8].getBusy()==false){
            rS[8].setBusy(true);
            rS[8].setOp('s');
            rS[8].setIndex(instIndex);
            instIndex++;
           
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[8].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "ADD3", 1);
                rS[8].setImm(i.imm);
                rS[8].setVk(i.imm);
                rS[8].setRd(i.rd);
               
                rS[8].setStartExec(-1);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[8].setQj(regS.getRegStat(i.rs1).second);
                rS[8].setImm(i.imm);
                rS[8].setVk(i.imm);
                rS[8].setRd(i.rd);
               
                rS[8].setStartExec(-1);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[8].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "ADD3", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[8].setClock(clock);
                i.index = rS[8].getIndex();
                issued.push_back(i);
                rS[8].setImm(i.imm);
                rS[8].setVk(i.imm);
                rS[8].setRd(i.rd);
            
                rS[8].setStartExec(-1);
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[8].setQk(regS.getRegStat(i.rs2).second);
                regS.modifyRegS(i.rd, "ADD3", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[8].setClock(clock);
                i.index = rS[8].getIndex();
                issued.push_back(i);
                rS[8].setImm(i.imm);
                rS[8].setVk(i.imm);
                rS[8].setRd(i.rd);
                
                rS[8].setStartExec(-1);
            }
            
            
        }
        
    }
    
    //neg requires rs1 and rd
    // rS[9]
        
        
    else if(i.instName=="NEG"){
        
        
            if(rS[9].getBusy()==false){
                rS[9].setBusy(true);
                rS[9].setOp('l');
                rS[9].setIndex(instIndex);
                instIndex++;
                if(regS.getRegStat(i.rs1).first==0){
                    rS[9].setVj(rf.getRegFile(i.rs1));
                    regS.modifyRegS(i.rd, "NEG1", 1);
                    q.popInstruction();
                    i.issueTime = clock;
                    rS[9].setClock(clock);
                    i.index = rS[9].getIndex();
                    issued.push_back(i);
                    rS[9].setImm(i.imm);
                    rS[9].setRd(i.rd);
                   
                    rS[9].setStartExec(-1);
                    
                }
                else if(regS.getRegStat(i.rs1).first==1){
                    
                    rS[9].setQj(regS.getRegStat(i.rs1).second);
                    regS.modifyRegS(i.rd, "NEG1", 1);
                    q.popInstruction();
                    i.issueTime = clock;
                    rS[9].setClock(clock);
                    i.index = rS[9].getIndex();
                    issued.push_back(i);
                    rS[9].setImm(i.imm);
                    rS[9].setRd(i.rd);
                    
                    rS[9].setStartExec(-1);
                    
                }
                
            }
        
        
    }
    
    //abs requires rs1 and rd
    //rS[10]
        
        
    else if(i.instName=="ABS"){
        
        
        
            if(rS[10].getBusy()==false){
                rS[10].setBusy(true);
                rS[10].setOp('l');
                rS[10].setIndex(instIndex);
                instIndex++;
                if(regS.getRegStat(i.rs1).first==0){
                    rS[10].setVj(rf.getRegFile(i.rs1));
                    regS.modifyRegS(i.rd, "ABS1", 1);
                    q.popInstruction();
                    i.issueTime = clock;
                    rS[10].setClock(clock);
                    i.index = rS[10].getIndex();
                    issued.push_back(i);
                    rS[10].setImm(i.imm);
                    rS[10].setRd(i.rd);
                  
                    rS[10].setStartExec(-1);
                    
                }
                else if(regS.getRegStat(i.rs1).first==1){
                    
                    rS[10].setQj(regS.getRegStat(i.rs1).second);
                    regS.modifyRegS(i.rd, "ABS1", 1);
                    q.popInstruction();
                    i.issueTime = clock;
                    rS[10].setClock(clock);
                    i.index = rS[10].getIndex();
                    issued.push_back(i);
                    rS[10].setImm(i.imm);
                    rS[10].setRd(i.rd);
               
                    rS[10].setStartExec(-1);
                    
                }
                
            }
        
        
    }
    
    //Div requires rs1 rs2 and rd
        
    //rS[11]
    
    else if(i.instName=="DIV"){
        
        if(rS[11].getBusy()==false){
            rS[11].setBusy(true);
            rS[11].setOp('a');
            rS[11].setIndex(instIndex);
            instIndex++;
            if(regS.getRegStat(i.rs1).first==0){
                rS[11].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "DIV1", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[11].setClock(clock);
                i.index = rS[11].getIndex();
                issued.push_back(i);
                rS[11].setImm(i.imm);
                rS[11].setRd(i.rd);
              
                rS[11].setStartExec(-1);
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                rS[11].setQj(regS.getRegStat(i.rs1).second);
                regS.modifyRegS(i.rd, "DIV1", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[11].setClock(clock);
                i.index = rS[11].getIndex();
                issued.push_back(i);
                rS[11].setImm(i.imm);
                rS[11].setRd(i.rd);
                
                rS[11].setStartExec(-1);
            }
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[11].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "DIV1", 1);
                rS[11].setImm(i.imm);
                rS[11].setRd(i.rd);
                
                rS[11].setStartExec(-1);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[11].setQk(regS.getRegStat(i.rs2).second);
                rS[11].setImm(i.imm);
                rS[11].setRd(i.rd);
              
                rS[11].setStartExec(-1);
               
            }
            
        }
        
    }
    
    
}










void integration::executeInstructions( instQueue &q, instQueue &p, resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem){
    
    
    //LW execution
    //condition Qj snd Qk  == -1, the reservation station should also
    // be busy (Qj and QK are always set to -1) and no conflicting address
    //first cycle we compute the effective address
    
    if( !((rS[4].getBusy()==1 | rS[5].getBusy()==1) && (rS[5].getIndex()<rS[0].getIndex()|rS[4].getIndex()<rS[0].getIndex()))){
 
    
    if((rS[0].getBusy()==1)&&(rS[0].getQj()=="")&&(rS[0].getQk()=="")){
       
            rS[0].setA(rS[0].getVj()+rS[0].getImm());
            
            if(clock - rS[0].getClock()>= 1){
                
                if(rS[0].getStartExec()==-1){
                rS[0].setStartExec(clock);
                issued[rS[0].getIndex()].startExec = clock;
                   
                }
            }
            
            if(clock - rS[0].getStartExec() >= 4){
                if((rS[0].getA()==rS[1].getA())|| (rS[0].getA()==rS[2].getA()) || (rS[0].getA()==rS[3].getA()) ){
                
                    if((rS[0].getClock()<rS[1].getClock())||(rS[0].getClock()<rS[2].getClock())||(rS[0].getClock()<rS[3].getClock())){
                        
                        rS[0].setEndExec(clock);
                        issued[rS[0].getIndex()].endExec = clock;
                        
                        
                        
                        wbQueue a;
                        a.value = mem.dataGetter(rS[0].getA());
                        a.index = rS[0].getRd();
                        a.clock = rS[0].getClock();
                        a.resvNum = 0;
                        a.inst = rS[0].getIndex();
                        writeBackQueue.push_back(a);
                        rS[0].setBusy(false);

                    }
                    
                } else {
                    
                    
                    rS[0].setEndExec(clock);
                    
              
                    issued[rS[0].getIndex()].endExec = clock;
                    
                    
                    
                    wbQueue a;
                    a.value = mem.dataGetter(rS[0].getA());
                    a.index = rS[0].getRd();
                    a.clock = rS[0].getClock();
                    a.resvNum = 0;
                    a.inst = rS[0].getIndex();
                    writeBackQueue.push_back(a);
                    rS[0].setBusy(false);
                    
                    
                }
                
            }
        
    
        
    }
    
}
    
    //LW second rS
    if( !((rS[4].getBusy()==1 | rS[5].getBusy()==1) && (rS[5].getIndex()<rS[1].getIndex()|rS[4].getIndex()<rS[1].getIndex()))){
    
    if((rS[1].getBusy()==1)&&(rS[1].getQj()=="")&&(rS[1].getQk()=="")){
       
        
        
        
        rS[1].setA(rS[1].getVj()+rS[1].getImm());
        
        if(clock - rS[1].getClock()>= 1){
            
            if(rS[1].getStartExec()==-1){
            rS[1].setStartExec(clock);
                issued[rS[1].getIndex()].startExec = clock;
            }

        }
        
        
        if(clock - rS[1].getStartExec() >= 4){
            
            if((rS[1].getA()==rS[0].getA())|| (rS[2].getA()==rS[1].getA()) || (rS[1].getA()==rS[3].getA()) ){
            
                if((rS[1].getClock()<rS[0].getClock())||(rS[2].getClock()<rS[1].getClock())||(rS[1].getClock()<rS[3].getClock())){
                    
                    
                    
                    
                    
                    rS[1].setEndExec(clock);
                    issued[rS[1].getIndex()].endExec = clock;
                    
                    
                    wbQueue a;
                    a.value = mem.dataGetter(rS[1].getA());
                    a.index = rS[1].getRd();
                    a.clock = rS[1].getClock();
                    a.resvNum = 1;
                    a.inst = rS[1].getIndex();
                    writeBackQueue.push_back(a);
                    rS[1].setBusy(false);
                
                } else {
                    
                    //sw function
                    rS[1].setEndExec(clock);
                    issued[rS[1].getIndex()].endExec = clock;
                    
                    
                    
                    wbQueue a;
                    a.value = mem.dataGetter(rS[1].getA());
                    a.index = rS[1].getRd();
                    a.clock = rS[1].getClock();
                    a.resvNum = 1;
                    a.inst = rS[1].getIndex();
                    writeBackQueue.push_back(a);
                    rS[1].setBusy(false);
                    
                    
                }

                
            }
            
        }
        
        
        
        
        
    }
    
    
}
    

    
    //SW first rS
    if( !((rS[4].getBusy()==1 | rS[5].getBusy()==1) && (rS[5].getIndex()<rS[2].getIndex()|rS[4].getIndex()<rS[2].getIndex()))){
    if((rS[2].getBusy()==1)&&(rS[2].getQj()=="")&&(rS[2].getQk()=="")){
       
        
           
            
            rS[2].setA(rS[2].getVj()+rS[2].getImm());
            
            if(clock - rS[2].getClock()>= 1){
                
                if(rS[2].getStartExec()==-1){
                rS[2].setStartExec(clock);
                    issued[rS[2].getIndex()].startExec = clock;
                }

            }
            
            
            if(clock - rS[2].getStartExec() >= 2){
                
                if((rS[2].getA()==rS[0].getA())|| (rS[2].getA()==rS[1].getA()) || (rS[2].getA()==rS[3].getA()) ){
                
                    if((rS[2].getClock()<rS[0].getClock())||(rS[2].getClock()<rS[1].getClock())||(rS[2].getClock()<rS[3].getClock())){
                        //sw function
                        sW( mem, rS[3].getVk(),rS[3].getA());
                        rS[2].setEndExec(clock);
                        issued[rS[2].getIndex()].endExec = clock;
                        rS[2].setBusy(false);
                        
                        
                    
                    }
                    
                }else {
                    
                    //sw function
                    sW( mem, rS[3].getVk(),rS[3].getA());
                    rS[2].setEndExec(clock);
                    issued[rS[2].getIndex()].endExec = clock;
                    rS[2].setBusy(false);
                    
                    
                    
                  
                    
                    
                    
                }

                
            }
        
        
        
        
        
    }
    
}
    
    
    //SW second rS
    if( !((rS[4].getBusy()==1 | rS[5].getBusy()==1) && (rS[5].getIndex()<rS[3].getIndex()|rS[4].getIndex()<rS[3].getIndex()))){
    if((rS[3].getBusy()==1)&&(rS[3].getQj()=="")&&(rS[3].getQk()=="")){
       
        
        rS[3].setA(rS[3].getVj()+rS[3].getImm());
        
        if(clock - rS[3].getClock()>= 1){
            
            if(rS[3].getStartExec()==-1){
            rS[3].setStartExec(clock);
                issued[rS[3].getIndex()].startExec = clock;
            }
        
            
        }
        
        
        if(clock - rS[3].getStartExec() >= 2){
            
            if((rS[3].getA()==rS[0].getA())|| (rS[3].getA()==rS[1].getA()) || (rS[3].getA()==rS[2].getA()) ){
            
                if((rS[3].getClock()<rS[0].getClock())||(rS[3].getClock()<rS[1].getClock())||(rS[3].getClock()<rS[2].getClock())){
                    
                    //sw function
                    sW( mem, rS[3].getVk(),rS[3].getA());
                    rS[3].setEndExec(clock);
                    issued[rS[3].getIndex()].endExec = clock;
                    rS[3].setBusy(false);
                
                }
                
            }
            else {
                
                //sw function
                sW( mem, rS[3].getVk(),rS[3].getA());
                
                rS[3].setEndExec(clock);
                issued[rS[3].getIndex()].endExec = clock;
                rS[3].setBusy(false);
                
                
         
                
                
            }

            
            
            
        }
        
    
        
    }
    
    }
    
   

    //ADD/ADDI
    
    if( !((rS[4].getBusy()==1 | rS[5].getBusy()==1) && (rS[5].getIndex()<rS[6].getIndex()|rS[4].getIndex()<rS[6].getIndex()))){
    if((rS[6].getBusy()==1)&&(rS[6].getQj()=="")&&(rS[6].getQk()=="")){
        if(clock - rS[6].getClock()>= 1){
        if(rS[6].getStartExec()==-1){
        rS[6].setStartExec(clock);
            issued[rS[6].getIndex()].startExec = clock;
        }
            
        }
        
        if(clock - rS[6].getStartExec() == 2 && (rS[6].getStartExec()!=-1)){
            
            rS[6].setEndExec(clock);
            issued[rS[6].getIndex()].endExec = clock;
            
            
            wbQueue a;
            a.value = rS[6].getVj() + rS[6].getVk();
            a.index = rS[6].getRd();
            a.clock = rS[6].getClock();
            a.resvNum = 6;
            a.inst = rS[6].getIndex();
            writeBackQueue.push_back(a);
            rS[6].setBusy(false);
            
            
            
        }
      
        
    }
    }
    
    if( !((rS[4].getBusy()==1 | rS[5].getBusy()==1) && (rS[5].getIndex()<rS[7].getIndex()|rS[4].getIndex()<rS[7].getIndex()))){
    if((rS[7].getBusy()==1)&&(rS[7].getQj()=="")&&(rS[7].getQk()=="")){
        
        if(clock - rS[7].getClock()>= 1){
        if(rS[7].getStartExec()==-1){
        rS[7].setStartExec(clock);
            issued[rS[7].getIndex()].startExec = clock;
        }
            
        }
        
        if(clock - rS[7].getStartExec() == 2 && (rS[7].getStartExec()!=-1)){
            
            rS[7].setEndExec(clock);
            issued[rS[7].getIndex()].endExec = clock;
            
            wbQueue a;
            a.value = rS[7].getVj() + rS[7].getVk();
            a.index = rS[7].getRd();
            a.clock = rS[7].getClock();
            a.resvNum = 7;
            a.inst = rS[7].getIndex();
            writeBackQueue.push_back(a);
            rS[7].setBusy(false);
            
        }
        
        
    }
    }
    
    
    if( !((rS[4].getBusy()==1 | rS[5].getBusy()==1) && (rS[5].getIndex()<rS[8].getIndex()|rS[4].getIndex()<rS[8].getIndex()))){
    
      
    if((rS[8].getBusy()==1)&&(rS[8].getQj()=="")&&(rS[8].getQk()=="")){
        if(clock - rS[8].getClock()>= 1){
        if(rS[8].getStartExec()==-1){
        rS[8].setStartExec(clock);
            issued[rS[8].getIndex()].startExec = clock;
        }
        }
        
        
        if(clock - rS[8].getStartExec() == 2 && (rS[8].getStartExec()!=-1)){
            
            rS[8].setEndExec(clock);
            issued[rS[8].getIndex()].endExec = clock;
            wbQueue a;
            a.value = rS[8].getVj() + rS[8].getVk();
            a.index = rS[8].getRd();
            a.resvNum = 8;
            a.inst = rS[8].getIndex();
            a.clock = rS[8].getClock();
            writeBackQueue.push_back(a);
            rS[8].setBusy(false);
            
            
            
        }
        
    }
    }
    
    
    
    //NEG
    
    
    if( !((rS[4].getBusy()==1 | rS[5].getBusy()==1) && (rS[5].getIndex()<rS[9].getIndex()|rS[4].getIndex()<rS[9].getIndex()))){
    if((rS[9].getBusy()==1)&&(rS[9].getQj()=="")&&(rS[9].getQk()=="")){
        if(clock - rS[9].getClock()>= 1){
        if(rS[9].getStartExec()==-1){
        rS[9].setStartExec(clock);
            issued[rS[9].getIndex()].startExec = clock;
        }
            
        }
        
        if(clock - rS[9].getStartExec() == 3 && (rS[9].getStartExec()!=-1)){
            
            rS[9].setEndExec(clock);
            issued[rS[9].getIndex()].endExec = clock;
            
            wbQueue a;
            a.value = rS[9].getVj()*-1;
            a.index = rS[9].getRd();
            a.clock = rS[9].getClock();
            a.resvNum = 9;
            a.inst = rS[9].getIndex();
            writeBackQueue.push_back(a);
            rS[9].setBusy(false);
            
            
            
        }
        
        
    }
    }
    
    
    
    //ABS
    if( !((rS[4].getBusy()==1 | rS[5].getBusy()==1) && (rS[5].getIndex()<rS[10].getIndex()|rS[4].getIndex()<rS[10].getIndex()))){
    if((rS[10].getBusy()==1)&&(rS[10].getQj()=="")&&(rS[10].getQk()=="")){
        if(clock - rS[10].getClock()>= 1){
        if(rS[10].getStartExec()==-1){
        rS[10].setStartExec(clock);
            issued[rS[10].getIndex()].startExec = clock;
        }
        }
        
        if(clock - rS[10].getStartExec() == 2 && (rS[10].getStartExec()!=-1)){
            
            rS[10].setEndExec(clock);
            issued[rS[10].getIndex()].endExec = clock;
            
            
            wbQueue a;
            a.value = abs(rS[10].getVj()) ;
            a.index = rS[10].getRd();
            a.clock = rS[10].getClock();
            a.resvNum = 10;
            a.inst = rS[10].getIndex();
            writeBackQueue.push_back(a);
            rS[10].setBusy(false);
            
            
            
        }
        }
    }
    
    
    
    
    //DIV
    if( !((rS[4].getBusy()==1 | rS[5].getBusy()==1) && (rS[5].getIndex()<rS[11].getIndex()|rS[4].getIndex()<rS[11].getIndex()))){
    if((rS[11].getBusy()==1)&&(rS[11].getQj()=="")&&(rS[11].getQk()=="")){
        if(clock - rS[11].getClock()>= 1){
        if(rS[11].getStartExec()==-1){
        rS[11].setStartExec(clock);
            issued[rS[11].getIndex()].startExec = clock;
        }
        }
        
        
        
        if(clock - rS[11].getStartExec() == 10 && (rS[11].getStartExec()!=-1)){
            
            rS[11].setEndExec(clock);
            issued[rS[11].getIndex()].endExec = clock;
            
            wbQueue a;
            a.value = rS[11].getVj() / rS[11].getVk();
            a.index = rS[11].getRd();
            a.clock = rS[11].getClock();
            a.resvNum = 11;
            a.inst = rS[11].getIndex();
            writeBackQueue.push_back(a);
            rS[11].setBusy(false);
            
            
            
        }
        
        
        }
    }
    
    

    
    
    
    
    
    //special for branching
    
    
    
    
    if( !((rS[4].getBusy()==1) && (rS[5].getIndex()<rS[11].getIndex()|rS[4].getIndex()<rS[11].getIndex()))){
    if((rS[5].getBusy()==1)&&(rS[5].getQj()=="")&&(rS[5].getQk()=="")){
        if(clock - rS[5].getClock()>= 1){
        if(rS[5].getStartExec()==-1){
        rS[5].setStartExec(clock);
            issued[rS[5].getIndex()].startExec = clock;
            jalCame = true;
        }
        }
        
        if((clock - rS[5].getStartExec() == 1) && (rS[5].getStartExec()!=-1)){
            rS[4].setStartExec(-1);
            //stopped here
            jal( q , p, rS, regS, rf, issued, mem, 0, 0, rS[5].getClock(), rS[5].getImm(), rS[5].getIndex());
            jalCame = false;
            rS[5].setEndExec(clock);
            issued[rS[5].getIndex()].endExec = clock;
            rS[5].setBusy(false);
            wbQueue a;
            a.value = rS[5].getIndex();
            a.index = rS[5].getRd();
            a.clock = rS[5].getClock();
            a.resvNum = 5;
            a.inst = rS[5].getIndex();
            writeBackQueue.push_back(a);
            
            
            
        }
        
    }
    }
    
    
    
    
    //BEQ
    
    
    
    if((rS[4].getBusy()==1)&&(rS[4].getQj()=="")&&(rS[4].getQk()=="")){
        if(clock - rS[4].getClock()>= 1){
        if(rS[4].getStartExec()==-1){
            
       
        rS[4].setStartExec(clock);
            issued[rS[4].getIndex()].startExec = clock;
            branchCame = true;
            
        }
        }
        
        
        
        if(clock - rS[4].getStartExec() == 1 && (rS[4].getStartExec()!=-1)){
            branchCounter++;
            
            //branch or don't branch function
            rS[4].setStartExec(-1);
            if(rS[4].getVk()-rS[4].getVj()!=0){
                
                branchCame =false;
               
                branchMissCounter++;
                goto dontBranch;
            }
            
            
        //branch function
            
            branch( q, p, rS, regS, rf, issued, mem, 0, 0, rS[4].getClock(), rS[4].getImm(), rS[4].getIndex());
           
            
dontBranch:
            
                
                
                
            
            
            branchCame =false;
            rS[4].setEndExec(clock);
            
            issued[rS[4].getIndex()].endExec = clock;
            rS[4].setBusy(false);
            rS[4].setIndex(10000);
            
            
        }
        
    }
    
    
    
    
    
    //JAL/JALR
 
    
    
    
    
    

    
    
}






//In the write back stage we need to broadcast the value to
// regStat and the other reservations stations
// mark the current reservations station as not busy



void integration::wB( resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem, int valueToWrite, int rd, int resvNum){
    
//the write back function shall take the rd and write back to the register file the new value
// and broadcast the value to all reservation stations waiting for this value
    
    
    if (regS.getRegStat(rd).second == rS[resvNum].getName()) {
        rf.setRegFile(valueToWrite, rd);
        regS.modifyRegS(rd, "", 0);
    }
    
    
    for(int i=0; i<12; i++){
        
        if((rS[i].getQj()==rS[resvNum].getName())){
            rS[i].setQj("");
            rS[i].setVj(valueToWrite);

        }

        if((rS[i].getQk()== rS[resvNum].getName())){
            
            rS[i].setQk("");
            rS[i].setVk(valueToWrite);
            
        }
        
    }
    
    
    
}



//add r5, r3, r2

//wb vj and vk will be forwarded by the CDB

//if we're issuing

//add r5, r5, r5




void integration::heapify(vector<wbQueue> &j, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    if (l < n && j[l].clock > j[largest].clock)
        largest = l;
    if (r < n && j[r].clock > j[largest].clock)
        largest = r;
    if (largest != i) {
        swap(j[i], j[largest]);
        heapify(j, n, largest);
    }
    
}

void integration::build_heap(vector<wbQueue> &j)
{
    for (int i = j.size() / 2 - 1; i >= 0; i--)
        heapify(j, j.size(), i);
}


void integration::heap_sort(vector<wbQueue> &j)
{
    build_heap(j);
    for (int i = j.size() - 1; i >= 0; i--) {
        swap(j[0], j[i]);
        heapify(j, i, 0);
    }
}



wbQueue integration::sortAndIssueWb(vector<wbQueue> writeBackQueue){
    
    heap_sort(writeBackQueue);
    wbQueue a;
    if(writeBackQueue.size()!=0){
     a = writeBackQueue[0];

    writeBackQueue.erase(writeBackQueue.begin());
    }
    
    return  a;
  

}




void integration::jal(instQueue &q, instQueue &p, resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem , int valueToWrite, int rd, int clk, int imm, int ind){
    
    vector<inst> queue = q.getQueue();
    
    for(int i=0; i<12; i++){
        
      //  if(rS[i].getClock()>clk && (rS[i].getClock()<=(clk+imm))){
        if(rS[i].getIndex()>ind&&(rS[i].getIndex()!=10000)){
            
            rS[i].flush(rS[i].getName());
            regS.modifyRegS(rS[i].getRd(), "", 0);
            
            
            for(int j=0; j<12; j++){
                
                
                if(rS[j].getQk()==rS[i].getName()){
                    
                    rS[j].setQk("");
                    rS[j].setVk(rf.getRegFile(rS[i].getRd()));
                }
                
                if(rS[j].getQj()==rS[i].getName()){
                    
                    rS[j].setQj("");
                    rS[j].setVj(rf.getRegFile(rS[i].getRd()));
                }
                
                
            }
            
        }
    }
    if(imm>0){
    for(int i=0; i<queue.size(); i++){
        
        if(queue[i].index<ind+imm){
            
            queue.erase(queue.begin()+i); 
            i=0;
        }
    }
        
        q.setQueue(queue);
    
    }
    
    if(imm<0){
        recoverQueue(q, p , ind, imm);
        
        
    }
    
    rS[5].setStartExec(-1);
    
    
    
    
    
    
}




void integration::branch(instQueue &q, instQueue &p ,resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem , int valueToWrite, int rd, int clk, int imm, int ind){
 
    //in case of negative offset recover queue
    
    
    
    vector<inst> queue = q.getQueue();
    
    
    for(int i=0; i<12; i++){
      
        if(rS[i].getClock()>clk && (rS[i].getClock()<=(clk+imm))){
        
         
            
            rS[i].flush(rS[i].getName());
            regS.modifyRegS(rS[i].getRd(), "", 0);
            


            
        }
    }
    
    
    if(imm>0){
    for(int i=0; i<queue.size(); i++){
        
        if(queue[i].index<ind+imm){
            
            queue.erase(queue.begin()+i);
            i = 0;
        }
    }
        q.setQueue(queue);
    }
    
    
    
    if(imm<0){
        recoverQueue(q, p , ind, imm);
        
        
    }
    
    
    rS[5].setStartExec(-1);
   
    
}




void integration::recoverQueue(instQueue &q, instQueue &p, int index, int imm){
    
    
    q = p;
    
    vector<inst> queue = q.getQueue();
    
    int jalIndex=0;
    vector<inst> jFinder = p.getQueue();
    
    for(int i=0; i<jFinder.size(); i++){
        if(jFinder[i].instName=="JAL"){
            jalIndex = i;
        }
        
    }
    
    
    for(int i=0; i<jalIndex+imm; i++){
        
        queue.erase(queue.begin());
        
    }
    
    q.setQueue(queue);
    
    
}



bool integration::checkExit(instQueue &q, resvStation rS[]){
    bool flag = true;
    vector<inst> queue = q.getQueue();
    
        for(int i=0; i<12; i++){
            
            if(rS[i].getBusy()){
                
                flag = false;
            }
            
        
        

        
        
    }
    
    return flag;
    
    
}



void integration::printStats(vector<inst> &issued, int clock){
    
    
    for(int i=0; i<issued.size(); i++){
        
        cout << "Inst Name: " << issued[i].instName << " Issue Time: " << issued[i].issueTime << " StartExec: " << issued[i].startExec << " End Exec: " << issued[i].endExec << " Wb: " << issued[i].writeBack << endl << endl << endl;
        
    }
    
    
    cout << "Total time spanned: " << clock << endl;

    cout  << "Branch Mispredictions percentage: " << float(branchMissCounter)/float(branchCounter) *float(100) << " %" << endl;
    
    
    float ipc = float(issued.size())/float(clock);
    cout << "IPC: " <<  ipc << endl;
    
    
    
     
    
}





void integration::sW( dataMem &mem, int value, int add){
    
    mem.dataSetter(add, value);
    
}





