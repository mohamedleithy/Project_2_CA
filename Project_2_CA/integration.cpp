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
    
    vector<inst> issued;
    

    mem.dataSetter(0, 0);
    mem.dataSetter(1, 1);
    mem.dataSetter(2, 2);
    mem.dataSetter(3, 3);
    mem.dataSetter(4, 4);
    mem.dataSetter(5, 5);
    mem.dataSetter(6, 6);
    mem.dataSetter(7, 7);
    
    
    rf.setRegFile(44, 6);
    rf.setRegFile(10, 1);
    rf.setRegFile(12, 2);
    
    resvStations[0].setName("Lw1");
    resvStations[1].setName("Lw2");
    resvStations[2].setName("Sw1");
    resvStations[3].setName("Sw2");
    resvStations[4].setName("BEQ1");
    resvStations[5].setName("J1");
    resvStations[6].setName("ADD1");
    resvStations[7].setName("ADD2");
    resvStations[8].setName("ADD3");
    resvStations[9].setName("NEG1");
    resvStations[10].setName("ABS1");
    resvStations[11].setName("DIV1");
    
    
    
    
    
    
    
    //start
    
    
    
    while(1){
        
     issueInstructions( q, resvStations, rS, rf, issued);
        
    executeInstructions( resvStations, rS, rf, issued, mem);
    
    wbQueue b =  sortAndIssueWb(writeBackQueue);
        if(writeBackQueue.size()!=0){
        wB(resvStations,rS, rf, issued, mem, b.value, b.index);
        }
        
        clock++; 
    }
    
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
            if(regS.getRegStat(i.rs1).first==0){
                rS[0].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "LW1", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[0].setClock(clock);
                
                issued.push_back(i);
                rS[0].setImm(i.imm);
                rS[0].setRd(i.rd);
                
            }
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[0].setQj(i.rs1);
                q.popInstruction();
                i.issueTime = clock;
                rS[0].setClock(clock);
                issued.push_back(i);
                rS[0].setImm(i.imm);
                rS[0].setRd(i.rd);
                
            }
            
        }
        
        else if(rS[1].getBusy()==false){
            rS[1].setBusy(true);
            rS[1].setOp('l');
            if(regS.getRegStat(i.rs1).first==0){
                rS[1].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "LW2", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[1].setClock(clock);
                issued.push_back(i);
                rS[1].setImm(i.imm);
                rS[1].setRd(i.rd);
            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[1].setQj(i.rs1);
                q.popInstruction();
                i.issueTime = clock;
                rS[1].setClock(clock);
                issued.push_back(i);
                rS[1].setImm(i.imm);
                rS[1].setRd(i.rd);
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
            if(regS.getRegStat(i.rs1).first==0){
                rS[2].setVj(rf.getRegFile(i.rs1));
               
                q.popInstruction();
                i.issueTime = clock;
                rS[2].setClock(clock);
                issued.push_back(i);
                rS[2].setImm(i.imm);
                rS[2].setRd(i.rd);
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[2].setQj(i.rs1);
                q.popInstruction();
                i.issueTime = clock;
                rS[2].setClock(clock);
                issued.push_back(i);
                rS[2].setImm(i.imm);
                rS[2].setRd(i.rd);
                
            }
            
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[2].setVk(rf.getRegFile(i.rs2));
                rS[2].setImm(i.imm);
                rS[2].setRd(i.rd);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[2].setQk(i.rs2);
                rS[2].setImm(i.imm);
                rS[2].setRd(i.rd);
               
            }
            
            
            
            
            
        }
        
        
        
        
        //rS[3] check
        else if(rS[3].getBusy()==false){
            rS[3].setBusy(true);
            rS[3].setOp('s');
           
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[3].setVj(rf.getRegFile(i.rs1));
                
                rS[3].setImm(i.imm);
                rS[3].setRd(i.rd);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[3].setQj(i.rs1);
                rS[3].setImm(i.imm);
                rS[3].setRd(i.rd);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[3].setVk(rf.getRegFile(i.rs2));
               
                q.popInstruction();
                i.issueTime = clock;
                rS[3].setClock(clock);
                issued.push_back(i);
                rS[3].setImm(i.imm);
                rS[3].setRd(i.rd);
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[3].setQk(i.rs2);
                q.popInstruction();
                i.issueTime = clock;
                rS[3].setClock(clock);
                issued.push_back(i);
                rS[3].setImm(i.imm);
                rS[3].setRd(i.rd);
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
            if(regS.getRegStat(i.rs1).first==0){
                rS[4].setVj(rf.getRegFile(i.rs1));
                
                q.popInstruction();
                i.issueTime = clock;
                rS[4].setClock(clock);
                issued.push_back(i);
                rS[4].setImm(i.imm);
                rS[4].setRd(i.rd);
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[4].setQj(i.rs1);
                q.popInstruction();
                i.issueTime = clock;
                rS[4].setClock(clock);
                issued.push_back(i);
                rS[4].setImm(i.imm);
                rS[4].setRd(i.rd);
                
            }
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[4].setVk(rf.getRegFile(i.rs2));
               
                rS[4].setImm(i.imm);
                rS[4].setRd(i.rd);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[4].setQk(i.rs2);
                rS[4].setImm(i.imm);
                rS[4].setRd(i.rd);
               
            }
            
            
            
            
            
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
       
        
       
        
    }
    
    // Jal requires rd and imm
    // rS[5]
    else if(i.instName=="JAL"){
        
        if(rS[5].getBusy()==false){
            rS[5].setBusy(true);
            rS[5].setOp('j');
            regS.modifyRegS(i.rd, "JAL", 1);
            q.popInstruction();
            i.issueTime = clock;
            rS[5].setClock(clock);
            issued.push_back(i);
            rS[5].setImm(i.imm);
            rS[5].setRd(i.rd);
        }
        
    }
    // Jalr requires rd and rs1
    else if(i.instName=="JALR"){
        
     
        
        
        if(rS[5].getBusy()==false){
            rS[5].setBusy(true);
            rS[5].setOp('b');
            if(regS.getRegStat(i.rs1).first==0){
                rS[5].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "JALR", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[5].setClock(clock);
                issued.push_back(i);
                rS[5].setImm(i.imm);
                rS[5].setRd(i.rd);
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[5].setQj(i.rs1);
                q.popInstruction();
                i.issueTime = clock;
                rS[5].setClock(clock);
                issued.push_back(i);
                rS[5].setImm(i.imm);
                rS[5].setRd(i.rd);
                
            }
        
        
    
    }
    }
    
    //add requires rs1 rs2 and rd
    else if(i.instName=="ADD"){
        
        
        
        
        
        if(rS[6].getBusy()==false){
            rS[6].setBusy(true);
            rS[6].setOp('a');
            if(regS.getRegStat(i.rs1).first==0){
                rS[6].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "ADD1", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[6].setClock(clock);
                issued.push_back(i);
                rS[6].setImm(i.imm);
                rS[6].setRd(i.rd);
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[6].setQj(i.rs1);
                q.popInstruction();
                i.issueTime = clock;
                rS[6].setClock(clock);
                issued.push_back(i);
                rS[6].setImm(i.imm);
                rS[6].setRd(i.rd);
                
            }
            
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[6].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "ADD1", 1);
                rS[6].setImm(i.imm);
                rS[6].setRd(i.rd);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[6].setQk(i.rs2);
                rS[6].setImm(i.imm);
                rS[6].setRd(i.rd);
               
            }
            
            
            
            
            
        }
        
        
        
        
        //rS[7] check
        else if(rS[7].getBusy()==false){
            rS[7].setBusy(true);
            rS[7].setOp('s');
           
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[7].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "ADD2", 1);
                rS[7].setImm(i.imm);
                rS[7].setRd(i.rd);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[7].setQj(i.rs1);
                rS[7].setImm(i.imm);
                rS[7].setRd(i.rd);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[7].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "ADD2", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[7].setClock(clock);
                issued.push_back(i);
                rS[7].setImm(i.imm);
                rS[7].setRd(i.rd);
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[7].setQk(i.rs2);
                q.popInstruction();
                i.issueTime = clock;
                rS[7].setClock(clock);
                issued.push_back(i);
                rS[7].setImm(i.imm);
                rS[7].setRd(i.rd);
            }
            
            
        }
        
        
        
        
        else if(rS[8].getBusy()==false){
            rS[8].setBusy(true);
            rS[8].setOp('s');
           
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[8].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "ADD3", 1);
                rS[8].setImm(i.imm);
                rS[8].setRd(i.rd);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[8].setQj(i.rs1);
                rS[8].setImm(i.imm);
                rS[8].setRd(i.rd);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[8].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "ADD3", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[8].setClock(clock);
                issued.push_back(i);
                rS[8].setImm(i.imm);
                rS[8].setRd(i.rd);
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[8].setQk(i.rs2);
                q.popInstruction();
                i.issueTime = clock;
                rS[8].setClock(clock);
                issued.push_back(i);
                rS[8].setImm(i.imm);
                rS[8].setRd(i.rd);
            }
            
            
        }
      
        
        
        
        
        
    }
    
    //addi requires rd rs1 and imm
    else if(i.instName=="ADDI"){
        
        
        
        if(rS[6].getBusy()==false){
            rS[6].setBusy(true);
            rS[6].setOp('a');
            if(regS.getRegStat(i.rs1).first==0){
                rS[6].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "ADD1", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[6].setClock(clock);
                issued.push_back(i);
                rS[6].setImm(i.imm);
                rS[6].setRd(i.rd);
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[6].setQj(i.rs1);
                q.popInstruction();
                i.issueTime = clock;
                rS[6].setClock(clock);
                issued.push_back(i);
                rS[6].setImm(i.imm);
                rS[6].setRd(i.rd);
                
            }
            
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[6].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "ADD1", 1);
                rS[6].setImm(i.imm);
                rS[6].setRd(i.rd);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[6].setQk(i.rs2);
                rS[6].setImm(i.imm);
                rS[6].setRd(i.rd);
               
            }
            
            
            
            
            
        }
        
        
        
        
        //rS[7] check
        else if(rS[7].getBusy()==false){
            rS[7].setBusy(true);
            rS[7].setOp('s');
            rS[7].setImm(i.imm);
            
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[7].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "ADD2", 1);
                rS[7].setImm(i.imm);
                rS[7].setRd(i.rd);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[7].setQj(i.rs1);
                rS[7].setImm(i.imm);
                rS[7].setRd(i.rd);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[7].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "ADD2", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[7].setClock(clock);
                issued.push_back(i);
                rS[7].setImm(i.imm);
                rS[7].setRd(i.rd);
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[7].setQk(i.rs2);
                q.popInstruction();
                i.issueTime = clock;
                rS[7].setClock(clock);
                issued.push_back(i);
                rS[7].setImm(i.imm);
                rS[7].setRd(i.rd);
            }
            
            
        }
        
        //rS[8] check
        else if(rS[8].getBusy()==false){
            rS[8].setBusy(true);
            rS[8].setOp('s');
           
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[8].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "ADD3", 1);
                rS[8].setImm(i.imm);
                rS[8].setRd(i.rd);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[8].setQj(i.rs1);
                rS[8].setImm(i.imm);
                rS[8].setRd(i.rd);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[8].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "ADD3", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[8].setClock(clock);
                issued.push_back(i);
                rS[8].setImm(i.imm);
                rS[8].setRd(i.rd);
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[8].setQk(i.rs2);
                q.popInstruction();
                i.issueTime = clock;
                rS[8].setClock(clock);
                issued.push_back(i);
                rS[8].setImm(i.imm);
                rS[8].setRd(i.rd);
            }
            
            
        }
        
    }
    
    //neg requires rs1 and rd
    // rS[9]
        
        
    else if(i.instName=="NEG"){
        
        
            if(rS[9].getBusy()==false){
                rS[9].setBusy(true);
                rS[9].setOp('l');
                if(regS.getRegStat(i.rs1).first==0){
                    rS[9].setVj(rf.getRegFile(i.rs1));
                    regS.modifyRegS(i.rd, "NEG1", 1);
                    q.popInstruction();
                    i.issueTime = clock;
                    rS[9].setClock(clock);
                    issued.push_back(i);
                    rS[9].setImm(i.imm);
                    rS[9].setRd(i.rd);
                    
                }
                else if(regS.getRegStat(i.rs1).first==1){
                    
                    rS[9].setQj(i.rs1);
                    q.popInstruction();
                    i.issueTime = clock;
                    rS[9].setClock(clock);
                    issued.push_back(i);
                    rS[9].setImm(i.imm);
                    rS[9].setRd(i.rd);
                    
                }
                
            }
        
        
    }
    
    //abs requires rs1 and rd
    //rS[10]
        
        
    else if(i.instName=="ABS"){
        
        
        
            if(rS[10].getBusy()==false){
                rS[10].setBusy(true);
                rS[10].setOp('l');
                if(regS.getRegStat(i.rs1).first==0){
                    rS[10].setVj(rf.getRegFile(i.rs1));
                    regS.modifyRegS(i.rd, "ABS1", 1);
                    q.popInstruction();
                    i.issueTime = clock;
                    rS[10].setClock(clock);
                    issued.push_back(i);
                    rS[10].setImm(i.imm);
                    rS[10].setRd(i.rd);
                    
                }
                else if(regS.getRegStat(i.rs1).first==1){
                    
                    rS[10].setQj(i.rs1);
                    q.popInstruction();
                    i.issueTime = clock;
                    rS[10].setClock(clock);
                    issued.push_back(i);
                    rS[10].setImm(i.imm);
                    rS[10].setRd(i.rd);
                    
                }
                
            }
        
        
    }
    
    //Div requires rs1 rs2 and rd
        
    //rS[11]
    
    else if(i.instName=="DIV"){
        
        if(rS[11].getBusy()==false){
            rS[11].setBusy(true);
            rS[11].setOp('a');
            if(regS.getRegStat(i.rs1).first==0){
                rS[11].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rd, "DIV1", 1);
                q.popInstruction();
                i.issueTime = clock;
                rS[11].setClock(clock);
                issued.push_back(i);
                rS[11].setImm(i.imm);
                rS[11].setRd(i.rd);
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                rS[11].setQj(i.rs1);
                q.popInstruction();
                i.issueTime = clock;
                rS[11].setClock(clock);
                issued.push_back(i);
                rS[11].setImm(i.imm);
                rS[11].setRd(i.rd);
            }
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[11].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rd, "DIV1", 1);
                rS[11].setImm(i.imm);
                rS[11].setRd(i.rd);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[11].setQk(i.rs2);
                rS[11].setImm(i.imm);
                rS[11].setRd(i.rd);
               
            }
            
        }
        
    }
    
    
}










void integration::executeInstructions( resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem){
    
    
    //LW execution
    //condition Qj snd Qk  == -1, the reservation station should also
    // be busy (Qj and QK are always set to -1) and no conflicting address
    //first cycle we compute the effective address
    
    if((rS[0].getBusy()==1)&&(rS[0].getQj()==-1)&&(rS[0].getQk()==-1)){
       
            rS[0].setA(rS[0].getVj()+rS[0].getImm());
            
            if(clock - rS[0].getClock()>= 1){
                
                if(rS[0].getStartExec()==-1){
                rS[0].setStartExec(clock);
                    cout << rS[0].getStartExec() << endl;
                }
            }
            
            if(clock - rS[0].getStartExec() >= 4){
                if((rS[0].getA()==rS[1].getA())|| (rS[0].getA()==rS[2].getA()) || (rS[0].getA()==rS[3].getA()) ){
                
                    if((rS[0].getClock()<rS[1].getClock())||(rS[0].getClock()<rS[2].getClock())||(rS[0].getClock()<rS[3].getClock())){
                        
                        rS[0].setEndExec(clock);
                        
                        
                        
                        wbQueue a;
                        a.value = mem.dataGetter(rS[0].getA());
                        a.index = rS[0].getRd();
                        writeBackQueue.push_back(a);
                        rS[0].setBusy(false);

                    }
                    
                } else {
                    
                    
                    rS[0].setEndExec(clock);
                    
                    
                    
                    wbQueue a;
                    a.value = mem.dataGetter(rS[0].getA());
                    a.index = rS[0].getRd();
                    writeBackQueue.push_back(a);
                    rS[0].setBusy(false);
                    
                    
                }
                
            }
        
    
        
    }
    
    //LW second rS
    if((rS[1].getBusy()==1)&&(rS[1].getQj()==-1)&&(rS[1].getQk()==-1)){
       
        
        
        
        rS[1].setA(rS[1].getVj()+rS[1].getImm());
        
        if(clock - rS[1].getClock()>= 1){
            
            if(rS[1].getStartExec()==-1){
            rS[1].setStartExec(clock);
            }

        }
        
        
        if(clock - rS[1].getStartExec() >= 4){
            
            if((rS[2].getA()==rS[0].getA())|| (rS[2].getA()==rS[1].getA()) || (rS[2].getA()==rS[3].getA()) ){
            
                if((rS[2].getClock()<rS[0].getClock())||(rS[2].getClock()<rS[1].getClock())||(rS[2].getClock()<rS[3].getClock())){
                    
                    rS[2].setEndExec(clock);
                    
                    
                    wbQueue a;
                    a.value = mem.dataGetter(rS[1].getA());
                    a.index = rS[1].getRd();
                    writeBackQueue.push_back(a);
                    rS[1].setBusy(false);
                
                } else {
                    
                    
                    rS[0].setEndExec(clock);
                    
                    
                    
                    wbQueue a;
                    a.value = mem.dataGetter(rS[1].getA());
                    a.index = rS[1].getRd();
                    writeBackQueue.push_back(a);
                    rS[1].setBusy(false);
                    
                    
                }

                
            }
            
        }
        
        
        
        
        
    }
    
    //SW first rS
    if((rS[2].getBusy()==1)&&(rS[2].getQj()==-1)&&(rS[2].getQk()==-1)){
       
        
           
            
            rS[2].setA(rS[2].getVj()+rS[2].getImm());
            
            if(clock - rS[2].getClock()>= 1){
                
                if(rS[2].getStartExec()==-1){
                rS[2].setStartExec(clock);
                }

            }
            
            
            if(clock - rS[2].getStartExec() >= 2){
                
                if((rS[2].getA()==rS[0].getA())|| (rS[2].getA()==rS[1].getA()) || (rS[2].getA()==rS[3].getA()) ){
                
                    if((rS[2].getClock()<rS[0].getClock())||(rS[2].getClock()<rS[1].getClock())||(rS[2].getClock()<rS[3].getClock())){
                        
                        rS[2].setEndExec(clock);
                        rS[2].setBusy(false);
                        
                        
                    
                    }
                    
                }else {
                    
                    
                    rS[2].setEndExec(clock);
                    rS[2].setBusy(false);
                    
                    
                    
                    wbQueue a;
                    
                    
                    
                }

                
            }
        
        
        
        
        
    }
    
    
    //SW second rS
    
    if((rS[3].getBusy()==1)&&(rS[3].getQj()==-1)&&(rS[3].getQk()==-1)){
       
        
        rS[3].setA(rS[3].getVj()+rS[3].getImm());
        
        if(clock - rS[3].getClock()>= 1){
            
            if(rS[3].getStartExec()==-1){
            rS[3].setStartExec(clock);
            }
        
            
        }
        
        
        if(clock - rS[3].getStartExec() >= 2){
            
            if((rS[3].getA()==rS[0].getA())|| (rS[3].getA()==rS[1].getA()) || (rS[3].getA()==rS[2].getA()) ){
            
                if((rS[3].getClock()<rS[0].getClock())||(rS[3].getClock()<rS[1].getClock())||(rS[3].getClock()<rS[2].getClock())){
                    
                    rS[3].setEndExec(clock);
                    rS[3].setBusy(false);
                
                }
                
            }
            else {
                
                
                rS[3].setEndExec(clock);
                rS[3].setBusy(false);
                
                
                
                wbQueue a;
                
                
                
            }

            
            
            
        }
        
    
        
    }
   
    
    //BEQ
    
    
    
    if((rS[4].getBusy()==1)&&(rS[4].getQj()==-1)&&(rS[4].getQk()==-1)){
        
        if(rS[4].getStartExec()==-1){
        rS[4].setStartExec(clock);
        }
        
        
        
        if(clock - rS[4].getStartExec() == 2){
            
            rS[4].setEndExec(clock);
            rS[4].setBusy(false);
            
            
        }
        
    }
    
    
    
    
    
    //JAL/JALR
    
    
    if((rS[5].getBusy()==1)&&(rS[5].getQj()==-1)&&(rS[5].getQk()==-1)){
        
        if(rS[5].getStartExec()==-1){
        rS[5].setStartExec(clock);
        }
        
        
        if(clock - rS[5].getStartExec() == 2){
            
            rS[5].setEndExec(clock);
            rS[5].setBusy(false);
            
            
        }
        
    }
    
    
    
    
    
    //ADD/ADDI
    
    
    if((rS[6].getBusy()==1)&&(rS[6].getQj()==-1)&&(rS[6].getQk()==-1)){
        
        if(rS[6].getStartExec()==-1){
        rS[6].setStartExec(clock);
        }
        
        if(clock - rS[6].getStartExec() == 3){
            
            rS[6].setEndExec(clock);
            
            
            wbQueue a;
            a.value = rS[6].getVj() + rS[6].getVk();
            a.index = rS[6].getRd();
            writeBackQueue.push_back(a);
            rS[6].setBusy(false);
            
            
            
        }
      
        
    }
    
    
    if((rS[7].getBusy()==1)&&(rS[7].getQj()==-1)&&(rS[7].getQk()==-1)){
        
        
        if(rS[7].getStartExec()==-1){
        rS[7].setStartExec(clock);
        }
        
        if(clock - rS[7].getStartExec() == 3){
            
            rS[7].setEndExec(clock);
            
            wbQueue a;
            a.value = rS[7].getVj() + rS[7].getVk();
            a.index = rS[7].getRd();
            writeBackQueue.push_back(a);
            rS[7].setBusy(false);
            
        }
        
        
    }
    
    if((rS[8].getBusy()==1)&&(rS[8].getQj()==-1)&&(rS[8].getQk()==-1)){
        
        if(rS[8].getStartExec()==-1){
        rS[8].setStartExec(clock);
        }
        
        
        if(clock - rS[8].getStartExec() == 3){
            
            rS[8].setEndExec(clock);
            
            wbQueue a;
            a.value = rS[8].getVj() + rS[8].getVk();
            a.index = rS[8].getRd();
            writeBackQueue.push_back(a);
            rS[8].setBusy(false);
            
            
            
        }
        
    }
    
    
    
    //NEG
    
    
    
    if((rS[9].getBusy()==1)&&(rS[9].getQj()==-1)&&(rS[9].getQk()==-1)){
        
        if(rS[9].getStartExec()==-1){
        rS[9].setStartExec(clock);
        }
        
        if(clock - rS[9].getStartExec() == 4){
            
            rS[9].setEndExec(clock);
            
            wbQueue a;
            a.value = rS[9].getVj()*-1;
            a.index = rS[9].getRd();
            writeBackQueue.push_back(a);
            rS[9].setBusy(false);
            
            
        }
        
        
    }
    
    
    
    //ABS
    
    if((rS[10].getBusy()==1)&&(rS[10].getQj()==-1)&&(rS[10].getQk()==-1)){

        if(rS[10].getStartExec()==-1){
        rS[10].setStartExec(clock);
        }
        
        if(clock - rS[10].getStartExec() == 3){
            
            rS[10].setEndExec(clock);
            
            
            wbQueue a;
            a.value = abs(rS[10].getVj()) ;
            a.index = rS[10].getRd();
            writeBackQueue.push_back(a);
            rS[10].setBusy(false);
            
            
            
        }
    }
    
    
    
    
    //DIV
    
    if((rS[11].getBusy()==1)&&(rS[11].getQj()==-1)&&(rS[11].getQk()==-1)){
        
        if(rS[11].getStartExec()==-1){
        rS[11].setStartExec(clock);
        }
        
        
        
        if(clock - rS[11].getStartExec() == 3){
            
            rS[11].setEndExec(clock);
            
            wbQueue a;
            a.value = rS[11].getVj() / rS[11].getVk();
            a.index = rS[11].getRd();
            writeBackQueue.push_back(a);
            rS[11].setBusy(false);
            
            
            
        }
        
    }
    
    
    
}






//In the write back stage we need to broadcast the value to
// regStat and the other reservations stations
// mark the current reservations station as not busy



void integration::wB( resvStation rS[], regStat &regS , regFile &rf, vector<inst> &issued, dataMem &mem, int valueToWrite, int rd){
    
//the write back function shall take the rd and write back to the register file the new value
// and broadcast the value to all reservation stations waiting for this value along with updating the regStat to the new reservation station that is to forward the value later on
    
    
    rf.setRegFile(valueToWrite, rd);
    
    
    
    for(int i=0; i<12; i++){
        
        
        if((rS[i].getQj()==rd)){
            rS[i].setQj(-1);
            rS[i].setVj(valueToWrite);

        }

        if((rS[i].getQk()==rd)){
            
            rS[i].setQk(-1);
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





