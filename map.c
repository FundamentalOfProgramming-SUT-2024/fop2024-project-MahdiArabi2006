#include <ncurses.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include <locale.h> 
#include <unistd.h>
#include <string.h>
int size = 0;

struct Food{
    int x_food;
    int y_food;
    int number_room;
    int type;//1-4
};

struct Spell{
    int x_spell;
    int y_spell;
    int number_room;
    int type;//1-3
};

struct Wepon{
    int x_wepon;
    int y_wepon;
    int number_room;
    int type;//1-5
};

struct Gold{
    int x_gold;
    int y_gold;
    int is_black;
    int worth;
    int number_room;
};

struct Player{
    int x;
    int y;
    int food_number;
    struct Food foods[12];
    int health;
    int wepon_number;
    struct Wepon wepons[12];
    int spell_number;
    struct Spell spells[12];
    int gold;
    int have_master_key;
};

struct Trap{
    int x_trap;
    int y_trap;
    int number_room;
};

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
    int is_secret_door;
    int is_password_door;
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
    struct Trap traps[3];
    int x_fight_room;
    int y_fight_room;
    int number_room_fight_room;
    int number_Spell_room;
    int number_Password_Doors_room;
    int x_create_paasword;
    int y_create_paasword;
    int number_Master_Key_room;
    int x_Master_Key;
    int y_Master_Key;
    struct Gold golds[3];
    struct Wepon wepons[3];
    struct Spell spells[3];
    struct Food foods[3];
    int last_password;
    int x_password_door;
    int y_password_door;
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
int deciphering();
int is_pillor(struct Map *map,int x, int y);
int is_trap(struct Map *map,int x, int y);
int is_gold(struct Map *map,int x, int y);
int is_spell(struct Map *map,int x, int y);
int is_wepon(struct Map *map,int x, int y);
int is_food(struct Map *map,int x, int y);
void move_player(struct Map *map,struct Player *p);
int is_not_wall(struct Map *map, int x, int y);
int is_door(struct Map *map,int x, int y);
int is_corridor(struct Map *map,int x, int y);
void move_effect(const char* state,struct Player *p,struct Map* map,int x,int y);
void f_gold(struct Map *map,int x, int y);
void f_spell(struct Map *map,int x, int y);
void f_wepon(struct Map *map,int x, int y);
void f_food(struct Map *map,int x, int y);
int index_gold(struct Map *map,int x, int y);
int index_spell(struct Map *map,int x, int y);
int index_wepon(struct Map *map,int x, int y);
int index_food(struct Map *map,int x, int y);
int is_master_key(struct Map *map,int x, int y);
void f_master_key(struct Map *map,int x, int y);
int is_password_door(struct Map *map,int x, int y);
int is_fight_room(struct Map *map,int x, int y);
void f_fight(struct Map *map,int x,int y);
int is_create_password(struct Map *map,int x,int y);
void create_password(struct Map *map,time_t time_start);
int panel(struct Player* p,struct Map *map);
void regular_move(struct Player *p,struct Map *map,int second_x,int second_y,time_t time_start);
void f_move(struct Player *p,struct Map *map,int second_x,int second_y,time_t time_start);
void g_move(struct Player *p,struct Map *map,int second_x,int second_y,time_t time_start);


int main() {
    initscr();  
    cbreak();  
    noecho();  
    srand(time(0));
    generate_map(&game.maps[0]);
    print_map(game.maps[0].number_of_rooms, game.maps[0].rooms, &game.maps[0]);
    struct Player p;
    move_player(&game.maps[0],&p);
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
            map->rooms[current_room].doors[0].is_secret_door = 0;
            map->rooms[current_room].doors[0].is_password_door = 0;
            //3
            map->rooms[current_room].doors[1].x_door = rand() % ((map->rooms[current_room].x + map->rooms[current_room].size - 1) - (map->rooms[current_room].x + 1) + 1) + map->rooms[current_room].x + 1;
            map->rooms[current_room].doors[1].y_door = map->rooms[current_room].y + map->rooms[current_room].size;
            map->rooms[current_room].doors[1].room_number = current_room;
            map->rooms[current_room].doors[1].is_secret_door = 0;
            map->rooms[current_room].doors[1].is_password_door = 0;
        }
        if(current_room + 1 == 2){
            //2
            map->rooms[current_room].doors[0].x_door = map->rooms[current_room].x + map->rooms[current_room].size;
            map->rooms[current_room].doors[0].y_door = rand() % ((map->rooms[current_room].y + map->rooms[current_room].size - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[0].room_number = current_room;
            map->rooms[current_room].doors[0].is_secret_door = 0;
            map->rooms[current_room].doors[0].is_password_door = 0;
            //4
            map->rooms[current_room].doors[1].x_door = map->rooms[current_room].x;
            map->rooms[current_room].doors[1].y_door = rand() % (((map->rooms[current_room].y + map->rooms[current_room].size) - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[1].room_number = current_room;
            map->rooms[current_room].doors[1].is_secret_door = 0;
            map->rooms[current_room].doors[1].is_password_door = 0;
        }
        if(current_room + 1 == 3){
            //1
            map->rooms[current_room].doors[0].x_door = rand() % ((map->rooms[current_room].x + map->rooms[current_room].size - 1) - (map->rooms[current_room].x + 1) + 1) + (map->rooms[current_room].x + 1);
            map->rooms[current_room].doors[0].y_door = map->rooms[current_room].y;
            map->rooms[current_room].doors[0].room_number = current_room;
            map->rooms[current_room].doors[0].is_secret_door = 0;
            map->rooms[current_room].doors[0].is_password_door = 0;
            //2
            map->rooms[current_room].doors[1].x_door = map->rooms[current_room].x + map->rooms[current_room].size;
            map->rooms[current_room].doors[1].y_door = rand() % ((map->rooms[current_room].y + map->rooms[current_room].size - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[1].room_number = current_room;
            map->rooms[current_room].doors[1].is_secret_door = 0;
            map->rooms[current_room].doors[1].is_password_door = 0;
        }
        if(current_room + 1 == 4){
            //2
            map->rooms[current_room].doors[0].x_door = map->rooms[current_room].x + map->rooms[current_room].size;
            map->rooms[current_room].doors[0].y_door = rand() % ((map->rooms[current_room].y + map->rooms[current_room].size - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[0].room_number = current_room;
            map->rooms[current_room].doors[0].is_secret_door = 0;
            map->rooms[current_room].doors[0].is_password_door = 0;

            //4
            map->rooms[current_room].doors[1].x_door = map->rooms[current_room].x;
            map->rooms[current_room].doors[1].y_door = rand() % (((map->rooms[current_room].y + map->rooms[current_room].size) - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[1].room_number = current_room;
            map->rooms[current_room].doors[1].is_secret_door = 0;
            map->rooms[current_room].doors[1].is_password_door = 0;
        }
        if(current_room + 1 == 5){
            //2
            map->rooms[current_room].doors[0].x_door = map->rooms[current_room].x + map->rooms[current_room].size;
            map->rooms[current_room].doors[0].y_door = rand() % ((map->rooms[current_room].y + map->rooms[current_room].size - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[0].room_number = current_room;
            map->rooms[current_room].doors[0].is_secret_door = 0;
            map->rooms[current_room].doors[0].is_password_door = 0;
            //4
            map->rooms[current_room].doors[1].x_door = map->rooms[current_room].x;
            map->rooms[current_room].doors[1].y_door = rand() % (((map->rooms[current_room].y + map->rooms[current_room].size) - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[1].room_number = current_room;
            map->rooms[current_room].doors[1].is_secret_door = 0;
            map->rooms[current_room].doors[1].is_password_door = 0;
        }
        if(current_room + 1 == 6){
            //4
            map->rooms[current_room].doors[0].x_door = map->rooms[current_room].x;
            map->rooms[current_room].doors[0].y_door = rand() % (((map->rooms[current_room].y + map->rooms[current_room].size) - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[0].room_number = current_room;
            map->rooms[current_room].doors[0].is_secret_door = 0;
            map->rooms[current_room].doors[0].is_password_door = 0;
            //3
            map->rooms[current_room].doors[1].x_door = rand() % ((map->rooms[current_room].x + map->rooms[current_room].size - 1) - (map->rooms[current_room].x + 1) + 1) + map->rooms[current_room].x + 1;
            map->rooms[current_room].doors[1].y_door = map->rooms[current_room].y + map->rooms[current_room].size;
            map->rooms[current_room].doors[1].room_number = current_room;
            map->rooms[current_room].doors[1].is_secret_door = 0;
            map->rooms[current_room].doors[1].is_password_door = 0;
        }
        if(current_room + 1 == 7){
            //2
            map->rooms[current_room].doors[0].x_door = map->rooms[current_room].x + map->rooms[current_room].size;
            map->rooms[current_room].doors[0].y_door = rand() % ((map->rooms[current_room].y + map->rooms[current_room].size - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[0].room_number = current_room;
            map->rooms[current_room].doors[0].is_secret_door = 0;
            map->rooms[current_room].doors[0].is_password_door = 0;
            //4
            map->rooms[current_room].doors[1].x_door = map->rooms[current_room].x;
            map->rooms[current_room].doors[1].y_door = rand() % (((map->rooms[current_room].y + map->rooms[current_room].size) - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[1].room_number = current_room;
            map->rooms[current_room].doors[1].is_secret_door = 0;
            map->rooms[current_room].doors[1].is_password_door = 0;
        }
        if(current_room + 1 == 8){
            //1
            map->rooms[current_room].doors[0].x_door = rand() % ((map->rooms[current_room].x + map->rooms[current_room].size - 1) - (map->rooms[current_room].x + 1) + 1) + (map->rooms[current_room].x + 1);
            map->rooms[current_room].doors[0].y_door = map->rooms[current_room].y;
            map->rooms[current_room].doors[0].room_number = current_room;
            map->rooms[current_room].doors[0].is_secret_door = 0;
            map->rooms[current_room].doors[0].is_password_door = 0;
            //4
            map->rooms[current_room].doors[1].x_door = map->rooms[current_room].x;
            map->rooms[current_room].doors[1].y_door = rand() % (((map->rooms[current_room].y + map->rooms[current_room].size) - 1) - (map->rooms[current_room].y + 1) + 1) + (map->rooms[current_room].y + 1);
            map->rooms[current_room].doors[1].room_number = current_room;
            map->rooms[current_room].doors[1].is_secret_door = 0;
            map->rooms[current_room].doors[1].is_password_door = 0;
        }
        current_room ++;
    }
    //Stair
    map->number_room_stair = rand() % map->number_of_rooms;
    map->x_stair = 0;
    map->y_stair = 0;
    while(map->x_stair == 0 || map->y_stair == 0){
        map->x_stair = rand() % ((map->rooms[map->number_room_stair].x + map->rooms[map->number_room_stair].size - 1) - (map->rooms[map->number_room_stair].x + 1) + 1) + ((map->rooms[map->number_room_stair].x + 1));
        map->y_stair = rand() % ((map->rooms[map->number_room_stair].y + map->rooms[map->number_room_stair].size - 1) - (map->rooms[map->number_room_stair].y + 1) + 1) + ((map->rooms[map->number_room_stair].y + 1));
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
            map->pillors[i].x_pillar = rand() % ((map->rooms[map->pillors[i].number_room].x + map->rooms[map->pillors[i].number_room].size - 1) - (map->rooms[map->pillors[i].number_room].x + 1) + 1) + ((map->rooms[map->pillors[i].number_room].x + 1));
            map->pillors[i].y_pillar = rand() % ((map->rooms[map->pillors[i].number_room].y + map->rooms[map->pillors[i].number_room].size - 1) - (map->rooms[map->pillors[i].number_room].y + 1) + 1) + ((map->rooms[map->pillors[i].number_room].y + 1));
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
    //Traps
    for(int i = 0; i < 3; i++){
        map->traps[i].number_room = rand() % map->number_of_rooms;
    }
    for(int i = 0; i < 3; i++){
        map->traps[i].x_trap = 0;
        map->traps[i].y_trap = 0;
        while(map->traps[i].x_trap == 0 || map->traps[i].y_trap == 0 || (map->traps[i].x_trap == map->x_stair && map->traps[i].y_trap == map->y_stair) || (map->traps[i].x_trap == map->pillors[0].x_pillar && map->traps[i].y_trap == map->pillors[0].y_pillar) || (map->traps[i].x_trap == map->pillors[1].x_pillar && map->traps[i].y_trap == map->pillors[1].y_pillar) || (map->traps[i].x_trap == map->pillors[2].x_pillar && map->traps[i].y_trap == map->pillors[2].y_pillar)){
            map->traps[i].x_trap = rand() % ((map->rooms[map->traps[i].number_room].x + map->rooms[map->traps[i].number_room].size - 1) - (map->rooms[map->traps[i].number_room].x + 1) + 1) + ((map->rooms[map->traps[i].number_room].x + 1));
            map->traps[i].y_trap = rand() % ((map->rooms[map->traps[i].number_room].y + map->rooms[map->traps[i].number_room].size - 1) - (map->rooms[map->traps[i].number_room].y + 1) + 1) + ((map->rooms[map->traps[i].number_room].y + 1));
        }
    }
    for(int i = 0; i < 3; i++){
        move(map->traps[i].y_trap,map->traps[i].x_trap);
        printw("^");
    }
    //Fight_room
    map->number_room_fight_room = rand() % map->number_of_rooms;
    map->x_fight_room = 0;
    map->y_fight_room = 0;
    while(map->x_fight_room == 0 || map->y_fight_room == 0 || (map->x_fight_room == map->x_stair && map->y_fight_room == map->y_stair) || (map->x_fight_room == map->pillors[0].x_pillar && map->y_fight_room == map->pillors[0].y_pillar) || (map->x_fight_room == map->pillors[1].x_pillar && map->y_fight_room == map->pillors[1].y_pillar) || (map->x_fight_room == map->pillors[2].x_pillar && map->y_fight_room == map->pillors[2].y_pillar) || (map->x_fight_room == map->traps[0].x_trap && map->y_fight_room == map->traps[0].y_trap) || (map->x_fight_room == map->traps[1].x_trap && map->y_fight_room == map->traps[1].y_trap) || (map->x_fight_room == map->traps[2].x_trap && map->y_fight_room == map->traps[2].y_trap)){
        map->x_fight_room = rand() % ((map->rooms[map->number_room_fight_room].x + map->rooms[map->number_room_fight_room].size - 1) - (map->rooms[map->number_room_fight_room].x + 1) + 1) + ((map->rooms[map->number_room_fight_room].x + 1));
        map->y_fight_room = rand() % ((map->rooms[map->number_room_fight_room].y + map->rooms[map->number_room_fight_room].size - 1) - (map->rooms[map->number_room_fight_room].y + 1) + 1) + ((map->rooms[map->number_room_fight_room].y + 1));
    }
    move(map->y_fight_room,map->x_fight_room);
    printw("F");
    //Spell_room && Secret Doors
    map->number_Spell_room = rand() % map->number_of_rooms;
    map->rooms[map->number_Spell_room].doors[0].is_secret_door = 1;
    map->rooms[map->number_Spell_room].doors[1].is_secret_door = 1;
    //Password Doors
    map->number_Password_Doors_room = rand() % map->number_of_rooms;
    while(map->number_Password_Doors_room == map->number_Spell_room){
        map->number_Password_Doors_room = rand() % map->number_of_rooms;
    }
    map->rooms[map->number_Password_Doors_room].doors[0].is_password_door = 1;
    map->x_password_door = map->rooms[map->number_Password_Doors_room].doors[0].x_door;
    map->y_password_door = map->rooms[map->number_Password_Doors_room].doors[0].y_door;
    //Create_password
    map->x_create_paasword = 0;
    map->y_create_paasword = 0;
    while(map->x_create_paasword == 0 || map->y_create_paasword == 0 || (map->x_create_paasword == map->x_stair && map->y_create_paasword == map->y_stair) || (map->x_create_paasword == map->x_fight_room && map->y_create_paasword == map->y_fight_room) || (map->x_create_paasword == map->pillors[0].x_pillar && map->y_create_paasword == map->pillors[0].y_pillar) || (map->x_create_paasword == map->pillors[1].x_pillar && map->y_create_paasword == map->pillors[1].y_pillar) || (map->x_create_paasword == map->pillors[2].x_pillar && map->y_create_paasword == map->pillors[2].y_pillar) || (map->x_create_paasword == map->traps[0].x_trap && map->y_create_paasword == map->traps[0].y_trap) || (map->x_create_paasword == map->traps[1].x_trap && map->y_create_paasword == map->traps[1].y_trap) || (map->x_create_paasword == map->traps[2].x_trap && map->y_create_paasword == map->traps[2].y_trap)){
        map->x_create_paasword = rand() % ((map->rooms[map->number_Password_Doors_room].x + map->rooms[map->number_Password_Doors_room].size - 1) - (map->rooms[map->number_Password_Doors_room].x + 1) + 1) + ((map->rooms[map->number_Password_Doors_room].x + 1));
        map->y_create_paasword = rand() % ((map->rooms[map->number_Password_Doors_room].y + map->rooms[map->number_Password_Doors_room].size - 1) - (map->rooms[map->number_Password_Doors_room].y + 1) + 1) + ((map->rooms[map->number_Password_Doors_room].y + 1));
    }
    move(map->y_create_paasword,map->x_create_paasword);
    printw("&");
    //Master Key
    map->number_Master_Key_room = rand() % map->number_of_rooms;
    map->x_Master_Key = 0;
    map->y_Master_Key = 0;
    while(map->x_Master_Key == 0 || map->y_Master_Key == 0 || (map->x_Master_Key == map->x_stair && map->y_Master_Key == map->y_stair) || (map->x_Master_Key == map->x_create_paasword && map->y_Master_Key == map->y_create_paasword) || (map->x_Master_Key == map->x_fight_room && map->y_Master_Key == map->y_fight_room) || is_pillor(map,map->x_Master_Key,map->y_Master_Key) || is_trap(map,map->x_Master_Key,map->y_Master_Key)){
        map->x_Master_Key = rand() % ((map->rooms[map->number_Master_Key_room].x + map->rooms[map->number_Master_Key_room].size - 1) - (map->rooms[map->number_Master_Key_room].x + 1) + 1) + ((map->rooms[map->number_Master_Key_room].x + 1));
        map->y_Master_Key = rand() % ((map->rooms[map->number_Master_Key_room].y + map->rooms[map->number_Master_Key_room].size - 1) - (map->rooms[map->number_Master_Key_room].y + 1) + 1) + ((map->rooms[map->number_Master_Key_room].y + 1));
    }
    start_color();
    init_pair(1,COLOR_YELLOW,COLOR_WHITE);
    attron(COLOR_PAIR(1));
    mvprintw(map->y_Master_Key, map->x_Master_Key,"K");
    attroff(COLOR_PAIR(1));
    refresh();
    //Foods
    for(int i = 0; i < 3; i++){
        map->foods[i].number_room = rand() % map->number_of_rooms;
        map->foods[i].type = rand() % 4 + 1;
    }
    for(int i = 0; i < 3; i++){
        map->foods[i].x_food = 0;
        map->foods[i].y_food = 0;
        while(map->foods[i].x_food == 0 || map->foods[i].y_food == 0 || (map->foods[i].x_food == map->x_stair && map->foods[i].y_food == map->y_stair) || (map->foods[i].x_food == map->x_create_paasword && map->foods[i].y_food == map->y_create_paasword) || (map->foods[i].x_food == map->x_fight_room && map->foods[i].y_food == map->y_fight_room) || (map->foods[i].x_food == map->x_Master_Key && map->foods[i].y_food == map->y_Master_Key) || is_pillor(map,map->foods[i].x_food,map->foods[i].y_food) || is_trap(map,map->foods[i].x_food,map->foods[i].y_food)){
            map->foods[i].x_food = rand() % ((map->rooms[map->foods[i].number_room].x + map->rooms[map->foods[i].number_room].size - 1) - (map->rooms[map->foods[i].number_room].x + 1) + 1) + ((map->rooms[map->foods[i].number_room].x + 1));
            map->foods[i].y_food = rand() % ((map->rooms[map->foods[i].number_room].y + map->rooms[map->foods[i].number_room].size - 1) - (map->rooms[map->foods[i].number_room].y + 1) + 1) + ((map->rooms[map->foods[i].number_room].y + 1));
        }
    }
    for(int i = 0; i < 3; i++){
        move(map->foods[i].y_food,map->foods[i].x_food);
        printw("f");
    }
    //Spells
    for(int i = 0; i < 3; i++){
        map->spells[i].number_room = rand() % map->number_of_rooms;
        map->spells[i].type = rand() % 3 + 1;
    }
    for(int i = 0; i < 3; i++){
        map->spells[i].x_spell = 0;
        map->spells[i].y_spell = 0;
        while(map->spells[i].x_spell == 0 || map->spells[i].y_spell == 0 || (map->spells[i].x_spell == map->x_stair && map->spells[i].y_spell == map->y_stair) || (map->spells[i].x_spell == map->x_create_paasword && map->spells[i].y_spell == map->y_create_paasword) || (map->spells[i].x_spell == map->x_fight_room && map->spells[i].y_spell == map->y_fight_room) || (map->spells[i].x_spell == map->x_Master_Key && map->spells[i].y_spell == map->y_Master_Key) || is_pillor(map,map->spells[i].x_spell,map->spells[i].y_spell) || is_trap(map,map->spells[i].x_spell,map->spells[i].y_spell) || is_food(map,map->spells[i].x_spell,map->spells[i].y_spell)){
            map->spells[i].x_spell = rand() % ((map->rooms[map->spells[i].number_room].x + map->rooms[map->spells[i].number_room].size - 1) - (map->rooms[map->spells[i].number_room].x + 1) + 1) + ((map->rooms[map->spells[i].number_room].x + 1));
            map->spells[i].y_spell = rand() % ((map->rooms[map->spells[i].number_room].y + map->rooms[map->spells[i].number_room].size - 1) - (map->rooms[map->spells[i].number_room].y + 1) + 1) + ((map->rooms[map->spells[i].number_room].y + 1));
        }
    }
    for(int i = 0; i < 3; i++){
        move(map->spells[i].y_spell,map->spells[i].x_spell);
        printw("S");
    }
    //Wepons
    for(int i = 0; i < 3; i++){
        map->wepons[i].number_room = rand() % map->number_of_rooms;
        map->wepons[i].type = rand() % 5 + 1;
    }
    for(int i = 0; i < 3; i++){
        map->wepons[i].x_wepon = 0;
        map->wepons[i].y_wepon = 0;
        while(map->wepons[i].x_wepon == 0 || map->wepons[i].x_wepon == 0 || (map->wepons[i].x_wepon == map->x_stair && map->wepons[i].y_wepon == map->y_stair) || (map->wepons[i].x_wepon == map->x_create_paasword && map->wepons[i].y_wepon == map->y_create_paasword) || (map->wepons[i].x_wepon == map->x_fight_room && map->wepons[i].y_wepon == map->y_fight_room) || (map->wepons[i].x_wepon == map->x_Master_Key && map->wepons[i].y_wepon == map->y_Master_Key) || is_pillor(map,map->wepons[i].x_wepon,map->wepons[i].y_wepon) || is_trap(map,map->wepons[i].x_wepon,map->wepons[i].y_wepon) || is_food(map,map->wepons[i].x_wepon,map->wepons[i].y_wepon) || is_spell(map,map->wepons[i].x_wepon,map->wepons[i].y_wepon)){
            map->wepons[i].x_wepon = rand() % ((map->rooms[map->wepons[i].number_room].x + map->rooms[map->wepons[i].number_room].size - 1) - (map->rooms[map->wepons[i].number_room].x + 1) + 1) + ((map->rooms[map->wepons[i].number_room].x + 1));
            map->wepons[i].y_wepon = rand() % ((map->rooms[map->wepons[i].number_room].y + map->rooms[map->wepons[i].number_room].size - 1) - (map->rooms[map->wepons[i].number_room].y + 1) + 1) + ((map->rooms[map->wepons[i].number_room].y + 1));
        }
    }
    for(int i = 0; i < 3; i++){
        move(map->wepons[i].y_wepon,map->wepons[i].x_wepon);
        printw("W");
    }
    //Golds
    int wich_black = rand() % 5;
    for(int i = 0; i < 3; i++){
        map->golds[i].number_room = rand() % map->number_of_rooms;
        if(i == wich_black){
            map->golds[i].is_black = 1;
            map->golds[i].worth = 500;
        }
        map->golds[i].worth = rand() % (300 - 100 + 1) + 100;
        map->golds[i].is_black = 0;
    }
    for(int i = 0; i < 3; i++){
        map->golds[i].x_gold = 0;
        map->golds[i].y_gold = 0;
        while(map->golds[i].x_gold == 0 || map->golds[i].y_gold == 0 || (map->golds[i].x_gold == map->x_stair && map->golds[i].y_gold == map->y_stair) || (map->golds[i].x_gold == map->x_create_paasword && map->golds[i].y_gold == map->y_create_paasword) || (map->golds[i].x_gold == map->x_fight_room && map->golds[i].y_gold == map->y_fight_room) || (map->golds[i].x_gold == map->x_Master_Key && map->golds[i].y_gold == map->y_Master_Key) || is_pillor(map,map->golds[i].x_gold,map->golds[i].y_gold) || is_trap(map,map->golds[i].x_gold,map->golds[i].y_gold) || is_food(map,map->golds[i].x_gold,map->golds[i].y_gold) || is_spell(map,map->golds[i].x_gold,map->golds[i].y_gold) || is_wepon(map,map->golds[i].x_gold,map->golds[i].y_gold)){
            map->golds[i].x_gold = rand() % ((map->rooms[map->golds[i].number_room].x + map->rooms[map->golds[i].number_room].size - 1) - (map->rooms[map->golds[i].number_room].x + 1) + 1) + ((map->rooms[map->golds[i].number_room].x + 1));
            map->golds[i].y_gold = rand() % ((map->rooms[map->golds[i].number_room].y + map->rooms[map->golds[i].number_room].size - 1) - (map->rooms[map->golds[i].number_room].y + 1) + 1) + ((map->rooms[map->golds[i].number_room].y + 1));
        }
    }
    for(int i = 0; i < 3; i++){
        move(map->golds[i].y_gold,map->golds[i].x_gold);
        printw("G");
    }
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
        if(i == map->number_Password_Doors_room){
            move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
            printw("@");
            move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
            printw("+");
            continue;
        }
        if(i == map->number_Spell_room){
            if(i == 0){
                move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                printw("|");
                move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                printw("_");
                continue;
            }
            if(i == 1){
                move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                printw("|");
                move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                printw("|");
                continue;
            }
            if(i == 2){
                move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                printw("_");
                move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                printw("|");
                continue;
            }
            if(i == 3){
                move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                printw("|");
                move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                printw("|");
                continue;
            }
            if(i == 4){
                move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                printw("|");
                move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                printw("|");
                continue;
            }
            if(i == 5){
                move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                printw("|");
                move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                printw("_");
                continue;
            }
            if(i == 6){
                move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                printw("|");
                move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                printw("|");
                continue;
            }
            if(i == 7){
                move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                printw("_");
                move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                printw("|");
                continue;
            }
        }
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

int deciphering(){
    int key = rand() % (9999 - 1000 + 1) + 1000;
    return key;
}

int is_pillor(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->pillors[i].x_pillar == x && map->pillors[i].y_pillar == y){
            return 1;
        }
    }
    return 0;
}
int is_trap(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->traps[i].x_trap == x && map->traps[i].y_trap == y){
            return 1;
        }
    }
    return 0;
}
int is_gold(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->golds[i].x_gold == x && map->golds[i].y_gold == y){
            return 1;
        }
    }
    return 0;
}
int is_spell(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->spells[i].x_spell == x && map->spells[i].y_spell == y){
            return 1;
        }
    }
    return 0;
}
int is_wepon(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->wepons[i].x_wepon == x && map->wepons[i].y_wepon == y){
            return 1;
        }
    }
    return 0;
}

int is_food(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->foods[i].x_food == x && map->foods[i].y_food == y){
            return 1;
        }
    }
    return 0;
}

void move_player(struct Map *map,struct Player *p){
    raw(); 
    keypad(stdscr, TRUE); 
    noecho();
    curs_set(0);
    int start_room = rand() % map->number_of_rooms;
    p->x = 0;
    p->y = 0;
    p->health = 1000;
    p->food_number = 0;
    p->wepon_number = 0;
    p->spell_number = 0;
    p->gold = 0;
    p->have_master_key = 0;
    move(0,0);
    printw("Helth: %d  Food: %d  Gold: %d",p->health,p->food_number,p->gold);
    while(p->x == 0 || p->y == 0 || (p->x == map->x_stair && p->y == map->y_stair) || (p->x == map->x_create_paasword && p->y == map->y_create_paasword) || (p->x == map->x_fight_room && p->y == map->y_fight_room) || (p->x == map->x_Master_Key && p->y == map->y_Master_Key) || is_pillor(map,p->x,p->y) || is_trap(map,p->x,p->y) || is_food(map,p->x,p->y) || is_spell(map,p->x,p->y) || is_wepon(map,p->x,p->y) || is_gold(map,p->x,p->y)){
        p->x = rand() % ((map->rooms[start_room].x + map->rooms[start_room].size - 1) - (map->rooms[start_room].x + 1) + 1) + ((map->rooms[start_room].x + 1));
        p->y = rand() % ((map->rooms[start_room].y + map->rooms[start_room].size - 1) - (map->rooms[start_room].y + 1) + 1) + ((map->rooms[start_room].y + 1));
    }
    mvprintw(p->y,p->x,"P");
    refresh();
    time_t time_start;
    while (1){
        time_t time_end;
        time(&time_end);
        if(time_end - time_start >= 10){
            move(0,60);
            clrtoeol();
        }
        int c = getch();
        if(c == 'w'){
            regular_move(p,map,0,-1,time_start);
        }
        if(c == 'x'){
            regular_move(p,map,0,1,time_start);
        }
        if(c == 'a'){
            regular_move(p,map,-1,0,time_start);
        }
        if(c == 'd'){
            regular_move(p,map,1,0,time_start);
        }
        if(c == 'e'){
            regular_move(p,map,1,-1,time_start);
        }
        if(c == 'q'){
            regular_move(p,map,-1,-1,time_start);
        }
        if(c == 'c'){
            regular_move(p,map,1,1,time_start);
        }
        if(c == 'z'){
            regular_move(p,map,-1,1,time_start);
        }
        if(c == 'f'){
            int c2 = getch();
            if(c2 == 'w'){
                f_move(p,map,0,-1,time_start);
            }
            if(c2 == 'x'){
                f_move(p,map,0,1,time_start);
            }
            if(c2 == 'd'){
                f_move(p,map,1,0,time_start);
            }
            if(c2 == 'a'){
                f_move(p,map,-1,0,time_start);
            }
            if(c2 == 'e'){
                f_move(p,map,1,-1,time_start);
            }
            if(c2 == 'q'){
                f_move(p,map,-1,-1,time_start);
            }
            if(c2 == 'c'){
                f_move(p,map,1,1,time_start);
            }
            if(c2 == 'z'){
                f_move(p,map,-1,1,time_start);
            }
        }
        if(c == 'g'){
            int c2 = getch();
            if(c2 == 'w'){
                g_move(p,map,0,-1,time_start);
            }
            if(c2 == 'x'){
                g_move(p,map,0,1,time_start);
            }
            if(c2 == 'a'){
                g_move(p,map,-1,0,time_start);
            }
            if(c2 == 'd'){
                g_move(p,map,1,0,time_start);
            }
            if(c2 == 'e'){
                g_move(p,map,1,-1,time_start);
            }
            if(c2 == 'q'){
                g_move(p,map,-1,-1,time_start);
            }
            if(c2 == 'c'){
                g_move(p,map,1,1,time_start);
            }
            if(c2 == 'z'){
                g_move(p,map,-1,1,time_start);
            }
        }
    }
}

int is_not_wall(struct Map *map, int x, int y) {
    for(int i = 0; i < map->number_of_rooms; i++) {
        int room_x1 = map->rooms[i].x;
        int room_x2 = map->rooms[i].x + map->rooms[i].size;
        int room_y1 = map->rooms[i].y;
        int room_y2 = map->rooms[i].y + map->rooms[i].size;

        if(x > room_x1 && x < room_x2 && y > room_y1 && y < room_y2) {
            return 1;
        }
    }
    return 0;
}

int is_door(struct Map *map,int x, int y){
    for(int i = 0; i < map->number_of_rooms; i++){
        if((x == map->rooms[i].doors[0].x_door && y == map->rooms[i].doors[0].y_door) || (x == map->rooms[i].doors[1].x_door && y == map->rooms[i].doors[1].y_door)){
            return 1;
        }
    }
    return 0;
}

int is_corridor(struct Map *map,int x, int y){
    for(int i = 0; i < map->corridor_count; i++){
        if(x == map->corridors[i].x_corridor && y == map->corridors[i].y_corrifer){
            return 1;
        }
    }
    return 0;
}

void move_effect(const char* state,struct Player *p,struct Map* map,int x,int y){
    if(!strcmp(state,"food")){
        p->foods[p->food_number].type = map->foods[index_food(map,x,y)].type;
        f_food(map,x,y);
        move(1,0);
        printw("You got food!");
        refresh();
        sleep(1);
        move(1,0);
        clrtoeol();
        move(0,0);
        clrtoeol();
        p->food_number += 1;
        printw("Helth: %d  Food: %d Gold: %d",p->health,p->food_number,p->gold);
        refresh();
    }
    else if(!strcmp(state,"trap")){
        move(1,0);
        printw("This was a trap!");
        refresh();
        sleep(1);
        move(1,0);
        clrtoeol();
        move(0,0);
        clrtoeol();
        p->health -= 100;
        printw("Helth: %d  Food: %d Gold: %d",p->health,p->food_number,p->gold);
        refresh();
    }
    else if(!strcmp(state,"spell")){
        p->spells[p->spell_number].type = map->spells[index_spell(map,x,y)].type;
        f_spell(map,x,y);
        move(1,0);
        printw("You got a spell!");
        refresh();
        sleep(1);
        move(1,0);
        clrtoeol();
        p->spell_number += 1;
        refresh();
    }
    else if(!strcmp(state,"wepon")){
        p->wepons[p->wepon_number].type = map->wepons[index_wepon(map,x,y)].type;
        f_wepon(map,x,y);
        move(1,0);
        printw("You got a wepon");
        refresh();
        sleep(1);
        move(1,0);
        clrtoeol();
        p->wepon_number += 1;
        refresh();
    }
    if(!strcmp(state,"gold")){
        move(1,0);
        if(map->golds[index_gold(map,x,y)].is_black){
            printw("You got black gold!");
            refresh();
        }else{
            printw("You got regular gold!");
            refresh();
        }
        sleep(1);
        move(1,0);
        clrtoeol();
        p->gold += map->golds[index_gold(map,x,y)].worth;
        f_gold(map,x,y);
        move(0,0);
        printw("Helth: %d  Food: %d Gold: %d",p->health,p->food_number,p->gold);
        refresh();
    }
    if(!strcmp(state,"master")){
        move(1,0);
        printw("You got Master Key!");
        refresh();
        sleep(1);
        move(1,0);
        clrtoeol();
        p->have_master_key = 1;
        f_master_key(map,x,y);
    }
    if(!strcmp(state,"fight")){
        move(1,0);
        printw("You will enter to fight room");
        refresh();
        sleep(2);
        move(1,0);
        clrtoeol();
        f_fight(map,x,y);
        //Fightroom
    }
}

void f_gold(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->golds[i].x_gold == x && map->golds[i].y_gold == y){
            map->golds[i].x_gold = 0;
            map->golds[i].y_gold = 0;
            break;
        }
    }
}

void f_spell(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->spells[i].x_spell == x && map->spells[i].y_spell == y){
            map->spells[i].x_spell = 0;
            map->spells[i].y_spell = 0;
            break;
        }
    }
}

void f_wepon(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->wepons[i].x_wepon == x && map->wepons[i].y_wepon == y){
            map->wepons[i].x_wepon = 0;
            map->wepons[i].y_wepon = 0;
            break;
        }
    }
}

void f_food(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->foods[i].x_food == x && map->foods[i].y_food == y){
            map->foods[i].x_food = 0;
            map->foods[i].y_food = 0;
            break;
        }
    }
}

int index_gold(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->golds[i].x_gold == x && map->golds[i].y_gold == y){
            return i;
        }
    }
}

int index_spell(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->spells[i].x_spell == x && map->spells[i].y_spell == y){
            return i;
        }
    }
}

int index_wepon(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->wepons[i].x_wepon == x && map->wepons[i].y_wepon == y){
            return i;
        }
    }
}

int index_food(struct Map *map,int x, int y){
    for(int i = 0; i < 3; i++){
        if(map->foods[i].x_food == x && map->foods[i].y_food == y){
            return i;
        }
    }
}

int is_master_key(struct Map *map,int x, int y){
    if(map->x_Master_Key == x && map->y_Master_Key == y){
        return 1;
    }
    return 0;
}

void f_master_key(struct Map *map,int x, int y){
    map->x_Master_Key = 0;
    map->y_Master_Key = 0;
    return;
}

void f_fight(struct Map *map,int x,int y){
    map->x_fight_room = 0;
    map->y_fight_room = 0;
    return;
}

int is_password_door(struct Map *map,int x, int y){
    for(int i = 0; i < map->number_of_rooms; i++){
        if(i == map->number_Password_Doors_room){
            if(x == map->rooms[i].doors[0].x_door && y == map->rooms[i].doors[0].y_door){
                return 1;
            }
        }
    }
    return 0;
}

int is_fight_room(struct Map *map,int x, int y){
     if(map->x_fight_room == x && map->y_fight_room == y){
        return 1;
    }
    return 0;
}

int is_create_password(struct Map *map,int x,int y){
    if(map->x_create_paasword == x && map->y_create_paasword == y){
        return 1;
    }
    return 0;
}


int panel(struct Player* p,struct Map *map){
    move(1,70);
    printw("make your chice:");
    move(2,70);
    printw("t.Use Mater Key  y.Enter last password  u.Exit");
    int choice;
    choice = getch();
    if(choice == 't'){
        if(p->have_master_key){
            move(1,70);
            clrtoeol();
            move(2,70);
            clrtoeol();
            p->have_master_key = 0;
            map->x_password_door = 0;
            map->y_password_door = 0;
            return 1;
        }else{
            move(3,70);
            printw("You don have master key");
            sleep(2);
            move(1,70);
            clrtoeol();
            move(2,70);
            clrtoeol();
            move(3,70);
            clrtoeol();
            return 0;
        }
    }
    if(choice == 'y'){
        move(3,70);
        printw("Enter The password");
        move(4,70);
        int password;
        nocbreak();
        echo();
        scanw("%d",&password);
        start_color();
        init_pair(1,COLOR_YELLOW,COLOR_BLACK);
        init_pair(2,COLOR_RED,COLOR_BLACK);
        for(int i = 0; i < 3;i++){
            if(map->last_password == password){
                move(1,70);
                clrtoeol();
                move(2,70);
                clrtoeol();
                move(3,70);
                clrtoeol();
                move(4,70);
                clrtoeol();
                cbreak();
                noecho();
                map->x_password_door = 0;
                map->y_password_door = 0;
                return 1;
            }else{
                if(i == 0){
                    move(4,70);
                    clrtoeol();
                    attron(COLOR_PAIR(1));
                    mvprintw(5,70,"Wrong password!");
                    attroff(COLOR_PAIR(1));
                    sleep(1);
                    move(5,70);
                    clrtoeol();
                    move(4,70);
                    scanw("%d",&password);
                }
                if(i == 1){
                    move(4,70);
                    clrtoeol();
                    attron(COLOR_PAIR(2));
                    mvprintw(5,70,"Wrong password!");
                    attroff(COLOR_PAIR(2));
                    sleep(1);
                    move(5,70);
                    clrtoeol();
                    move(4,70);
                    scanw("%d",&password);
                }
                if(i == 2){
                    move(0,70);
                    clrtoeol();
                    move(1,70);
                    clrtoeol();
                    move(3,70);
                    clrtoeol();
                    move(4,70);
                    clrtoeol();
                    cbreak();
                    noecho();
                    return 0;
                }
            }
        }
    }
    if(choice == 'u'){
        move(0,60);
        clrtoeol();
        move(1,60);
        clrtoeol();
        return 0;
    }
    move(0,60);
    clrtoeol();
    move(1,60);
    clrtoeol();
    move(3,60);
    clrtoeol();
    move(4,6);
    clrtoeol();
    return 0;
}

void create_password(struct Map *map,time_t time_start){
    int password = deciphering();
    map->last_password = password;
    move(0,60);
    printw("The password: %d",password);
    time(&time_start);
}

void regular_move(struct Player *p,struct Map *map,int second_x,int second_y,time_t time_start){
    if(is_not_wall(map,p->x + second_x,p->y + second_y) && !is_pillor(map,p->x + second_x,p->y + second_y)){
        if(is_food(map,p->x + second_x,p->y + second_y)){
            move_effect("food",p,map,p->x + second_x,p->y + second_y);
        }
        if(is_trap(map,p->x + second_x,p->y + second_y)){
            move_effect("trap",p,map,p->x + second_x,p->y + second_y);
        }
        if(is_spell(map,p->x + second_x,p->y + second_y)){
            move_effect("spell",p,map,p->x + second_x,p->y + second_y);
        }
        if(is_wepon(map,p->x + second_x,p->y + second_y)){
            move_effect("wepon",p,map,p->x + second_x,p->y + second_y);
        }
        if(is_gold(map,p->x + second_x,p->y + second_y)){
            move_effect("gold",p,map,p->x + second_x,p->y + second_y);
        }
        if(is_master_key(map,p->x + second_x,p->y + second_y)){
            move_effect("master",p,map,p->x + second_x,p->y + second_y);
        }
        if(is_fight_room(map,p->x + second_x,p->y + second_y)){
            move_effect("fight",p,map,p->x + second_x,p->y + second_y);
        }
        if(is_create_password(map,p->x + second_x,p->y + second_y)){
            create_password(map,time_start);
        }
        if(is_trap(map,p->x,p->y)){
            mvprintw(p->y,p->x,"^");
            refresh();
        }
        else{
            mvprintw(p->y,p->x," ");
            refresh();
        }
        p->y += second_y;
        p->x += second_x;
        mvprintw(p->y,p->x,"P");
        refresh();
    }if(!is_not_wall(map,p->x + second_x,p->y + second_y)){
        if(is_corridor(map,p->x + second_x,p->y + second_y)){
            mvprintw(p->y,p->x,"#");
            refresh();
            p->y += second_y;
            p->x += second_x;
            mvprintw(p->y,p->x,"P");
            refresh();
        }
        if(is_door(map,p->x + second_x,p->y + second_y)){
            if(is_password_door(map,p->x + second_x,p->y + second_y)){
                int resualt = panel(p,map);
                if(resualt){
                    mvprintw(p->y,p->x," ");
                    refresh();
                    p->y += second_y;
                    p->x += second_x;
                    mvprintw(p->y,p->x,"P");
                    refresh();
                }
            }else{
                mvprintw(p->y,p->x," ");
                refresh();
                p->y += second_y;
                p->x += second_x;
                mvprintw(p->y,p->x,"P");
                refresh();
            }
        }
    }
}

void f_move(struct Player *p,struct Map *map,int second_x,int second_y,time_t time_start){
    int x_before = p->x;
    int y_before = p->y;
    while (is_not_wall(map,p->x + second_x,p->y + second_y) && !is_pillor(map,p->x + second_x,p->y + second_y)){
        p->y += second_y;
        p->x += second_x;
    }
    mvprintw(y_before,x_before," ");
    if(is_food(map,p->x,p->y)){
        move_effect("food",p,map,p->x,p->y);
    }
    if(is_trap(map,p->x,p->y)){
        move_effect("trap",p,map,p->x,p->y);
    }
    if(is_spell(map,p->x,p->y)){
        move_effect("spell",p,map,p->x,p->y);
    }
    if(is_wepon(map,p->x,p->y)){
        move_effect("wepon",p,map,p->x,p->y);
    }
    if(is_gold(map,p->x,p->y)){
        move_effect("gold",p,map,p->x,p->y);
    }
    if(is_master_key(map,p->x,p->y)){
        move_effect("master",p,map,p->x,p->y);
    }
    if(is_fight_room(map,p->x,p->y)){
        move_effect("fight",p,map,p->x,p->y);
    }
    if(is_create_password(map,p->x,p->y)){
        create_password(map,time_start);
    }
    mvprintw(p->y,p->x,"P");
    refresh();
    while(is_corridor(map,p->x + second_x,p->y + second_y)){
    p->y += second_y;
    p->x += second_x;
    }
    if(is_corridor(map,x_before,y_before)){
    mvprintw(y_before,x_before,"#");
    refresh();
    }else if(is_door(map,x_before,y_before)){
    mvprintw(y_before,x_before," ");
    refresh();
    }
    mvprintw(p->y,p->x,"P");
    refresh();
}

void g_move(struct Player *p,struct Map *map,int second_x,int second_y,time_t time_start){
    if(is_not_wall(map,p->x + second_x,p->y + second_y) && !is_pillor(map,p->x + second_x,p->y + second_y)){
        if(is_trap(map,p->x + second_x,p->y + second_y)){
            move_effect("trap",p,map,p->x + second_x,p->y + second_y);
        }
        if(is_trap(map,p->x,p->y)){
            mvprintw(p->y,p->x,"^");
            refresh();
        }else{
            mvprintw(p->y,p->x," ");
            refresh();
        }
        p->y += second_y;
        p->x += second_x;
        mvprintw(p->y,p->x,"P");
        refresh();
    }if(!is_not_wall(map,p->x + second_x,p->y + second_y)){
        if(is_corridor(map,p->x + second_x,p->y + second_y)){
            mvprintw(p->y,p->x,"#");
            refresh();
            p->y += second_y;
            p->x += second_x;
            mvprintw(p->y,p->x,"P");
            refresh();
        }
        if(is_door(map,p->x + second_x,p->y + second_y)){
            mvprintw(p->y,p->x," ");
            refresh();
            p->y += second_y;
            p->x += second_x;
            mvprintw(p->y,p->x,"P");
            refresh();
        }
    }
}