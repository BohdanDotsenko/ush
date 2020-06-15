#include "ush.h"

int mx_cycle_for_quotes(char *line, char delim, int *i) {
    (*i) += 1;           
    for (; line[(*i)] && line[(*i)] != delim; (*i)++); 
    if (line[(*i)] == delim && line[(*i) - 1] != '\\') 
        return (*i);
    else 
        return -1;
}

int mx_check_quotes(char *line, char delim) {
    int i = 0;


    for (; line[i]; i++) {   
        if (line[i] == '\\' && line[i+1] == '\'') {
            i += 1;
            continue;
        }
        if (line[i] == '\'') 
            if (mx_cycle_for_quotes(line, '\'', &i) == -1)
                return -1;
        if (line[i] == '\\' && line[i+1] == '"') {
            i += 1;
            continue;
        }
        if (line[i] == '"')
           if (mx_cycle_for_quotes(line, '"', &i) == -1)
               return -1;
        if (line[i] == '\\' && line[i + 1] == delim)
            continue; 
        if (line[i] == delim && line[i + 1] == delim && line[i] != ' ')
           return -1;
        if (line[i] == delim) {
            return i;
        }
    }
    return 100;
}


    //if (line[i] != ';' || strlen(line) > 0)
    //    return i; //we have ;
    //else
    //    return -1; // we havent ;  

            /*    
        if (line[i] == '"' && line[i-1] != '\\')
            if (mx_cycle_for_quotes(line, '"', &i) == -1)
                return -1;
        if (line[i] == ';' && line[i - 1] != '\\')
            return i;
        if (line[i] == ';' && line[i - 1] == ';')
            return -1;
    */


                /*    
        if (line[i] == '"' && line[i-1] != '\\')
            if (mx_cycle_for_quotes(line, '"', &i) == -1)
                return -1;
        if (line[i] == ';' && line[i - 1] != '\\')
            return i;
        if (line[i] == ';' && line[i - 1] == ';')
            return -1;
    */
//}

/*for (; line[i]; i++) {
        if (line[i] == '\'' && line[i-1] != '\\')
            if (mx_cycle_for_quotes(line, '\'', &i) == -1)
                return -1;
        if (line[i] == '"' && line[i-1] != '\\')
            if (mx_cycle_for_quotes(line, '"', &i) == -1)
                return -1;
        if (line[i] == ';' && line[i - 1] != '\\')
            return i;
        if (line[i] == ';' && line[i - 1] == ';')
            return -1;
    
    }
    if (line[i] != ';' || strlen(line) > 0)
        return 1; //we have ;
    else
        return -1; // we havent ;
}
*/

