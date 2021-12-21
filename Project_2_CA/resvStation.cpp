//
//  resvStation.cpp
//  Project_2_CA
//
//  Created by Mohamed Ellethy on 02/12/2021.
//

#include "resvStation.hpp"
resvStation::resvStation(){
    
     busy = false;
     op = 'z';
     vj = -1;
     vk= -1;
     qj= -1;
     qk = -1;
     a = -1;
    name = "";
    clock = 0;
    imm = 0;
    rd = 0;
    
    startExec = -1;
    endExec = -1;
    ind = 0;
    
    
}


void resvStation::setName(string s){
    
    name  = s;
    
    
}
string resvStation::getName(){
    
    return name;
    
}

void resvStation::setBusy(bool x){
    
    busy = x;
    
    
    
}
bool resvStation::getBusy(){
    
    
    
    return busy;
}


void resvStation::setOp(char c){
    
    
    op = c;
    
    
    
    
}
char resvStation::getOp(){
    
    
    return op;
    
}

void resvStation::setVj(int x){
    
    
    vj = x;
    
}
int resvStation::getVj(){
    
    return vj;
    
}


void resvStation::setVk(int x){
    
    vk =x;
    
    
}
int resvStation::getVk(){
    
    return vk;
    
}



void resvStation::setQj(int x){
    
    
    qj = x;
    
    
    
}
int resvStation::getQj(){
    
    
    return  qj;
}



void resvStation::setQk(int x){
    
    
    qk = x;
}
int resvStation::getQk(){
    
    
    return qk;
    
}



void resvStation::setA(int x){
    
    
    a = x;
    
    
}
int resvStation::getA(){
    

    return  a;
    
}



void resvStation::setClock(int clockk){
    
    
    clock = clockk;
    
    
}
int resvStation::getClock(){
    
    
    
    return clock; 
}



void resvStation::setImm(int immm){
    
    imm = immm;
    
}
int resvStation::getImm(){
    
    
    return imm;
    
    
}


void resvStation::setRd(int rdd){
    
    rd = rdd;
    
}
int resvStation::getRd(){
    
    
    
    return rd;
    
    
}




void resvStation::setStartExec(int startExecc){
    
    startExec = startExecc;
    
    
}



int resvStation::getStartExec(){
    
    
   
    return startExec;
    
    
}



void resvStation::setEndExec(int endExecc){
    
    
  
    endExec = endExecc;
    
}



int resvStation::getEndExec(){
    
    return endExec;
    
}


void resvStation::flush(){
    
    
    
    busy = false;
    op = 'z';
    vj = -1;
    vk= -1;
    qj= -1;
    qk = -1;
    a = -1;
   name = "";
   clock = 0;
   imm = 0;
   rd = 0;
   
   startExec = -1;
   endExec = -1; 
    
    
}

void resvStation::setIndex(int i){
    
    ind = i;
}


int resvStation::getIndex(){
    
    return ind;
}
