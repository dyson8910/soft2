#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

class LabMember{
protected:
  char name[32];

public:
  LabMember(const char* _name){
    strcpy(name, _name);
  }
  ~LabMember(){}
  char* SetName(char* _name){
    sprintf(name, "%s", _name);
  }
  const char* GetName() const{
    return name;
  }
  virtual void PrintInfo(){};
  bool operator<(const LabMember l)const{
    return (strcmp(GetName(), l.GetName())<0 ? true:false);
  }
  bool operator>(const LabMember l)const{
    return (strcmp(GetName(), l.GetName())>0 ? true:false);
  }
};

bool labmember_less(LabMember* a,LabMember* b){
  return (strcmp(a->GetName(),b->GetName())<0 ? true: false);
}

/*
int compare(const void* a, const void* b){
  return (strcmp((*((const LabMember**)(a)))->GetName(), (*((const LabMember**)(b)))->GetName()));
}
*/

class Professor : public LabMember{
private:
  int room;

public:
  Professor(const char* _name) : LabMember(_name){
    room = 0;
  }
  ~Professor(){}
  void SetRoom(int _room){
    room = _room;
  }
  int GetRoom(){
    return room;
  }
  void PrintInfo(){
    printf("professor name Prof. %s (%d)\n",GetName(),GetRoom());
  }
};

class Student : public LabMember{
private:
  int grade;

public:
  Student(const char* _name) : LabMember(_name){
    grade = 0;
  }
  ~Student(){}
  char* SetGrade(int _grade){
    grade = _grade;
  }
  int GetGrade(){
    return grade;
  }
  void PrintInfo(){
    printf("student name Mr. %s (%d)\n",GetName(),GetGrade());
  }
};

class Lab{
private:
  //LabMember* members[36];
  std::vector<LabMember *>members;
  int n_members;

public:
  Lab(){
    n_members =0;
  }
  ~Lab(){}
  void AddMember(LabMember* new_member){
    //members[n_members] = new_member;
    members.push_back(new_member);
    n_members++;
  }
  void PrintMember(){
    int i;
    //qsort(members,n_members,sizeof(LabMember*),compare);
    std::sort(members.begin(),members.end(),labmember_less);
    for(int i = 0; i<n_members;i++){
      members[i]->PrintInfo();
    }
  }
};

int main(int argc,char* argv[]){
  Lab jsk;
  Professor *p1 = new Professor("");
  Professor *p2 = new Professor("");
  Professor *p3 = new Professor("");
  Student *s1 = new Student("");
  Student *s2 = new Student("");
  Student *s3 = new Student("");

  p1->SetName("yamada");
  p2->SetName("endo");
  p3->SetName("takahashi");
  s1->SetName("suzuki");
  s2->SetName("okada");
  s3->SetName("fujita");
  p1->SetRoom(123);
  p2->SetRoom(456);
  p3->SetRoom(789);
  s1->SetGrade(4);
  s2->SetGrade(3);
  s3->SetGrade(2);
  jsk.AddMember(p1);
  jsk.AddMember(p2);
  jsk.AddMember(p3);
  jsk.AddMember(s1);
  jsk.AddMember(s2);
  jsk.AddMember(s3);

  jsk.PrintMember();

  return 0;
}
