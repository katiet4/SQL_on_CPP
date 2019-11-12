 #include "database.h"
 #include <fstream>

#define ERROR_OF_NAME 655565
#define ERROR_UNDEFINED 324556
#define ERROR_IN_NAME_OF_COLUMN 332151
#define ERROR_IN_DATA 231221
#define ERROR_IN_COUNT_OF_DATA 219301
#define ERROR_IN_COMMAND 21223
#define ERROR_NAME_REPITED 229948
#define ERROR_UNKNOW_SYMBOLS 876332
#define ERROR_IN_EXPORT 87632221
#define ERROR_UNKNOW_COMMAND 2993998


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

            return ERROR_IN_EXPORT;
          }
          db->add(head_for_add, body_for_add);
        }
      }
      this->databases.push_back(db);

      return 0;
    }

};
