#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

class Database
{
private:
  string nameDB;

public:
  //vector head : [[type, name], [type, name], ..., [type, name]]
  vector <vector <string>> head;

  //vector body : [[data, data, ..., data],
  //              [data, data, ..., data],
  //              [data, data, ..., data],]
  vector <vector <string>> body;

  void show()
  {
    for(int i = 0; i<head.size();i++){
      cout<<head[i][1]<<"\t"<<"|"<<"\t";
    }
    cout<<endl;
    for(int i = 0; i<head.size();i++){
      for(int j = 0; j<head[i][1].length()+10;j++){
        cout<<"-";
      }
    }
    cout<<endl;
    for(int i = 0; i<body.size();i++){
      for(int j = 0; j<body[i].size();j++)
      {
        cout<<body[i][j]<<"\t"<<"|"<<"\t";
      }
      cout<<endl;
      for(int j = 0; j < body[i].size();j++)
      {
        for(int r= 0; r < body[i][j].length()+10;r++)
        {
          cout<<"-";
        }

      }
      cout<<endl;
    }

  }

  string get_nameDB()
  {
    return this->nameDB;
  }

  // create database ( add ot vector head )
  void create(string nameDB, vector <vector <string>> head)
  {
    this->nameDB = nameDB;
    this->head = head;
  }

  // Add to database ( add ot vector body )
  void add( vector <string> head, vector <string> body)
  {
    vector <string> row_body;
    bool he_is_here = false;
    for(int i = 0; i < this->head.size(); i++){
      for(int j = 0; j< head.size();j++){
        if(this->head[i][1] == head[j]){
          row_body.push_back(body[j]);
          he_is_here = true;
          break;
        }

      }

      if(he_is_here){
        he_is_here = false;
      }
      else{
        row_body.push_back("NULL");
      }
    }
    this->body.push_back(row_body);
  }
};
