#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_LEN 200
#define MAX_EVENTS 1000

typedef struct{
    char day[MAX_LINE_LEN];
    char month[MAX_LINE_LEN];
    char year[MAX_LINE_LEN];
    char dweek[MAX_LINE_LEN];
    char start[MAX_LINE_LEN];
    char end[MAX_LINE_LEN];
    char description[MAX_LINE_LEN];
    char timezone[MAX_LINE_LEN];
    char location[MAX_LINE_LEN];
} Event;


void parsing_file (char* filename, Event* eventarray, int* size_pointer);
void parse_event(Event* eventarray, char* cur_line, int* size_pointer, FILE* xml_file);
int comparison_for_qsort(const void* v1, const void* v2);
void within_range(Event* eventarray, Event* new_e_array, int* array_size, int* new_a_size, int from_d, int from_m, int from_y, int to_d, int to_m, int to_y);
void print_events(Event* new_e_array, int* new_a_size);
void change_month(char* month, char* month_str);

//within_range function reads each event from the eventarray and checks if the events happen within
//the time range given by the user input then adds the events that happen within the
//time range into the new_e_array.

void within_range(Event* eventarray, Event* new_e_array, int* array_size, int* new_a_size, int from_d, int from_m, int from_y, int to_d, int to_m, int to_y){

    for(int i = 0; i < *array_size; i++){

        char* ptr;

        long year;
        long month;
        long day;

        year = strtol(eventarray[i].year, &ptr, 10);
        month = strtol(eventarray[i].month, &ptr, 10);
        day = strtol(eventarray[i].day, &ptr, 10);


        if(year >= from_y && year <= to_y){
            if(month == from_m ){
                if(day >= from_d){
                    new_e_array[*new_a_size] = eventarray[i];
                    *new_a_size += 1;
                    continue;
                }
            }else if(month > from_m && month < to_m){
                new_e_array[*new_a_size] = eventarray[i];
                *new_a_size += 1;
                continue;
            }else if(month == to_m){
                if(day <= to_d){
                    new_e_array[*new_a_size] = eventarray[i];
                    *new_a_size += 1;
                    continue;
                }
            }
        }
    }

}

//takes the numerical values of events months and converts them into string values

void change_month(char* month, char* month_str){
    if(strncmp(month, "01", strlen("01")) == 0){
        strcpy(month_str, "January");
    }else if(strncmp(month, "02", strlen("02")) == 0){
        strcpy(month_str, "February");
    }else if(strncmp(month, "03", strlen("03")) == 0){
        strcpy(month_str, "March");
    }else if(strncmp(month, "04", strlen("04")) == 0){
        strcpy(month_str, "April");
    }else if(strncmp(month, "05", strlen("05")) == 0){
        strcpy(month_str, "May");
    }else if(strncmp(month, "06", strlen("06")) == 0){
        strcpy(month_str, "June");
    }else if(strncmp(month, "07", strlen("07")) == 0){
        strcpy(month_str, "July");
    }else if(strncmp(month, "08", strlen("08")) == 0){
        strcpy(month_str, "August");
    }else if(strncmp(month, "09", strlen("09")) == 0){
        strcpy(month_str, "September");
    }else if(strncmp(month, "10", strlen("10")) == 0){
        strcpy(month_str, "October" );
    }else if(strncmp(month, "11", strlen("11")) == 0){
        strcpy(month_str, "November");
    }else if(strncmp(month, "12", strlen("12")) == 0){
        strcpy(month_str, "December");
    }
}


void print_events(Event* new_e_array, int* new_a_size){
    char month[MAX_LINE_LEN];
    char year[MAX_LINE_LEN];
    char day[MAX_LINE_LEN];
    char dweek[MAX_LINE_LEN];
    char month_num[MAX_LINE_LEN];

    for(int i = 0; i < *new_a_size; i++){

        if(strncmp(month_num, new_e_array[i].month, strlen(new_e_array[i].month)) != 0 || strncmp(day, new_e_array[i].day, strlen(new_e_array[i].day)) != 0
        || strncmp(year, new_e_array[i].year, strlen(new_e_array[i].year)) != 0 || strncmp(dweek, new_e_array[i].dweek, strlen(new_e_array[i].dweek)) != 0){
            char month_str[MAX_LINE_LEN];
            change_month(new_e_array[i].month, month_str);
            strcpy(month, month_str);
            strcpy(month_num, new_e_array[i].month);
            strcpy(day, new_e_array[i].day);
            strcpy(year, new_e_array[i].year);
            strcpy(dweek, new_e_array[i].dweek);
            char str[1000];

            sprintf(str, "%s %s, %s (%s)", month, day, year, dweek);

            if(i > 0){
                printf("\n%s\n", str);
            }else{
                printf("%s\n", str);
            }

            int dash_length = strlen(str);
            for(int i = 0; i <= dash_length; i++){
                if(i == dash_length){
                    printf("\n");
                }
                else{
                    printf("-");
                }
            }
            char starthour[MAX_LINE_LEN];
            char startmin[MAX_LINE_LEN];
            char endhour[MAX_LINE_LEN];
            char endmin[MAX_LINE_LEN];
            sscanf(new_e_array[i].start, "%[^ :] %s", starthour, startmin);
            sscanf(new_e_array[i].end, "%[^ :] %s", endhour, endmin);
            char* ptr;

            long start_int = strtol(starthour, &ptr, 10);
            long end_int = strtol(endhour, &ptr, 10);
            if(start_int == 12 && end_int <= 12){
                printf("%s%s AM", starthour, startmin);
            }else if(start_int == 12 && end_int > 12){
                printf("%s%s PM", starthour, startmin);
            }else if(start_int < 12){
                printf("%s%s AM", starthour, startmin);
            }else if(start_int > 12){
                start_int = start_int % 12;
                printf("%02ld%s PM", start_int, startmin);
            }


            if(end_int == 12 && start_int < 12){
                printf(" to %s%s PM", endhour, endmin);
            }else if(end_int == 12 && start_int > 12){
                printf(" to %s%s AM", endhour, endmin);
            }else if(end_int < 12){
                printf(" to %s%s AM", endhour, endmin);
            }else if(end_int > 12){
                end_int = end_int % 12;
                printf(" to %02ld%s PM", end_int, endmin);
            }

            if(i == *new_a_size - 1){
            printf(": %s {{%s}} | %s", new_e_array[i].description, new_e_array[i].location, new_e_array[i].timezone);
            }else{
            printf(": %s {{%s}} | %s\n", new_e_array[i].description, new_e_array[i].location, new_e_array[i].timezone);
            }



        }else if(strncmp(month_num, new_e_array[i].month, strlen(new_e_array[i].month)) == 0 && strncmp(day, new_e_array[i].day, strlen(new_e_array[i].day)) == 0
            && strncmp(year, new_e_array[i].year, strlen(new_e_array[i].year)) == 0 && strncmp(dweek, new_e_array[i].dweek, strlen(new_e_array[i].dweek)) == 0){

            char starthour[MAX_LINE_LEN];
            char startmin[MAX_LINE_LEN];
            char endhour[MAX_LINE_LEN];
            char endmin[MAX_LINE_LEN];
            sscanf(new_e_array[i].start, "%[^ :] %s", starthour, startmin);
            sscanf(new_e_array[i].end, "%[^ :] %s", endhour, endmin);
            char* ptr;

            long start_int = strtol(starthour, &ptr, 10);
            long end_int = strtol(endhour, &ptr, 10);
            if(start_int == 12 && end_int <= 12){
                printf("%s%s AM", starthour, startmin);
            }else if(start_int == 12 && end_int > 12){
                printf("%s%s PM", starthour, startmin);
            }else if(start_int < 12){
                printf("%s%s AM", starthour, startmin);
            }else if(start_int > 12){
                start_int = start_int % 12;
                printf("%02ld%s PM", start_int, startmin);
            }


            if(end_int == 12 && start_int < 12){
                printf(" to %s%s PM", endhour, endmin);
            }else if(end_int == 12 && start_int > 12){
                printf(" to %s%s AM", endhour, endmin);
            }else if(end_int < 12){
                printf(" to %s%s AM", endhour, endmin);
            }else if(end_int > 12){
                end_int = end_int % 12;
                printf(" to %02ld%s PM", end_int, endmin);
            }

            if(i == *new_a_size - 1){
            printf(": %s {{%s}} | %s", new_e_array[i].description, new_e_array[i].location, new_e_array[i].timezone);
            }else{
            printf(": %s {{%s}} | %s\n", new_e_array[i].description, new_e_array[i].location, new_e_array[i].timezone);
            }

        }
     
    }




}

//comparison function needed to use qsort in the main function
//to sort the events in a chronological order


int comparison_for_qsort(const void* v1, const void* v2) {
    Event* e1 = (Event *)v1;
    Event* e2 = (Event *)v2;

    if(strncmp(e1->year, e2->year, strlen(e2->year)) == 0 ){
       if(strncmp(e1->month, e2->month, strlen(e2->month)) == 0){
           if(strncmp(e1->day, e2->day, strlen(e2->day)) == 0){
               if(strncmp(e1->start, e2->start, strlen(e2->start)) == 0){
                   return 0;
               }else if(strncmp(e1->start, e2->start, strlen(e2->start)) < 0){
                   return -1;
               }else{
                   return 1;
               }
           }else if(strncmp(e1->day, e2->day, strlen(e2->day)) < 0){
               return -1;
           }else{
               return 1;
           }
       }else if(strncmp(e1->month, e2->month, strlen(e2->month)) < 0){
           return -1;
       }else{
           return 1;
       }
    } else if (strncmp(e1->year, e2->year, strlen(e2->year)) < 0){
        return -1;
    }
    else{
        return 1;
    }
}
    //parse_event parses each event read through the file into smaller categories that store
    //informations about the event and stores them into an event struct whilst adding each
    //event into the array.
void parse_event(Event* eventarray, char* cur_line, int* size_pointer, FILE* xml_file){

    char end_of_event[MAX_LINE_LEN] = "</event>";
    char description[MAX_LINE_LEN];
    char timezone[MAX_LINE_LEN];
    char location[MAX_LINE_LEN];
    char day[MAX_LINE_LEN];
    char month[MAX_LINE_LEN];
    char year[MAX_LINE_LEN];
    char dweek[MAX_LINE_LEN];
    char start[MAX_LINE_LEN];
    char end[MAX_LINE_LEN];

    fgets(cur_line, MAX_LINE_LEN, xml_file);
    sscanf(cur_line, " %[^\n]", cur_line);
    while(strncmp(cur_line, end_of_event, strlen(end_of_event)) != 0){
        char category[MAX_LINE_LEN];
        char value[MAX_LINE_LEN];
        char end_tag[MAX_LINE_LEN];

        sscanf(cur_line, "<%[^>]>%[^<]", category, value);

        if (strncmp(category, "description", strlen("description")) == 0) {
            strcpy(description, value);
        }
        else if (strncmp(category, "timezone", strlen("timezone")) == 0) {
            strcpy(timezone, value);
        }
        else if (strncmp(category, "location", strlen("location")) == 0) {
            strcpy(location, value);
        }
        else if (strncmp(category, "day", strlen("day")) == 0) {
            strcpy(day, value);
        }
        else if (strncmp(category, "month", strlen("month")) == 0) {
            strcpy(month, value);
        }
        else if (strncmp(category, "year", strlen("year")) == 0) {
            strcpy(year, value);
        }
        else if (strncmp(category, "dweek", strlen("dweek")) == 0) {
            strcpy(dweek, value);
        }
        else if (strncmp(category, "start", strlen("start")) == 0) {
            strcpy(start, value);
        }
        else if (strncmp(category, "end", strlen("end")) == 0) {
            strcpy(end, value);
        }

        fgets(cur_line, MAX_LINE_LEN, xml_file);
        sscanf(cur_line, " %[^\n]", cur_line);
    }
    Event e;
    strcpy(e.description, description);
    strcpy(e.timezone, timezone);
    strcpy(e.location, location);
    strcpy(e.day, day);
    strcpy(e.month, month);
    strcpy(e.year, year);
    strcpy(e.dweek, dweek);
    strcpy(e.start, start);
    strcpy(e.end, end);

    eventarray[*size_pointer] = e;
    *size_pointer+=1;
}
    //parsing_file takes the file as an argument along with other needed arguments to open and
    //read lines from the file then calling parse_event function to parse the events
    //into categories needed.

void parsing_file (char* filename, Event* eventarray, int* size_pointer){
    FILE* xml_file = fopen(filename, "r");

    if(xml_file == NULL){
        printf("Error: The file is null\n");
        exit(1);
    }

    char begin_event[MAX_LINE_LEN] = "<event>";
    char end_of_file[MAX_LINE_LEN] = "</calendar>";
    char cur_line[MAX_LINE_LEN];

    fgets(cur_line, MAX_LINE_LEN, xml_file);

    while(strncmp(cur_line, end_of_file, strlen(end_of_file)) != 0) {
        sscanf(cur_line, " %[^\n]", cur_line);
        if (strncmp(cur_line, begin_event, strlen(begin_event)) == 0) {
            //Read event
            parse_event(eventarray, cur_line, size_pointer, xml_file);
        }

        fgets(cur_line, MAX_LINE_LEN, xml_file);
    }
    fclose(xml_file);
}
/*
    Function: main
    Description: represents the entry point of the program.
    Inputs:
        - argc: indicates the number of arguments to be passed to the program.
        - argv: an array of strings containing the arguments passed to the program.
    Output: an integer describing the result of the execution of the program:
        - 0: Successful execution.
        - 1: Erroneous execution.
*/
int main(int argc, char *argv[])
{
    /* Starting calling your own code from this point. */
    // Ideally, please try to decompose your solution into multiple functions that are called from a concise main() function.
    int from_y = 0;
    int from_m = 0;
    int from_d = 0;

    int to_y = 0;
    int to_m = 0;
    int to_d = 0;

    char filename[MAX_LINE_LEN];

    sscanf(argv[1],"--start=%d/%d/%d",&from_y, &from_m, &from_d);
    sscanf(argv[2], "--end=%d/%d/%d", &to_y, &to_m, &to_d);
    sscanf(argv[3], "--file=%s", filename);


    Event eventarray[MAX_EVENTS];
    int array_size = 0;

    parsing_file(filename, eventarray, &array_size);

    qsort(eventarray, array_size, sizeof(Event), comparison_for_qsort);

    Event new_e_array[MAX_EVENTS];
    int new_a_size = 0;

    within_range(eventarray, new_e_array, &array_size, &new_a_size, from_d, from_m, from_y, to_d, to_m, to_y);

    print_events(new_e_array, &new_a_size);

    exit(0);
}