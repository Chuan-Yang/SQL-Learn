/**
 * How to access the database using C
 * Author: chuan1
 */

#include <stdio.h>
#include <sqlite3.h>


void mysquare(sqlite3_context * ctx, int nargs, sqlite3_value ** values){
    double x = sqlite3_value_double(values[0]);
    double y = x+x;
    sqlite3_result_double(ctx, y);
}


int main(){
    sqlite3 *db; //the database
    sqlite3_stmt *stmt; //keep statement in the database

    int ret_value;
    ret_value = sqlite3_open("test.db", &db);       
    if (ret_value){     // Open database
        fprintf(stderr, "Open Errror %s", sqlite3_errmsg(db));
        sqlite3_close(db); // close the database
        return 0;         // clsoe the program
    }

    sqlite3_create_function(db, "square", 1, SQLITE_UTF8,NULL,mysquare,NULL,NULL);

    char *myquery = "update mytable set id = square(id)";

    ret_value = sqlite3_prepare(db, myquery,-1,&stmt,0); 
    //-1:
    //0: the pointer of all the unused data, give them null 0 or w/e
    
    if (ret_value!=SQLITE_OK){      //prepare statement
        fprintf(stderr, "Open Errror %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    ret_value = sqlite3_step(stmt);
    // if (ret_value!=SQLITE_OK)

    // while( (ret_value=sqlite3_step(stmt)) == SQLITE_ROW ){      //Execute statement
    //     int i;
    //     for (i=0; sqlite3_column_count(stmt);i++){
    //         printf ("%s|", sqlite3_column_text(stmt,i));
    //     printf ("%s|", sqlite3_column_text(stmt,i));    
    //     }
    //     //sqlite3_column_text(stmt,index);
    // }

    // int id = 1;
    // sqlite3_reset(stmt);
    // sqlite3_clear_bindings(stmt);
    // sqlite3_bind_int(stmt,1,id);



    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}