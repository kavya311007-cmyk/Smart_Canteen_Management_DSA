#include <iostream>
#include <mysqlx/xdevapi.h>
using namespace std;

int main(){
    string email;
    string password;
    string role;

    cout<<"Enter Email: ";
    cin>>email;
    cout<<"Enter Password: ";
    cin>>password;

    mysqlx::Session session(
    "localhost",
    33060,
    "root",
    "Mahant@100"
    );
    cout<<"MySQL connected successfully..";

    mysqlx::Schema db = session.getSchema("smart_canteen"); 

    cout<<"Database selectde successfully.."<<endl;

    mysqlx::Table users = db.getTable("users");
    mysqlx::RowResult result = users
    .select("*")
    .where("email= :email AND password= :password")
    .bind("email",email)
    .bind("password",password)
    .execute();

    if(result.count()>0){
        cout<<"Login Succeeded"<<endl;
    }else{
        cout<<"Invalid"<<endl;
    }


    for(auto row : result){
        role = row[4].get<string>();
        cout<<role<<endl;

        if(role=="Admin"){
            cout<<"Admin logged in";
        }else if(role=="Staff"){
            cout<<"Staff logged in";
        }else{
            cout<<"Student logged in";
        }
    }

    return 0;
}