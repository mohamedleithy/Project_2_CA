//
//  instQueue.cpp
//  Project_2_CA
//
//  Created by Mohamed Ellethy on 02/12/2021.
//

#include "instQueue.hpp"


instQueue::instQueue(){
    
    counter = 0;
}




void instQueue::parseInst(string filePath){
    vector <vector <string> > data;
    
    ifstream infile ("/Users/leithy/Desktop/Arch_proj_2/Test_cases/test1.txt");
    
    while (infile) {
        string s;
        if (!getline( infile, s )) break;
        istringstream ss( s );
        vector <string> record;
        while (ss)
        {
          string s;
          if (!getline( ss, s, ' ' )) break;
          record.push_back( s );
        }
        
        data.push_back( record );
      
        
    }
   
    
    for(int i=0; i<data.size(); i++){
        
        inst a;
        if(data[i][0]=="LW"){
            
            
            a.instName = "LW";
           
            a.rs2 = 0;
            a.rd = (int)(data[i][1][1])-48;
            
            string imm = data[i][2];
            size_t found = imm.find('(');
            string fill = "";
            
            a.rs1 = (int)imm[found+2] - 48;
            
            for(int i=0 ; i<found; i++){
                
                fill += imm[i];
            }
            
            a.imm = stoi(fill);
            a.index = counter;
            counter++;
            
            iQueue.push_back(a);
            
        }
        else if(data[i][0]=="SW"){
            
            a.instName = "SW";
           
            a.rd = 0;
            a.rs2 = (int)(data[i][1][1])-48;
            
            string imm = data[i][2];
            size_t found = imm.find('(');
            string fill = "";
            
            a.rs1 = (int)imm[found+2] - 48;
            
            for(int i=0 ; i<found; i++){
                
                fill += imm[i];
            }
            
           a.imm = stoi(fill);
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
        }
        
        else if(data[i][0]=="BEQ"){
            
            a.instName = "BEQ";
           a.rs1 = (int)data[i][1][1] - 48;
            a.rs2 = (int)data[i][2][1]-48;
            a.rd = 0;
            a.imm = stoi(data[i][3]);
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
            
        }
        
        else if(data[i][0]=="JAL"){
            
            a.instName = "JAL";
            a.rs1 = 0;
            a.rs2 = 0;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = stoi(data[i][2]);
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
            
        }
        
        
        else if(data[i][0]=="JALR"){
            
            a.instName = "JALR";
            a.rs1 = (int)(data[i][2][1])-48;
            a.rs2 = 0;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = 0;
            a.index = counter;
            counter++;
            
            iQueue.push_back(a);
            
        }
        
        
        else if(data[i][0]=="ADD"){
            
            a.instName = "ADD";
            a.rs1 = (int)(data[i][2][1])-48;
            a.rs2 = (int)(data[i][3][1])-48;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = 0;
            a.index = counter;
            counter++;
            
            iQueue.push_back(a);
            
        }
        
        
        else if(data[i][0]=="ADDI"){
            
            a.instName = "ADDI";
            a.rs1 = (int)(data[i][2][1])-48;
            a.rs2 = 0;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = stoi(data[i][3]);
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
        }
        
        
        else if(data[i][0]=="NEG"){
            
            a.instName = "NEG";
            a.rs1 = (int)(data[i][2][1])-48;
            a.rs2 = 0;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = 0;
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
            
        }
        
        
        else if(data[i][0]=="ABS"){
            
            a.instName = "ABS";
            a.rs1 = (int)(data[i][2][1])-48;
            a.rs2 = 0;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = 0;
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
        }
        
        
        else if(data[i][0]=="DIV"){
            
            a.instName = "DIV";
            a.rs1 = (int)(data[i][2][1])-48;
            a.rs2 = (int)(data[i][3][1])-48;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = 0;
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
            
            
        }
        
        
        
        
     
        
        
        
        
        
        
    }
    
    


}




inst instQueue::getInstruction(){
    
    
    return iQueue.front();
    
    
    
}


void instQueue::popInstruction(){
    
    iQueue.erase(iQueue.begin());
    
    
}


vector<inst> instQueue::getQueue(){
    
    

    
    return iQueue;
    
}



void instQueue::setQueue(vector<inst> q){
    
    iQueue = q; 
    
    
    
    
}



void instQueue::parseInstLabel(string filePath){
    
    
    vector <vector <string> > data;
    
    ifstream infile ("/Users/leithy/Desktop/Arch_proj_2/Test_cases/test1.txt");
    
    while (infile) {
        string s;
        if (!getline( infile, s )) break;
        istringstream ss( s );
        vector <string> record;
        while (ss)
        {
          string s;
          if (!getline( ss, s, ' ' )) break;
          record.push_back( s );
        }
        
        data.push_back( record );
      
        
    }
   
    
    for(int i=0; i<data.size(); i++){
        
        inst a;
        if(data[i][0]=="LW"){
            
            
            a.instName = "LW";
           
            a.rs2 = 0;
            a.rd = (int)(data[i][1][1])-48;
            
            string imm = data[i][2];
            size_t found = imm.find('(');
            string fill = "";
            
            a.rs1 = (int)imm[found+2] - 48;
            
            for(int i=0 ; i<found; i++){
                
                fill += imm[i];
            }
            
            a.imm = stoi(fill);
            a.index = counter;
            counter++;
            
            iQueue.push_back(a);
            
        }
        else if(data[i][0]=="SW"){
            
            a.instName = "SW";
           
            a.rd = 0;
            a.rs2 = (int)(data[i][1][1])-48;
            
            string imm = data[i][2];
            size_t found = imm.find('(');
            string fill = "";
            
            a.rs1 = (int)imm[found+2] - 48;
            
            for(int i=0 ; i<found; i++){
                
                fill += imm[i];
            }
            
           a.imm = stoi(fill);
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
        }
        
        else if(data[i][0]=="BEQ"){
            
            a.instName = "BEQ";
           a.rs1 = (int)data[i][1][1] - 48;
            a.rs2 = (int)data[i][2][1]-48;
            a.rd = 0;
            string convToImm = data[i][3];
            convToImm = convToImm+":";
            
            for(int j=0; j<data.size();j++){
    
                
              
                if(convToImm == data[j][0]){
                    
                  
                    if(j-i>0){
                        
                        a.imm = (j-i)-1;
                        
                    }else if(j-i<0){
                        
                        a.imm = (j-i)+1;
                        
                    }
                   
                    
                }
                
                
        
            }
            
            
            
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
            
        }
        
        else if(data[i][0]=="JAL"){
            
            a.instName = "JAL";
            a.rs1 = 0;
            a.rs2 = 0;
            a.rd = (int)(data[i][1][1])-48;
            
         
            
            string convToImm = data[i][3];
            convToImm = convToImm+":";
            
            for(int j=0; j<data.size();j++){
    
                
              
                if(convToImm == data[j][0]){
                    
                    if(j-1>0){
                        
                        a.imm = (j-i)-1;
                        
                    }else if(j-1<0){
                        
                        a.imm = (j-i)+1;
                        
                    }
                    
                }
                
                
        
            }
            
            
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
            
        }
        
        
        else if(data[i][0]=="JALR"){
            
            a.instName = "JALR";
            a.rs1 = (int)(data[i][2][1])-48;
            a.rs2 = 0;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = 0;
            a.index = counter;
            counter++;
            
            iQueue.push_back(a);
            
        }
        
        
        else if(data[i][0]=="ADD"){
            
            a.instName = "ADD";
            a.rs1 = (int)(data[i][2][1])-48;
            a.rs2 = (int)(data[i][3][1])-48;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = 0;
            a.index = counter;
            counter++;
            
            iQueue.push_back(a);
            
        }
        
        
        else if(data[i][0]=="ADDI"){
            
            a.instName = "ADDI";
            a.rs1 = (int)(data[i][2][1])-48;
            a.rs2 = 0;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = stoi(data[i][3]);
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
        }
        
        
        else if(data[i][0]=="NEG"){
            
            a.instName = "NEG";
            a.rs1 = (int)(data[i][2][1])-48;
            a.rs2 = 0;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = 0;
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
            
        }
        
        
        else if(data[i][0]=="ABS"){
            
            a.instName = "ABS";
            a.rs1 = (int)(data[i][2][1])-48;
            a.rs2 = 0;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = 0;
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
        }
        
        
        else if(data[i][0]=="DIV"){
            
            a.instName = "DIV";
            a.rs1 = (int)(data[i][2][1])-48;
            a.rs2 = (int)(data[i][3][1])-48;
            a.rd = (int)(data[i][1][1])-48;
            a.imm = 0;
            a.index = counter;
            counter++;
            iQueue.push_back(a);
            
            
            
        }
        
        
    
    
}


}
