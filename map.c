#include <ncurses.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
int size = 0;

struct Corridor{
    int x_corridor;
    int y_corrifer;
};

struct Pillar{
    int x_pillar;
    int y_pillar;
    int number_room;
};

struct Door{
    int x_door;  
    int y_door;
    int room_number;
};

struct Room {  
    int x;  
    int y;
    int size;
    struct Door doors[2];
    int x_window;
    int y_window;
};  

struct Map{
    int x_stair;
    int y_stair;
    int number_room_stair;
    int number_of_rooms;
    struct Room rooms[8];
    struct Pillar pillors[3];
    int corridor_count;
    struct Corridor corridors[300];
};

struct Game{
    struct Map maps[4];
}game;

void generate_map(struct Map *map);
int can_have_room(struct Room rooms[8], int current_room);  
void print_map(int number_of_rooms, struct Room rooms[8], struct Map *map);  
int is_path_clear(struct Map *map, int x, int y);
int draw_corridor(struct Map *map, int start_x, int start_y, int end_x, int end_y);
void connect_doors(struct Map *map);

int main() {
    initscr();  
    cbreak();  
    noecho();  
    srand(time(0));
    generate_map(&game.maps[0]);
    print_map(game.maps[0].number_of_rooms, game.maps[0].rooms, &game.maps[0]);
    getch(); 
    endwin();
    return 0;  
}  

void generate_map(struct Map *map) {
    //Rooms
    map->number_of_rooms = ((unsigned int)rand() % 3) + 6; // 6-8  
    int current_room = 0;  

    while (current_room < map->number_of_rooms) {  
        if(current_room + 1 == 1){
            map->rooms[current_room].x = (unsigned int)rand() % (11 - (0 + 2) + 1) + (0 + 2);  
            map->rooms[current_room].y = (unsigned int)rand() % (10 - 2 + 1) + 2;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            if (can_have_room(map->rooms, current_room)) {  
                current_room++;

            }
        }
        else if(current_room + 1 == 2){
            map->rooms[current_room].x = (unsigned int)rand() % (25 - (16) + 1) + (16);  
            map->rooms[current_room].y = (unsigned int)rand() % (10 - 2 + 1) + 2;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            if (can_have_room(map->rooms, current_room)) {
                current_room++;  
            } 
        }
        else if(current_room + 1 == 3){
            map->rooms[current_room].x = (unsigned int)rand() % (11 - (0 + 2) + 1) + (0 + 2);
            map->rooms[current_room].y = (unsigned int)rand() % (23 - 14 + 1) + 14;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            if (can_have_room(map->rooms, current_room)) {  
                current_room++;  
            } 
        }
        else if(current_room + 1 == 4){
            map->rooms[current_room].x = (unsigned int)rand() % (25 - (16) + 1) + (16);  
            map->rooms[current_room].y = (unsigned int)rand() % (23 - 14 + 1) + 14;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            if (can_have_room(map->rooms, current_room)) {  
                current_room++;  
            } 
        }
        else if(current_room + 1 == 5){
            map->rooms[current_room].x = (unsigned int)rand() % (42 - (30) + 1) + (30);  
            map->rooms[current_room].y = (unsigned int)rand() % (10 - 2 + 1) + 2;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            if (can_have_room(map->rooms, current_room)) {  
                current_room++;

            }
        }
        else if(current_room + 1 == 6){
            map->rooms[current_room].x = (unsigned int)rand() % (60 - (47) + 1) + (47);  
            map->rooms[current_room].y = (unsigned int)rand() % (10 - 2 + 1) + 2;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            if (can_have_room(map->rooms, current_room)) {
                current_room++;  
            } 
        }
        else if(current_room + 1 == 7){
            map->rooms[current_room].x = (unsigned int)rand() % (42 - (30) + 1) + (30);  
            map->rooms[current_room].y = (unsigned int)rand() % (23 - 14 + 1) + 14;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            if (can_have_room(map->rooms, current_room)) {  
                current_room++;  
            } 
        }
        else if(current_room + 1 == 8){
            map->rooms[current_room].x = (unsigned int)rand() % (60 - (47) + 1) + (47);  
            map->rooms[current_room].y = (unsigned int)rand() % (23 - 14 + 1) + 14;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            if (can_have_room(map->rooms, current_room)) {  
                current_room++;  
            } 
        }
    }
    //Doors
    current_room = 0;
    while(current_room < map->number_of_rooms){
        if(current_room + 1 == 1){
            //2
            map->rooms[current_room].doors[0].x_door = map->rooms[current_room].x + map->rooms[current_room].size;
            map->rooms[current_room].doors[0].y_door = rand() % ((map->rooms[current_room].y + map->rooms[current_room].size - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[0].room_number = current_room;
            //3
            map->rooms[current_room].doors[1].x_door = rand() % ((map->rooms[current_room].x + map->rooms[current_room].size - 1) - (map->rooms[current_room].x + 1) + 1) + map->rooms[current_room].x + 1;
            map->rooms[current_room].doors[1].y_door = map->rooms[current_room].y + map->rooms[current_room].size;
            map->rooms[current_room].doors[1].room_number = current_room;
        }
        if(current_room + 1 == 2){
            //2
            map->rooms[current_room].doors[0].x_door = map->rooms[current_room].x + map->rooms[current_room].size;
            map->rooms[current_room].doors[0].y_door = rand() % ((map->rooms[current_room].y + map->rooms[current_room].size - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[0].room_number = current_room;
            //4
            map->rooms[current_room].doors[1].x_door = map->rooms[current_room].x;
            map->rooms[current_room].doors[1].y_door = rand() % (((map->rooms[current_room].y + map->rooms[current_room].size) - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[1].room_number = current_room;
        }
        if(current_room + 1 == 3){
            //1
            map->rooms[current_room].doors[0].x_door = rand() % ((map->rooms[current_room].x + map->rooms[current_room].size - 1) - (map->rooms[current_room].x + 1) + 1) + (map->rooms[current_room].x + 1);
            map->rooms[current_room].doors[0].y_door = map->rooms[current_room].y;
            map->rooms[current_room].doors[0].room_number = current_room;
            //2
            map->rooms[current_room].doors[1].x_door = map->rooms[current_room].x + map->rooms[current_room].size;
            map->rooms[current_room].doors[1].y_door = rand() % ((map->rooms[current_room].y + map->rooms[current_room].size - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[1].room_number = current_room;
        }
        if(current_room + 1 == 4){
            //2
            map->rooms[current_room].doors[0].x_door = map->rooms[current_room].x + map->rooms[current_room].size;
            map->rooms[current_room].doors[0].y_door = rand() % ((map->rooms[current_room].y + map->rooms[current_room].size - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[0].room_number = current_room;
            //4
            map->rooms[current_room].doors[1].x_door = map->rooms[current_room].x;
            map->rooms[current_room].doors[1].y_door = rand() % (((map->rooms[current_room].y + map->rooms[current_room].size) - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[1].room_number = current_room;
        }
        if(current_room + 1 == 5){
            //2
            map->rooms[current_room].doors[0].x_door = map->rooms[current_room].x + map->rooms[current_room].size;
            map->rooms[current_room].doors[0].y_door = rand() % ((map->rooms[current_room].y + map->rooms[current_room].size - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[0].room_number = current_room;
            //4
            map->rooms[current_room].doors[1].x_door = map->rooms[current_room].x;
            map->rooms[current_room].doors[1].y_door = rand() % (((map->rooms[current_room].y + map->rooms[current_room].size) - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[1].room_number = current_room;
        }
        if(current_room + 1 == 6){
            //4
            map->rooms[current_room].doors[0].x_door = map->rooms[current_room].x;
            map->rooms[current_room].doors[0].y_door = rand() % (((map->rooms[current_room].y + map->rooms[current_room].size) - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[0].room_number = current_room;
            //3
            map->rooms[current_room].doors[1].x_door = rand() % ((map->rooms[current_room].x + map->rooms[current_room].size - 1) - (map->rooms[current_room].x + 1) + 1) + map->rooms[current_room].x + 1;
            map->rooms[current_room].doors[1].y_door = map->rooms[current_room].y + map->rooms[current_room].size;
            map->rooms[current_room].doors[1].room_number = current_room;
        }
        if(current_room + 1 == 7){
            //2
            map->rooms[current_room].doors[0].x_door = map->rooms[current_room].x + map->rooms[current_room].size;
            map->rooms[current_room].doors[0].y_door = rand() % ((map->rooms[current_room].y + map->rooms[current_room].size - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[0].room_number = current_room;
            //4
            map->rooms[current_room].doors[1].x_door = map->rooms[current_room].x;
            map->rooms[current_room].doors[1].y_door = rand() % (((map->rooms[current_room].y + map->rooms[current_room].size) - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[1].room_number = current_room;
        }
        if(current_room + 1 == 8){
            //1
            map->rooms[current_room].doors[0].x_door = rand() % ((map->rooms[current_room].x + map->rooms[current_room].size - 1) - (map->rooms[current_room].x + 1) + 1) + (map->rooms[current_room].x + 1);
            map->rooms[current_room].doors[0].y_door = map->rooms[current_room].y;
            map->rooms[current_room].doors[0].room_number = current_room;
            //4
            map->rooms[current_room].doors[1].x_door = map->rooms[current_room].x;
            map->rooms[current_room].doors[1].y_door = rand() % (((map->rooms[current_room].y + map->rooms[current_room].size) - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[1].room_number = current_room;
        }
        current_room ++;
    }
    //Stair
    map->number_room_stair = rand() % map->number_of_rooms;
    map->x_stair = 0;
    map->y_stair = 0;
    while(map->x_stair == 0 || map->y_stair == 0){
        map->x_stair = rand() % ((map->rooms[map->number_room_stair].x + map->rooms[map->number_room_stair].size - 2) - (map->rooms[map->number_room_stair].x + 2) + 1) + ((map->rooms[map->number_room_stair].x + 2));
        map->y_stair = rand() % ((map->rooms[map->number_room_stair].y + map->rooms[map->number_room_stair].size - 2) - (map->rooms[map->number_room_stair].y + 2) + 1) + ((map->rooms[map->number_room_stair].y + 2));
    }
    move(map->y_stair,map->x_stair );
    printw("<");
    //Pillar
    for(int i = 0; i < 3; i++){
        map->pillors[i].number_room = rand() % map->number_of_rooms;
    }
    for(int i = 0; i < 3; i++){
        map->pillors[i].x_pillar = 0;
        map->pillors[i].y_pillar = 0;
        while(map->pillors[i].x_pillar == 0 || map->pillors[i].y_pillar == 0 || (map->pillors[i].x_pillar == map->x_stair && map->pillors[i].y_pillar == map->y_stair)){
            map->pillors[i].x_pillar = rand() % ((map->rooms[map->pillors[i].number_room].x + map->rooms[map->pillors[i].number_room].size - 2) - (map->rooms[map->pillors[i].number_room].x + 2) + 1) + ((map->rooms[map->pillors[i].number_room].x + 2));
            map->pillors[i].y_pillar = rand() % ((map->rooms[map->pillors[i].number_room].y + map->rooms[map->pillors[i].number_room].size - 2) - (map->rooms[map->pillors[i].number_room].y + 2) + 1) + ((map->rooms[map->pillors[i].number_room].y + 2));
        }
    }
    for(int i = 0; i < 3; i++){
        move(map->pillors[i].y_pillar,map->pillors[i].x_pillar);
        printw("O");
    }
    //Window
    // ... کدهای مربوط به پنجره‌ها (در اینجا کامنت شده‌اند) ...

    // مقداردهی اولیه ماتریس بازدید شده

    //Corridor
    connect_doors(map);
    if(map->number_of_rooms == 6){
        map->corridors[size].x_corridor = map->rooms[0].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[0].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[0].doors[1].x_door;
        map->corridors[size].y_corrifer = map->rooms[0].doors[1].y_door + 1;
        size++;
        map->corridors[size].x_corridor = map->rooms[1].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[1].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[1].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[1].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[2].doors[0].x_door;
        map->corridors[size].y_corrifer = map->rooms[2].doors[0].y_door - 1;
        size++;
        map->corridors[size].x_corridor = map->rooms[2].doors[1].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[2].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[3].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[3].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[3].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[3].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[4].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[4].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[4].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[4].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[5].doors[0].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[5].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[5].doors[1].x_door;
        map->corridors[size].y_corrifer = map->rooms[5].doors[1].y_door + 1;
        size++;
    }
    if(map->number_of_rooms == 7){
        map->corridors[size].x_corridor = map->rooms[0].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[0].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[0].doors[1].x_door;
        map->corridors[size].y_corrifer = map->rooms[0].doors[1].y_door + 1;
        size++;
        map->corridors[size].x_corridor = map->rooms[1].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[1].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[1].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[1].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[2].doors[0].x_door;
        map->corridors[size].y_corrifer = map->rooms[2].doors[0].y_door - 1;
        size++;
        map->corridors[size].x_corridor = map->rooms[2].doors[1].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[2].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[3].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[3].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[3].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[3].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[4].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[4].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[4].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[4].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[5].doors[0].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[5].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[5].doors[1].x_door;
        map->corridors[size].y_corrifer = map->rooms[5].doors[1].y_door + 1;
        size++;
        map->corridors[size].x_corridor = map->rooms[6].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[6].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[6].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[6].doors[0].y_door;
        size++;
    }
    if(map->number_of_rooms == 8){
        map->corridors[size].x_corridor = map->rooms[0].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[0].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[0].doors[1].x_door;
        map->corridors[size].y_corrifer = map->rooms[0].doors[1].y_door + 1;
        size++;
        map->corridors[size].x_corridor = map->rooms[1].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[1].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[1].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[1].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[2].doors[0].x_door;
        map->corridors[size].y_corrifer = map->rooms[2].doors[0].y_door - 1;
        size++;
        map->corridors[size].x_corridor = map->rooms[2].doors[1].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[2].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[3].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[3].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[3].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[3].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[4].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[4].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[4].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[4].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[5].doors[0].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[5].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[5].doors[1].x_door;
        map->corridors[size].y_corrifer = map->rooms[5].doors[1].y_door + 1;
        size++;
        map->corridors[size].x_corridor = map->rooms[6].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[6].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[6].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[6].doors[0].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[7].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[7].doors[1].y_door;
        size++;
        map->corridors[size].x_corridor = map->rooms[7].doors[0].x_door;
        map->corridors[size].y_corrifer = map->rooms[7].doors[0].y_door - 1;
        size++;
    }
    map->corridor_count = size;
}

int can_have_room(struct Room rooms[8], int current_room) {  
    for (int i = 0; i < current_room; i++) {  
        if ((rooms[current_room].x < rooms[i].x + rooms[i].size + 4) &&   
            (rooms[current_room].x + rooms[current_room].size > rooms[i].x - 4) &&   
            (rooms[current_room].y > rooms[i].y - rooms[i].size - 4) &&   
            (rooms[current_room].y - rooms[current_room].size < rooms[i].y + 4)) {  
            return 0;  
        }  
    }  
    return 1;  
}

int is_path_clear(struct Map *map, int x, int y) {
    for(int i = 0; i < map->number_of_rooms; i++) {
        int room_x1 = map->rooms[i].x;
        int room_x2 = map->rooms[i].x + map->rooms[i].size;
        int room_y1 = map->rooms[i].y;
        int room_y2 = map->rooms[i].y + map->rooms[i].size;

        if(x >= room_x1 && x <= room_x2 && y >= room_y1 && y <= room_y2) {
            return 0;
        }
    }
    return 1;
}
int draw_corridor(struct Map *map, int start_x, int start_y, int end_x, int end_y) {
    int x = start_x;
    int y = start_y;
    if(x == end_x && y == end_y){
        return 1;
    }
    if(x > end_x){
        x -= 1;
        if(x == end_x && y != end_y){
            x += 1;
        }
        else if(is_path_clear(map,x,y)){
            map->corridors[size].x_corridor = x;
            map->corridors[size].y_corrifer = y;
            size++;
            draw_corridor(map,x,y,end_x,end_y);
            return 1;
        }
        else{
            x += 1;
        }
    }
    if(x < end_x){
        x += 1;
        if(x == end_x && y != end_y){
            x -= 1;
        }
        else if(is_path_clear(map,x,y)){
            map->corridors[size].x_corridor = x;
            map->corridors[size].y_corrifer = y;
            size++;
            draw_corridor(map,x,y,end_x,end_y);
            return 1;
        }else{
            x -=1 ;
        }
    }
    if(y > end_y){
        y -= 1;
        if(x != end_x && y == end_y){
            y += 1;
        }
        else if(is_path_clear(map,x,y)){
            map->corridors[size].x_corridor = x;
            map->corridors[size].y_corrifer = y;
            size++;
            draw_corridor(map,x,y,end_x,end_y);
            return 1;
        }else{
            y += 1;
        }
    }
    if(y < end_y){
        y += 1;
        if(x != end_x && y == end_y){
            y -= 1;
        }
        else if(is_path_clear(map,x,y)){
            map->corridors[size].x_corridor = x;
            map->corridors[size].y_corrifer = y;
            size++;
            draw_corridor(map,x,y,end_x,end_y);
            return 1;
        }else{
            y -= 1;
        }
    }
    refresh();
    return 0;
}

void connect_doors(struct Map *map) {
    if(map->number_of_rooms == 6){
        draw_corridor(map,map->rooms[0].doors[0].x_door,map->rooms[0].doors[0].y_door,map->rooms[1].doors[1].x_door,map->rooms[1].doors[1].y_door);
        draw_corridor(map,map->rooms[1].doors[0].x_door,map->rooms[1].doors[0].y_door,map->rooms[4].doors[1].x_door,map->rooms[4].doors[1].y_door);
        draw_corridor(map,map->rooms[4].doors[0].x_door,map->rooms[4].doors[0].y_door,map->rooms[5].doors[0].x_door,map->rooms[5].doors[0].y_door);
        draw_corridor(map,map->rooms[5].doors[1].x_door,map->rooms[5].doors[1].y_door,map->rooms[3].doors[0].x_door,map->rooms[3].doors[0].y_door);
        draw_corridor(map,map->rooms[3].doors[1].x_door,map->rooms[3].doors[1].y_door,map->rooms[2].doors[1].x_door,map->rooms[2].doors[1].y_door);
        draw_corridor(map,map->rooms[2].doors[0].x_door,map->rooms[2].doors[0].y_door,map->rooms[0].doors[1].x_door,map->rooms[0].doors[1].y_door);
    }
    if(map->number_of_rooms == 7){
        draw_corridor(map,map->rooms[0].doors[0].x_door,map->rooms[0].doors[0].y_door,map->rooms[1].doors[1].x_door,map->rooms[1].doors[1].y_door);
        draw_corridor(map,map->rooms[1].doors[0].x_door,map->rooms[1].doors[0].y_door,map->rooms[4].doors[1].x_door,map->rooms[4].doors[1].y_door);
        draw_corridor(map,map->rooms[4].doors[0].x_door,map->rooms[4].doors[0].y_door,map->rooms[5].doors[0].x_door,map->rooms[5].doors[0].y_door);
        draw_corridor(map,map->rooms[5].doors[1].x_door,map->rooms[5].doors[1].y_door,map->rooms[6].doors[0].x_door,map->rooms[6].doors[0].y_door);
        draw_corridor(map,map->rooms[6].doors[1].x_door,map->rooms[6].doors[1].y_door,map->rooms[3].doors[0].x_door,map->rooms[3].doors[0].y_door);
        draw_corridor(map,map->rooms[3].doors[1].x_door,map->rooms[3].doors[1].y_door,map->rooms[2].doors[1].x_door,map->rooms[2].doors[1].y_door);
        draw_corridor(map,map->rooms[2].doors[0].x_door,map->rooms[2].doors[0].y_door,map->rooms[0].doors[1].x_door,map->rooms[0].doors[1].y_door);
    }
    if(map->number_of_rooms == 8){
        draw_corridor(map,map->rooms[0].doors[0].x_door,map->rooms[0].doors[0].y_door,map->rooms[1].doors[1].x_door,map->rooms[1].doors[1].y_door);
        draw_corridor(map,map->rooms[1].doors[0].x_door,map->rooms[1].doors[0].y_door,map->rooms[4].doors[1].x_door,map->rooms[4].doors[1].y_door);
        draw_corridor(map,map->rooms[4].doors[0].x_door,map->rooms[4].doors[0].y_door,map->rooms[5].doors[0].x_door,map->rooms[5].doors[0].y_door);
        draw_corridor(map,map->rooms[5].doors[1].x_door,map->rooms[5].doors[1].y_door,map->rooms[7].doors[0].x_door,map->rooms[7].doors[0].y_door);
        draw_corridor(map,map->rooms[7].doors[1].x_door,map->rooms[7].doors[1].y_door,map->rooms[6].doors[0].x_door,map->rooms[6].doors[0].y_door);
        draw_corridor(map,map->rooms[6].doors[1].x_door,map->rooms[6].doors[1].y_door,map->rooms[3].doors[0].x_door,map->rooms[3].doors[0].y_door);
        draw_corridor(map,map->rooms[3].doors[1].x_door,map->rooms[3].doors[1].y_door,map->rooms[2].doors[1].x_door,map->rooms[2].doors[1].y_door);
        draw_corridor(map,map->rooms[2].doors[0].x_door,map->rooms[2].doors[0].y_door,map->rooms[0].doors[1].x_door,map->rooms[0].doors[1].y_door);
    }
}
void print_map(int number_of_rooms, struct Room rooms[8], struct Map *map) {  
    for (int i = 0; i < number_of_rooms; i++) {  
        int x_1 = rooms[i].x;  
        int x_2 = rooms[i].x + rooms[i].size;  
        int y_1 = rooms[i].y;  
        int y_3 = rooms[i].y + rooms[i].size;  

        for (int j = 0; j <= rooms[i].size; j++) {  
            move(y_1, x_1 + j);  
            printw("_");  
            move(y_3, x_1 + j);  
            printw("_");  
        }  

        for (int j = 0; j < rooms[i].size; j++) {  
            move(y_1 + j + 1, x_1);  
            printw("|");
            move(y_1 + j + 1, x_2);  
            printw("|");  
        }  
    }
    for(int i = 0; i < number_of_rooms; i++){
        for(int j = 0; j < 2; j++){
            move(rooms[i].doors[j].y_door, rooms[i].doors[j].x_door);
            printw("+");
        }
    }
    for(int i = 0; i < map->corridor_count; i++){
        move(map->corridors[i].y_corrifer,map->corridors[i].x_corridor);
        printw("#");
    }
    refresh();
}