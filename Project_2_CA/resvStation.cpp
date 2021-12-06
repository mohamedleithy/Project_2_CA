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
