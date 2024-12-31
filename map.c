#include <ncurses.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
struct Door{
    int x_door;  
    int y_door;
};
struct Room {  
    int x;  
    int y;  
    int size;
    int number_of_doors;
    struct Door doors[3];
};  

void generate_rooms();  
int can_have_room(struct Room rooms[8], int current_room);  
void print_map(int number_of_rooms, struct Room rooms[8]);  

int main() {
    initscr();  
    cbreak();  
    noecho();  
    srand(time(0));  
    generate_rooms();  
    getch(); 
    endwin();
    return 0;  
}  

void generate_rooms() {  
    int number_of_rooms = ((unsigned int)rand() % 3) + 6; // 6-8  
    struct Room rooms[8];  
    int current_room = 0;  

    while (current_room < number_of_rooms) {  
        rooms[current_room].x = (unsigned int)rand() % (100 - 0 + 1) + 0;  
        rooms[current_room].y = (unsigned int)rand() % (30 - 10 + 1) + 10;
        rooms[current_room].size = ((unsigned int)rand() % 3) + 4;
        if (can_have_room(rooms, current_room)) {  
            current_room++;  
        } 
    }
    current_room = 0;
    while(current_room < number_of_rooms){
        rooms[current_room].number_of_doors = (unsigned int)rand() % 2 + 1;
        if(rooms[current_room].number_of_doors == 1){
            int witch_side = rand() % 4 + 1;
            if(witch_side == 1){
                rooms[current_room].doors->x_door = rand() % ()
            }
            if(witch_side == 2){}
            if(witch_side == 3){}
            if(witch_side == 4){}
        }
        if(rooms[current_room].number_of_doors == 2){}
    }
    print_map(number_of_rooms, rooms);  
}  

int can_have_room(struct Room rooms[8], int current_room) {  
    for (int i = 0; i < current_room; i++) {  
        if ((rooms[current_room].x <= rooms[i].x + rooms[i].size) &&   
            (rooms[current_room].x + rooms[current_room].size >= rooms[i].x) &&   
            (rooms[current_room].y >= rooms[i].y - rooms[i].size) &&   
            (rooms[current_room].y - rooms[current_room].size <= rooms[i].y)) {  
            return 0;  
        }  
    }  
    return 1;  
}  

void print_map(int number_of_rooms, struct Room rooms[8]) {  
    for (int i = 0; i < number_of_rooms; i++) {  
        int x_1 = rooms[i].x;  
        int x_2 = rooms[i].x + rooms[i].size;  
        int y_1 = rooms[i].y;  
        int y_3 = rooms[i].y - rooms[i].size;  

        for (int j = 0; j <= rooms[i].size; j++) {  
            move(y_1, x_1 + j);  
            printw("_");  
            move(y_3, x_1 + j);  
            printw("_");  
        }  

        for (int j = 0; j < rooms[i].size; j++) {  
            move(y_1 - j, x_1);  
            printw("|");
            move(y_1 - j, x_2);  
            printw("|");  
        }  
    }  
    refresh();  
}