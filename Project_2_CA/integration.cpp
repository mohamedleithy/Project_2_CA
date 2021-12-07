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
        
     issueInstructions( q, resvStations, rS, rf);
        
        clock++; 
    }
    
}





//issueing only

void integration::issueInstructions(instQueue &q, resvStation rS[], regStat &regS, regFile &rf){
    
    
    
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
                regS.modifyRegS(i.rs1, "LW2", 1);
                q.popInstruction();
            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[1].setQj(i.rs1);
                q.popInstruction();
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
                regS.modifyRegS(i.rs1, "SW1", 1);
                q.popInstruction();
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[2].setQj(i.rs1);
                q.popInstruction();
                
            }
            
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[2].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rs2, "SW1", 1);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[2].setQk(i.rs2);
               
            }
            
            
            
            
            
        }
        
        
        
        
        //rS[3] check
        else if(rS[3].getBusy()==false){
            rS[3].setBusy(true);
            rS[3].setOp('s');
           
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[3].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rs1, "SW2", 1);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[3].setQj(i.rs1);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[3].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rs2, "SW2", 1);
                q.popInstruction();
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[3].setQk(i.rs2);
                q.popInstruction();
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
                regS.modifyRegS(i.rs1, "BEQ1", 1);
                q.popInstruction();
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[4].setQj(i.rs1);
                q.popInstruction();
                
            }
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[4].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rs2, "BEQ1", 1);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[4].setQk(i.rs2);
               
            }
            
            
            
            
            
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
       
        
       
        
    }
    
    // Jal requires rd and imm
    // rS[5]
    else if(i.instName=="JAL"){
        
        if(rS[5].getBusy()==false){
            rS[5].setBusy(true);
            rS[5].setOp('j');
            q.popInstruction();
        }
        
    }
    // Jalr requires rd and rs1
    else if(i.instName=="JALR"){
        
     
        
        
        if(rS[5].getBusy()==false){
            rS[5].setBusy(true);
            rS[5].setOp('b');
            if(regS.getRegStat(i.rs1).first==0){
                rS[5].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rs1, "BEQ1", 1);
                q.popInstruction();
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[4].setQj(i.rs1);
                q.popInstruction();
                
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
                regS.modifyRegS(i.rs1, "ADD1", 1);
                q.popInstruction();
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[6].setQj(i.rs1);
                q.popInstruction();
                
            }
            
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[6].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rs2, "ADD1", 1);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[6].setQk(i.rs2);
               
            }
            
            
            
            
            
        }
        
        
        
        
        //rS[7] check
        else if(rS[7].getBusy()==false){
            rS[7].setBusy(true);
            rS[7].setOp('s');
           
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[7].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rs1, "ADD2", 1);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[7].setQj(i.rs1);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[7].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rs2, "ADD2", 1);
                q.popInstruction();
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[7].setQk(i.rs2);
                q.popInstruction();
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
                regS.modifyRegS(i.rs1, "ADD1", 1);
                q.popInstruction();
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                
                rS[6].setQj(i.rs1);
                q.popInstruction();
                
            }
            
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[6].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rs2, "ADD1", 1);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[6].setQk(i.rs2);
               
            }
            
            
            
            
            
        }
        
        
        
        
        //rS[7] check
        else if(rS[7].getBusy()==false){
            rS[7].setBusy(true);
            rS[7].setOp('s');
           
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[7].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rs1, "ADD2", 1);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[7].setQj(i.rs1);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[7].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rs2, "ADD2", 1);
                q.popInstruction();
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[7].setQk(i.rs2);
                q.popInstruction();
            }
            
            
        }
        
        //rS[8] check
        else if(rS[8].getBusy()==false){
            rS[8].setBusy(true);
            rS[8].setOp('s');
           
            
            //checking for rs1
            
            if(regS.getRegStat(i.rs1).first==0){
                rS[8].setVj(rf.getRegFile(i.rs1));
                regS.modifyRegS(i.rs1, "ADD3", 1);

            }
            else if(regS.getRegStat(i.rs1).first==1){
                rS[8].setQj(i.rs1);
            }
            
            
            
            //checking for rs2
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[8].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rs2, "ADD3", 1);
                q.popInstruction();
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[8].setQk(i.rs2);
                q.popInstruction();
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
                    regS.modifyRegS(i.rs1, "NEG1", 1);
                    q.popInstruction();
                    
                }
                else if(regS.getRegStat(i.rs1).first==1){
                    
                    rS[9].setQj(i.rs1);
                    q.popInstruction();
                    
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
                    regS.modifyRegS(i.rs1, "ABS1", 1);
                    q.popInstruction();
                    
                }
                else if(regS.getRegStat(i.rs1).first==1){
                    
                    rS[10].setQj(i.rs1);
                    q.popInstruction();
                    
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
                regS.modifyRegS(i.rs1, "DIV1", 1);
                q.popInstruction();
                
            }
            
            else if(regS.getRegStat(i.rs1).first==1){
                rS[11].setQj(i.rs1);
                q.popInstruction();
            }
            
            if(regS.getRegStat(i.rs2).first==0){
                rS[11].setVk(rf.getRegFile(i.rs2));
                regS.modifyRegS(i.rs2, "DIV1", 1);
                
            }
            else if(regS.getRegStat(i.rs2).first==1){
                rS[11].setQk(i.rs2);
               
            }
            
        }
        
    }
    
    
}

