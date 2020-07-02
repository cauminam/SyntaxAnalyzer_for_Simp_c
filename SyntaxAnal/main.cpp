//
//  main.cpp
//  SyntaxAnal
//
//  Created by 양준식 on 2020/06/27.
//  Copyright © 2020 양준식. All rights reserved.
//

#include <iostream>
using namespace std;
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <cstring>
#include <fstream>
#include "SLR_parsing_table.h"
#include "Production.h"


stack<int> GS;//테이블 쫓아가는과정에서 숫자를 저장할 stack
stack<string> imsi;
//lexical analyzer에서 global Queue가 string형이었음.
vector<string> input;//이것이 lexical에서 받아온 string이라고 하자. e.g. id*id$ 앞쪽에서 지우고 다시 원소 넣고 해야되기 때문에,
//string객체는 [0]과 같이 인덱스로 접근 가능함을 이용할 것임.

// 애초에 lexical anal에서 ,Queue에서 있었던 대로, 하나씩 빼서 string형태로 Syntax analyzer로 줌.




int main(int argc, const char * argv[]) {
    
   string input_file_name = argv[1];
    
    ifstream is;
    is.open(input_file_name);
    if(!is) { //인풋 파일이 안 열린 경우
        cout << "error occured while opening file" << endl;
        exit(1);
    }
    string oneline;
    
    
    while (!is.eof()){//파일 끝까지
         getline(is,oneline);//한줄 씩 읽어와서
        
        input.push_back(oneline);
    }is.close();
    
    input.push_back("$");
    
 
    
    
    cout<<"인풋 사이즈는 "<<input.size()<<endl;
    int splitter=0;//0이라는 것은 초기상태이므로, 배열의 0번 원소 앞을 나타내는 것
    
    GS.push(0);
    //next-input-symbol, 즉, splitter바로 뒤의 토큰은 splitter숫자를 이용해,
    //splitter뒤의 모든 토큰들을  stack에 넣었다가 reduce할 부분 다 해결하고서, stack에서 다시 갖고와서 vector에 넣음
    string tableResult;
    
    
    string temp,tempS;
    int tempIS;//숫자로 바꿔서 저장할 곳.
    
    string tempR1, tempR2;
    int production_num;
    int s_trash;
    int tempGOTOnum;
    int imsipushTempInt;
    
    while(true){
        tableResult=SLRtable[GS.top()][inputSymbolMap[input[splitter]]];
      
        tempR2="";//비우기
        
     ///////////////////////  ///////////////////////  ////////////////////// 오류인 경우  ///////////////////////  ///////////////////////  ///////////////////////  ///////////////////////
        
        if(tableResult=="n"){//error인 경우
            
          
            cout<<"This input cannot be accepted by SLR parsing table(ACTION)";
            return 0;
        }
       ///////////////////////  ///////////////////////  //////////////////////. 오류인 경우  ///////////////////////  ///////////////////////  ///////////////////////  ///////////////////////
        ///
        ///
        ///
     ///////////////////////  ///////////////////////  //////////////////////SHIFT 인 경우/  ///////////////////////  ///////////////////////  ///////////////////////  ///////////////////////
        else if(tableResult.front()=='s'){//테이블에서 가봤더니 's'로 시작하는경우
             temp=tableResult;
            
            cout<<"쉬프트 넘버는 " <<temp<<"입니다"<<endl;///////////%%%%%%%%%%%%
            
            for(int i=1;i<temp.size();i++){//s만 떼주고 숫자로 가져오기
                tempS+=temp[i];//string 연결
            }
            
            
            tempIS=stoi(tempS);
            
            GS.push(tempIS);//숫자로 바꾼거를 push.
            
            cout<<"스택에"<<tempIS<<"가 방금 들어감"<<endl;//////////%%%%%%%%%%
            
            //splitter 오른쪽을 한 칸 이동시켜야 함.
            splitter++;
            tempS="";
        
    }
    ///////////////////////  ///////////////////////  //////////////////////SHIFT 인 경우/  ///////////////////////  ///////////////////////  ///////////////////////  ///////////////////////
        /*
        
      
         int tempGOTOnum;*/
        
        else if(tableResult[0]=='R'){//테이블에서 가봤더니 'R'로 시작하는경우
            tempR2="";
            tempR1=tableResult;//R(10)과 같은 string을 저장
            //이제 얘를 10처럼 숫자만 떼와야됨
            
            cout<<"리듀스를 "<<tempR1<<"번호로 진행합니다"<<endl;
            
            for(int i=2;i<tempR1.size()-1;i++){//0,1에 해당하는 R(를 안 받고, 마지막 )도 안 받음
                tempR2+=tempR1[i];
            }//tempR2는 이제 숫자로 완성됨
            
            production_num=stoi(tempR2);//int형으로 바꾸기 즉 R(10)을 int 형 10으로 받은거임
            
            cout<<tempR1<<"해당 리듀스에는 "<<production_num<<"번 프로덕션쓰임"<<endl;
          //즉 몇 번 production으로 reduce를 해야하는지 알게 된 것임.
            
            
            s_trash= prodRHS[production_num];//해당 프로덕션 번호에서 RHS 토큰 수가 몇개인지 받아서 그 수만큼 stack에서 pop해서 버림
            cout<<"RHS갯수는 "<<s_trash<<"개가 필요함"<<endl;
            
            if(s_trash!=0){
            for(int j=0;j<s_trash;j++){//해당 production에서 RHS의 토큰 수 만큼 stack에서 pop해서 버림.
                cout<<"Reduce로 인해 "<<GS.top()<<"을 pop해서 버림"<<endl;
                GS.pop();
              
             }
            }
            
            else{
                cout<<"RHS갯수가 0개여서 stack에서 따로 팝 안함"<<endl;
            }
            
            //GOTO 해주는 부분 ㅎㅎ 새로운 stack top과 새로들어온 해당 프로덕션 번호의 LHS로 GOTO로 움직여서 stack에 push해주는 것 까지가 R에서의 임무.
            ////////여기서 input이 CODE|$ 상태면 accept해줘야함!! GOTO에 CODE에 관한게 있기 떄문에... 그 전에 멈춰줘야함.??
            cout<<"프로덕션 넘버가 "<<production_num<<"이고," <<endl<<"프로덕션 LHS가 "<<prodLHS[production_num]<<"이고"<<endl<<"현재 스택 탑은 "<<GS.top()<<"이다"<<endl;
            if(production_num==0){
                cout<<"sentence ACCEPT !! CONGRATULATION"<<endl;
                                                   return 0;
            }
            tempGOTOnum=stoi(SLRtable[GS.top()][inputSymbolMap[prodLHS[production_num]]]);//확인요망
            
            if(tempGOTOnum==85){
                cout<<"This input cannot be accepted by SLR parsing table(GOTO)";
                return 0;
            }
            cout<<"스택에"<<tempGOTOnum<<"넣는다"<<endl;
            
            GS.push(tempGOTOnum);
            
            
           //이제 input에서 RHS지우고 LHS내용으로 바꿔주고나서,
            
            //1번 RHS지우고 LHS로 바꿔주는 부분
            
            //vector는 맨 뒤 참조하는 v.back();과 맨 뒤 없애주는 v.pop_back();이용.
            //stack은 push()랑. 빼서 다시 저장할 때는 top()으로 참조해서 할 거 다 하고, pop()으로 삭제.
            
           imsipushTempInt=((int)input.size())-splitter;
            
            for(int k=0;k<imsipushTempInt;k++){
                cout<<"현재 SPLITTER 번호는 "<<splitter<<endl;
                cout<<"스플리터 뒤에있는"<<input.back()<<"를 임시 스택에 넣음"<<endl;
                imsi.push(input.back());//splitter뒤에있는 input의 토큰을 잠시 imsi stack에 넣어둔다.
                input.pop_back();//imsi에 넣어둔 토큰 제거.
                
            }
            //이제 input에는 스플리터 앞에 있는 토큰들만 남아있다.
            //위에서 사용한 s_trash가 지금 하는 reduce에 사용되는 production의 RHS토큰 갯수를 갖고있고,
            //prodLHS[production_num]이 지금 하는 reduce에 사용되는 production의 LHS에 대한 string객체임.
            //T*E|$ -> E|$로 reduce하면, splitter는3이었다가 1이 된다. 즉, (RHS갯수-1)만큼을 splitter에서 빼줘야함.
            if(s_trash!=0){
            for(int l=0;l<s_trash;l++){//reduce에서 사용되는 RHS의 토큰들을 모두 input에서 없애줌
                cout<<"리듀스에 사용되는 RHS인 "<<input.back()<<"을 팝해서 없앰"<<endl;
                input.pop_back();
            }
            }
            
            cout<<"새롭게 인풋스트링에 "<<prodLHS[production_num]<<"를 넣음"<<endl;
            input.push_back(prodLHS[production_num]);//reduce에서의 LHS토큰을 새로이 input에 넣어줌.
            
            //이제 다시 imsi에서 input으로 넣어주면 끝
          
                     
            
            while(imsi.empty()!=true){//imsi stack에 넣어뒀던걸 다시 input으로 넣어줌
            input.push_back(imsi.top());
            imsi.pop();
            }
            
              splitter++;
              splitter-=s_trash;//얘는 s_trash가 0이어도 상관없을 듯???
         
            if( input.front()=="S" && input.back()=="$" ){
                                  cout<<"sentence ACCEPT !! CONGRATULATIONs"<<endl;
                                    return 0;
                                    
                                }
           
         
            
            cout<<splitter<<" 스플리터 현재 번호"<<endl;
            cout<<" 현재 input상태"<<endl;
            for(int g=0;g<input.size();g++){
                cout<<input[g]<<"  ";
            }
       
            
           }
    
        
        
}
    
    
    
}
