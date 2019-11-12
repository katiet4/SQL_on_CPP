#include "sqlclass.h"
int handler_of_error(int error, string command = "");

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

        if (handler_of_error(error))
        {
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
        if(handler_of_error(error))
        {
          cout<<"Imported"<<endl;
        }


      }
      else if(params[0]== "export")
      {
        int error = sql->export_database(params[1]);
        if(handler_of_error(error)){
          cout<<"Exported"<<endl;
        }

      }
      else if(params[0]== "show")
      {

        int error = sql->show_database(params[1]);
        handler_of_error(error);
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
          continue;
        }
        int error = sql->check_params_for_add(params[1], head, body);

        if(handler_of_error(error))
        {
          sql->add_to_database(params[1], head, body);
          cout<<"Added to database"<<endl;
        }
      }
      else{
        handler_of_error(ERROR_UNKNOW_COMMAND, params[0]);
      }


    }

  }



  return 0;
}

int handler_of_error(int error, string command = ""){

  if (error == ERROR_UNDEFINED)
  {
    cout<<"Error undefined (Error: "<<error<<")"<<endl;
    return 0;
  }

  else if(error == ERROR_UNKNOW_SYMBOLS){
    cout<<"Error unknow symbols (Error: "<<error<<")"<<endl;
    return 0;
  }

  else if(error == ERROR_UNKNOW_COMMAND){
    cout<<"Error unknow command "<<"'"<<command<<"'"<<" (Error: "<<error<<")"<<endl;
    return 0;
  }
  else if(error == ERROR_UNKNOW_TYPE){
    cout<<"Error unknow type (Error: "<<error<<")"<<endl;
    return 0;
  }

  else if(error == ERROR_NAME_REPITED){
    cout<<"Error name repited (Error: "<<error<<")"<<endl;
    return 0;
  }

  else if(error == ERROR_IN_NAME_OF_COLUMN)
  {
    cout<<"Error in name of column (Error: "<<error<<")"<<endl;
    return 0;
  }

  else if(error == ERROR_IN_DATA){
    cout<<"Error in data (Error: "<<error<<")"<<endl;
    return 0;
  }

  else if(error == ERROR_OF_NAME)
  {
    cout<<"Error in name (Error: "<<error<<")"<<endl;
    return 0;
  }
  else if(error == ERROR_IN_COUNT_OF_DATA)
  {
    cout<<"Error in count of data (Error: "<<error<<")"<<endl;
    return 0;
  }
  else if(error == ERROR_IN_EXPORT)
  {
    cout<<"Error in export (Error: "<<error<<")"<<endl;
    return 0;
  }
  else if(error)
  {
    cout<<"Error in type (Error: "<<error<<")"<<endl;
    return 0;
  }
  return 1;
}
