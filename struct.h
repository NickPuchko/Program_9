#ifndef UP9_STRUCT_H
#define UP9_STRUCT_H
typedef struct

{
    char airline[20];
    char airport[20];
    char aircraft[20];
    int ID;
    int passengers;
    int estimated_hours;
    int estimated_minutes;
    int schedule_hours;
    int schedule_minutes;
} flights;
#endif //UP9_STRUCT_H
