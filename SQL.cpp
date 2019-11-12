#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

#define ERROR_OF_NAME 655565
#define ERROR_UNDEFINED 324556
#define ERROR_IN_NAME_OF_COLUMN 332151
#define ERROR_IN_DATA 231221
#define ERROR_IN_COUNT_OF_DATA 219301
#define ERROR_IN_COMMAND 21223
#define ERROR_NAME_REPITED 229948
#define ERROR_UNKNOW_SYMBOLS 876332
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

class SQL
{
  private:
    vector <Database*> databases;
    bool find_string_in_vector(string find, vector<string> find_in)
    {
      for(int i = 0; i < find_in.size(); i++){

        if (find_in[i] == find){
          return true;
        }

      }

      return false;
    }

    bool find_char_in_string(string find_in, char find)
    {
      for(int i = 0; i < find_in.length(); i++){

        if (find_in[i] == find){
          return true;
        }

      }

      return false;
    }


    Database* find_database(string nameDB)
    {
      for(int i = 0; i < this->databases.size(); i++){
        if( this->databases[i]->get_nameDB() == nameDB){
          return this->databases[i];
        }
      }
      return NULL;
    }


  public:
    string strip(string str)
    {
      string str_without_gap = "";
      int i = 0;
      int e = str.length()-1;
      int e2 = 0;
      for(; i < str.length();i++){
        if(str[i] == ' '){
          continue;
        }
        else
        {
           break;
        }
      }
      for(; i < str.length();e2++){
        if(str[e - e2] == ' '){
          continue;
        }
        else
        {
           break;
        }
      }
      for(; i <= e-e2;i++){
        str_without_gap += str[i];
      }

      return str_without_gap;
    }

    int show_database(string nameDB)
    {
      Database *db = find_database(nameDB);
      if(db != 0){
        db->show();
      }
      else{
        return ERROR_OF_NAME;
      }
      return 0;
    }

    int check_params_for_create(vector <string> params)
    {

      if (params.size() % 2 != 0){
        return ERROR_UNDEFINED;
      }

      //check the name for individuality
        if(find_database(params[1]) != 0){
          return ERROR_OF_NAME;
        }
        vector<char> unknow_symbols={'?', '#', '@', '^', '&', '|',
                                      '\\', '/', '$', '!', '*', '-', '+', '=', '%'};
        for(int i = 0; i < unknow_symbols.size(); i++){
          if(find_char_in_string(params[1], unknow_symbols[i])){
            return ERROR_UNKNOW_SYMBOLS;
          }
        }


      //check name of colomns for individuality
      for(int i = 3; i < params.size(); i+=2){
        for(int j = i+2; j < params.size(); j+=2){
          if(params[i] == params[j]){
            return ERROR_NAME_REPITED;
          }
        }
      }

      //check validations of types
      vector<string> type = {"int", "string"};

      for(int i = 2; i < params.size(); i+=2){
        for(int j = 0; j < unknow_symbols.size(); j++){
          if(find_char_in_string(params[i+1], unknow_symbols[j])){
            return ERROR_UNKNOW_SYMBOLS;
          }
        }
        if(find_string_in_vector(params[i], type)){
          continue;
        }
        return i;
      }

      return 0;

    }

    int check_params_for_add(string nameDB,vector <string> head, vector <string>  body)
    {


      Database *db = find_database(nameDB);
      //check the name for individuality
      if(db == 0){
        return ERROR_OF_NAME;
      }

      if(head.size() != body.size()){
        return ERROR_IN_COUNT_OF_DATA;
      }

      vector<char> unknow_symbols={'?', '#', '@', '^', '&', '|',
                                    '\\', '/', '$', '!', '*', '-', '+', '=', '%'};


      for(int i = 0; i < unknow_symbols.size(); i++){
        for(int j = 0;j< head.size(); j++){
          if(find_char_in_string(body[j], unknow_symbols[i])){
            return ERROR_UNKNOW_SYMBOLS;
          }
        }
      }

      int checker = 0;
      string vector_of_numbers = "0123456789";
      for(int i = 0; i<head.size();i++)
      {

        for(int j = 0; j<db->head.size();j++)
        {

          if(db->head[j][1] == head[i])
          {

            if(db->head[j][0] == "int")
            {
              for(int r = 0; r < body[i].length();r++)
              {
                if(find_char_in_string(vector_of_numbers, body[i][r])){
                  continue;
                }
                else{
                  return ERROR_IN_DATA;
                }
              }
            }


            checker++;
            break;
          }

        }
        if(checker){
          checker = 0;
        }
        else{
          return ERROR_IN_NAME_OF_COLUMN;
        }

      }

      return 0;

    }


    void string_to_lower(string &str)
    {
      for(auto& c : str)
      {
         c = tolower(c);
      }
    }

    vector <string> string_to_param_of_database(string command)
    {
      vector <string> params;
      string param = "";
      for(int i = 0; i < command.length(); i++){
        if (command[i] == ' ' || command[i] == ',' ||
            command[i] == '(' || command[i] == ')' ||
            command[i] == ';' || command[i] == '&' ||
            command[i] == '|')
        {
          if(param != "")
          {
            params.push_back(param);
            param = "";
          }
          continue;
        }
        param += command[i];
      }
      return params;
    }

    // create object of database
    void create_database(string nameDB, vector <vector <string>> head)
    {
      Database *db = new Database();
      db->create(nameDB, head);
      this->databases.push_back(db);
    }

    void show_all_databases()
    {
      for(int i = 0; i < this->databases.size(); i++){
        cout<< "database: " << this->databases[i]->get_nameDB() <<endl;
      }
    }


    //add data to object of database
    void add_to_database(string nameDB, vector <string> head, vector <string> body)
    {
      Database *db = find_database(nameDB);
      db->add(head, body);

    }

    int import_database(string nameDB, string file_name)
    {
      Database *db = find_database(nameDB);
      if(db == 0){
        return ERROR_OF_NAME;
      }
      ofstream fout(file_name, ios_base::out);
      fout<<nameDB<<endl;

      for(int i = 0; i<db->head.size();i++){
        fout<<db->head[i][0]<<"&"<<db->head[i][1]<<"|";
      }
      fout<<endl;
      for(int i = 0; i<db->body.size();i++){
        for(int j = 0; j<db->body[i].size();j++)
        {
          fout<<db->body[i][j]<<"|";
        }
        fout<<endl;
      }

      fout.close();
      cout<<"Imported"<<endl;
      return 0;

    }

    int export_database(string file_name)
    {
      ifstream fin(file_name, ios_base::in);

      string line;
      int num = 1;
      Database *db = new Database();
      string  nameDB;
      vector<vector<string>> head;
      vector<string> head_for_add;
      while (std::getline(fin, line)) {
        if (num == 1){
          nameDB = line;
        }
        else if(num == 2){
          vector<string> colums = string_to_param_of_database(line);
          for(int i = 0; i < colums.size();i+=2){
            vector <string> column = {colums[i],colums[i+1]};
            head_for_add.push_back(colums[i+1]);
            head.push_back(column);
          }
          db->create(nameDB, head);
        }
        else{
          vector<string> body_for_add = string_to_param_of_database(line);
          if(body_for_add.size() != head_for_add.size()){
            cout<<"it doesn`t exported"<<endl;
            return 0;
          }
          db->add(head_for_add, body_for_add);
        }
      }
      this->databases.push_back(db);
      cout<<"Exported"<<endl;
      return 0;
    }

};



int main()
{


  string command;
  string parram1;
  string parram2;

  //interface of database
  SQL *sql = new SQL();

  // command
  while(true){

    cout<<">";
    cin>>parram1;
    getline(cin, parram2);
    command += parram1 + parram2;
    cout<<endl;
    command = sql->strip(command);
    if(command[command.length()-1] != ';')
    {
      command += ' ';
      continue;
    }


    //request to database
    else
    {
      if (command.length()==1){
        cout<<"Check command please"<<endl;
        command = "";
        continue;
      }
      vector <string> params = sql->string_to_param_of_database(command);
      command = "";
      sql->string_to_lower(params[0]);
      //check command
      if(params[0]== "create")
      {
        int error = sql->check_params_for_create(params);
        if (error == ERROR_UNDEFINED)
        {
          cout<<"Error undefined (Error: "<<error<<")"<<endl;
        }
        else if(error == ERROR_UNKNOW_SYMBOLS){
          cout<<"Error unknow symbols (Error: "<<error<<")"<<endl;
        }
        else if(error == ERROR_NAME_REPITED){
          cout<<"Error name repited (Error: "<<error<<")"<<endl;
        }

        else if(error == ERROR_OF_NAME)
        {
          cout<<"Error in name (Error: "<<error<<")"<<endl;
        }

        else if(error)
        {
          cout<<"Error in type (Error: "<<error<<")"<<endl;
        }
        else{
          vector <vector <string>> head;
          for(int i = 2; i < params.size(); i+=2){
            vector <string> type_and_data;
            type_and_data.push_back(params[i]);
            type_and_data.push_back(params[i+1]);
            head.push_back(type_and_data);
          }
          sql->create_database(params[1], head);
          cout<<"Database created"<<endl;
        }
      }

      else if(params[0]== "import")
      {
        int error = sql->import_database(params[1], params[2]);
        // if(error == ERROR_OF_NAME){
        //   cout<<"Error in name (Error: "<<error<<")"<<endl;
        // }
      }
      else if(params[0]== "export")
      {
        int error = sql->export_database(params[1]);
        // if(error == ERROR_OF_NAME){
        //   cout<<"Error in name (Error: "<<error<<")"<<endl;
        // }
      }
      else if(params[0]== "show")
      {

        int error = sql->show_database(params[1]);
        if(error == ERROR_OF_NAME){
          cout<<"Error in name (Error: "<<error<<")"<<endl;
        }
      }
      else if(params[0]== "show_databases")
      {
        sql->show_all_databases();
      }

      else if(params[0]== "add")
      {
        vector <string> head, body;
        bool is_values_or_not = true;
        for(int i = 2; i < params.size(); i++){
          string save = params[i];
          sql->string_to_lower(params[i]);
          if (params[i] == "values"){
            is_values_or_not=false;
            continue;
          }
          params[i] = save;
          if(is_values_or_not)
          {
            head.push_back(params[i]);
          }
          else
          {
            body.push_back(params[i]);
          }
        }
        if(is_values_or_not){
          cout<<"Error in command (Error: "<<ERROR_IN_COMMAND<<")"<<endl;
        }
        int error = sql->check_params_for_add(params[1], head, body);

        if(error == ERROR_OF_NAME)
        {
          cout<<"Error in name (Error: "<<error<<")"<<endl;
        }

        else if(error == ERROR_IN_NAME_OF_COLUMN)
        {
          cout<<"Error in name of column (Error: "<<error<<")"<<endl;
        }
        else if(error == ERROR_IN_DATA){
          cout<<"Error in data (Error: "<<error<<")"<<endl;
        }
        else if(error == ERROR_UNKNOW_SYMBOLS){
          cout<<"Error unknow symbols (Error: "<<error<<")"<<endl;
        }
        else if(error == ERROR_IN_COUNT_OF_DATA)
        {
          cout<<"Error in count of data (Error: "<<error<<")"<<endl;
        }
        else
        {
          sql->add_to_database(params[1], head, body);
          cout<<"Added to database"<<endl;
        }
      }


    }

  }



  return 0;
}
