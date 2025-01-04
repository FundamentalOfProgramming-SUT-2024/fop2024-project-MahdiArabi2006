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
    int last_map;
    int x_map1;
    int x_map2;
    int x_map3;
    int x_map4;
    int y_map1;
    int y_map2;
    int y_map3;
    int y_map4;
};

struct Trap{
    int x_trap;
    int y_trap;
    int number_room;
};

struct Corridor{
    int x_corridor;
    int y_corrifer;
    int is_seen;
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
    int is_seen;
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

void generate_map(struct Map *map,char name[100],int number);
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
void move_player(struct Map *map,struct Player *p,int number_map);
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
int is_secret_door(struct Map *map,int x, int y);
void create_password(struct Map *map,time_t time_start);
int panel(struct Player* p,struct Map *map);
void regular_move(struct Player *p,struct Map *map,int second_x,int second_y,time_t time_start);
void f_move(struct Player *p,struct Map *map,int second_x,int second_y,time_t time_start);
void g_move(struct Player *p,struct Map *map,int second_x,int second_y,time_t time_start);
void save_map(char filename[100], struct Map *map,int number);
void load_map(char filename[100], struct Map *map,int number);
int is_room(struct Map *map, int x, int y);
void print_corridor(struct Map *map);
void print_room(struct Map *map);
void print(struct Map *map,int x, int y);
void make_corrider_is_seen(struct Map *map,int x, int y);
void check_corrider(struct Map *map,int x, int y);
int is_room_and_index(struct Map *map,int x,int y);
int control_name(char name[100]);
int control_email(char email[20]);
int control_password(char password[20]);
void create_new_player();
int valid_name_and_password(char name[100], char password[20]);
void enter_player();
void create_new_game(char name[100]);
void continue_last_game(char name[100]);
void seting_menu(char name[100]);
void profile(char name[100]);
void table_of_players();
void menus();
void players_menus(char name[100]);
void guest();
void save_player(char filename[100], struct Player * p);
void load_player(char filename[100], struct Player * p);
int is_stair(struct Map *map,int x,int y);

int main(){
    initscr();
    cbreak();  
    noecho();  
    srand(time(0));
	while (1){
		menus();
		getch();
		break;
	}
	endwin();
	return 0;
}

void generate_map(struct Map *map,char name[100],int number) {
    //Rooms
    map->number_of_rooms = ((unsigned int)rand() % 3) + 6; // 6-8  
    int current_room = 0;  

    while (current_room < map->number_of_rooms) {  
        if(current_room + 1 == 1){
            map->rooms[current_room].x = (unsigned int)rand() % (11 - (0 + 2) + 1) + (0 + 2);  
            map->rooms[current_room].y = (unsigned int)rand() % (10 - 2 + 1) + 2;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            map->rooms[current_room].is_seen = 0;
            if (can_have_room(map->rooms, current_room)) {  
                current_room++;

            }
        }
        else if(current_room + 1 == 2){
            map->rooms[current_room].x = (unsigned int)rand() % (25 - (16) + 1) + (16);  
            map->rooms[current_room].y = (unsigned int)rand() % (10 - 2 + 1) + 2;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            map->rooms[current_room].is_seen = 0;
            if (can_have_room(map->rooms, current_room)) {
                current_room++;  
            } 
        }
        else if(current_room + 1 == 3){
            map->rooms[current_room].x = (unsigned int)rand() % (11 - (0 + 2) + 1) + (0 + 2);
            map->rooms[current_room].y = (unsigned int)rand() % (23 - 14 + 1) + 14;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            map->rooms[current_room].is_seen = 0;
            if (can_have_room(map->rooms, current_room)) {  
                current_room++;  
            } 
        }
        else if(current_room + 1 == 4){
            map->rooms[current_room].x = (unsigned int)rand() % (25 - (16) + 1) + (16);  
            map->rooms[current_room].y = (unsigned int)rand() % (23 - 14 + 1) + 14;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            map->rooms[current_room].is_seen = 0;
            if (can_have_room(map->rooms, current_room)) {  
                current_room++;  
            } 
        }
        else if(current_room + 1 == 5){
            map->rooms[current_room].x = (unsigned int)rand() % (42 - (30) + 1) + (30);  
            map->rooms[current_room].y = (unsigned int)rand() % (10 - 2 + 1) + 2;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            map->rooms[current_room].is_seen = 0;
            if (can_have_room(map->rooms, current_room)) {  
                current_room++;

            }
        }
        else if(current_room + 1 == 6){
            map->rooms[current_room].x = (unsigned int)rand() % (60 - (47) + 1) + (47);  
            map->rooms[current_room].y = (unsigned int)rand() % (10 - 2 + 1) + 2;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            map->rooms[current_room].is_seen = 0;
            if (can_have_room(map->rooms, current_room)) {
                current_room++;  
            } 
        }
        else if(current_room + 1 == 7){
            map->rooms[current_room].x = (unsigned int)rand() % (42 - (30) + 1) + (30);  
            map->rooms[current_room].y = (unsigned int)rand() % (23 - 14 + 1) + 14;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            map->rooms[current_room].is_seen = 0;
            if (can_have_room(map->rooms, current_room)) {  
                current_room++;  
            } 
        }
        else if(current_room + 1 == 8){
            map->rooms[current_room].x = (unsigned int)rand() % (60 - (47) + 1) + (47);  
            map->rooms[current_room].y = (unsigned int)rand() % (23 - 14 + 1) + 14;
            map->rooms[current_room].size = ((unsigned int)rand() % 3) + 5;
            map->rooms[current_room].is_seen = 0;
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
    //Window
    //Corridor
    connect_doors(map);
    if(map->number_of_rooms == 6){
        map->corridors[size].x_corridor = map->rooms[0].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[0].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[0].doors[1].x_door;
        map->corridors[size].y_corrifer = map->rooms[0].doors[1].y_door + 1;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[1].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[1].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[1].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[1].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[2].doors[0].x_door;
        map->corridors[size].y_corrifer = map->rooms[2].doors[0].y_door - 1;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[2].doors[1].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[2].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[3].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[3].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[3].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[3].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[4].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[4].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[4].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[4].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[5].doors[0].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[5].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[5].doors[1].x_door;
        map->corridors[size].y_corrifer = map->rooms[5].doors[1].y_door + 1;
        map->corridors[size].is_seen = 0;
        size++;
    }
    if(map->number_of_rooms == 7){
        map->corridors[size].x_corridor = map->rooms[0].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[0].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[0].doors[1].x_door;
        map->corridors[size].y_corrifer = map->rooms[0].doors[1].y_door + 1;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[1].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[1].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[1].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[1].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[2].doors[0].x_door;
        map->corridors[size].y_corrifer = map->rooms[2].doors[0].y_door - 1;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[2].doors[1].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[2].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[3].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[3].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[3].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[3].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[4].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[4].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[4].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[4].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[5].doors[0].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[5].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[5].doors[1].x_door;
        map->corridors[size].y_corrifer = map->rooms[5].doors[1].y_door + 1;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[6].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[6].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[6].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[6].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
    }
    if(map->number_of_rooms == 8){
        map->corridors[size].x_corridor = map->rooms[0].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[0].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[0].doors[1].x_door;
        map->corridors[size].y_corrifer = map->rooms[0].doors[1].y_door + 1;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[1].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[1].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[1].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[1].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[2].doors[0].x_door;
        map->corridors[size].y_corrifer = map->rooms[2].doors[0].y_door - 1;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[2].doors[1].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[2].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[3].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[3].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[3].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[3].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[4].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[4].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[4].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[4].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[5].doors[0].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[5].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[5].doors[1].x_door;
        map->corridors[size].y_corrifer = map->rooms[5].doors[1].y_door + 1;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[6].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[6].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[6].doors[0].x_door + 1;
        map->corridors[size].y_corrifer = map->rooms[6].doors[0].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[7].doors[1].x_door - 1;
        map->corridors[size].y_corrifer = map->rooms[7].doors[1].y_door;
        map->corridors[size].is_seen = 0;
        size++;
        map->corridors[size].x_corridor = map->rooms[7].doors[0].x_door;
        map->corridors[size].y_corrifer = map->rooms[7].doors[0].y_door - 1;
        map->corridors[size].is_seen = 0;
        size++;
    }
    map->corridor_count = size;
    size = 0;
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
    //Fight_room
    map->number_room_fight_room = rand() % map->number_of_rooms;
    map->x_fight_room = 0;
    map->y_fight_room = 0;
    while(map->x_fight_room == 0 || map->y_fight_room == 0 || (map->x_fight_room == map->x_stair && map->y_fight_room == map->y_stair) || (map->x_fight_room == map->pillors[0].x_pillar && map->y_fight_room == map->pillors[0].y_pillar) || (map->x_fight_room == map->pillors[1].x_pillar && map->y_fight_room == map->pillors[1].y_pillar) || (map->x_fight_room == map->pillors[2].x_pillar && map->y_fight_room == map->pillors[2].y_pillar) || (map->x_fight_room == map->traps[0].x_trap && map->y_fight_room == map->traps[0].y_trap) || (map->x_fight_room == map->traps[1].x_trap && map->y_fight_room == map->traps[1].y_trap) || (map->x_fight_room == map->traps[2].x_trap && map->y_fight_room == map->traps[2].y_trap)){
        map->x_fight_room = rand() % ((map->rooms[map->number_room_fight_room].x + map->rooms[map->number_room_fight_room].size - 1) - (map->rooms[map->number_room_fight_room].x + 1) + 1) + ((map->rooms[map->number_room_fight_room].x + 1));
        map->y_fight_room = rand() % ((map->rooms[map->number_room_fight_room].y + map->rooms[map->number_room_fight_room].size - 1) - (map->rooms[map->number_room_fight_room].y + 1) + 1) + ((map->rooms[map->number_room_fight_room].y + 1));
    }
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
    //Master Key
    map->number_Master_Key_room = rand() % map->number_of_rooms;
    map->x_Master_Key = 0;
    map->y_Master_Key = 0;
    while(map->x_Master_Key == 0 || map->y_Master_Key == 0 || (map->x_Master_Key == map->x_stair && map->y_Master_Key == map->y_stair) || (map->x_Master_Key == map->x_create_paasword && map->y_Master_Key == map->y_create_paasword) || (map->x_Master_Key == map->x_fight_room && map->y_Master_Key == map->y_fight_room) || is_pillor(map,map->x_Master_Key,map->y_Master_Key) || is_trap(map,map->x_Master_Key,map->y_Master_Key)){
        map->x_Master_Key = rand() % ((map->rooms[map->number_Master_Key_room].x + map->rooms[map->number_Master_Key_room].size - 1) - (map->rooms[map->number_Master_Key_room].x + 1) + 1) + ((map->rooms[map->number_Master_Key_room].x + 1));
        map->y_Master_Key = rand() % ((map->rooms[map->number_Master_Key_room].y + map->rooms[map->number_Master_Key_room].size - 1) - (map->rooms[map->number_Master_Key_room].y + 1) + 1) + ((map->rooms[map->number_Master_Key_room].y + 1));
    }
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
    save_map(name,map,number);
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
            map->corridors[size].is_seen = 0;
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
            map->corridors[size].is_seen = 0;
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
            map->corridors[size].is_seen = 0;
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
            map->corridors[size].is_seen = 0;
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

void move_player(struct Map *map,struct Player *p,int number_map){
    raw(); 
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    if(number_map == 1){
        if(p->x_map1 == 0 && p->y_map1 == 0){
            int start_room = rand() % map->number_of_rooms;
            p->x = 0;
            p->y = 0;
            p->last_map = number_map;
            move(0,0);
            printw("Helth: %d  Food: %d  Gold: %d",p->health,p->food_number,p->gold);
            while(p->x == 0 || p->y == 0 || (p->x == map->x_stair && p->y == map->y_stair) || (p->x == map->x_create_paasword && p->y == map->y_create_paasword) || (p->x == map->x_fight_room && p->y == map->y_fight_room) || (p->x == map->x_Master_Key && p->y == map->y_Master_Key) || is_pillor(map,p->x,p->y) || is_trap(map,p->x,p->y) || is_food(map,p->x,p->y) || is_spell(map,p->x,p->y) || is_wepon(map,p->x,p->y) || is_gold(map,p->x,p->y)){
                p->x = rand() % ((map->rooms[start_room].x + map->rooms[start_room].size - 1) - (map->rooms[start_room].x + 1) + 1) + ((map->rooms[start_room].x + 1));
                p->y = rand() % ((map->rooms[start_room].y + map->rooms[start_room].size - 1) - (map->rooms[start_room].y + 1) + 1) + ((map->rooms[start_room].y + 1));
            }
        }else{
            p->x = p->x_map1;
            p->y = p->y_map1;
        }
    }
    else if(number_map == 2){
        if(p->x_map2 == 0 && p->y_map2 == 0){
            int start_room = rand() % map->number_of_rooms;
            p->x = 0;
            p->y = 0;
            p->last_map = number_map;
            move(0,0);
            printw("Helth: %d  Food: %d  Gold: %d",p->health,p->food_number,p->gold);
            while(p->x == 0 || p->y == 0 || (p->x == map->x_stair && p->y == map->y_stair) || (p->x == map->x_create_paasword && p->y == map->y_create_paasword) || (p->x == map->x_fight_room && p->y == map->y_fight_room) || (p->x == map->x_Master_Key && p->y == map->y_Master_Key) || is_pillor(map,p->x,p->y) || is_trap(map,p->x,p->y) || is_food(map,p->x,p->y) || is_spell(map,p->x,p->y) || is_wepon(map,p->x,p->y) || is_gold(map,p->x,p->y)){
                p->x = rand() % ((map->rooms[start_room].x + map->rooms[start_room].size - 1) - (map->rooms[start_room].x + 1) + 1) + ((map->rooms[start_room].x + 1));
                p->y = rand() % ((map->rooms[start_room].y + map->rooms[start_room].size - 1) - (map->rooms[start_room].y + 1) + 1) + ((map->rooms[start_room].y + 1));
            }
        }else{
            p->x = p->x_map2;
            p->y = p->y_map2;
        }
    }
    else if(number_map == 3){
        if(p->x_map3 == 0 && p->y_map3 == 0){
            int start_room = rand() % map->number_of_rooms;
            p->x = 0;
            p->y = 0;
            p->last_map = number_map;
            move(0,0);
            printw("Helth: %d  Food: %d  Gold: %d",p->health,p->food_number,p->gold);
            while(p->x == 0 || p->y == 0 || (p->x == map->x_stair && p->y == map->y_stair) || (p->x == map->x_create_paasword && p->y == map->y_create_paasword) || (p->x == map->x_fight_room && p->y == map->y_fight_room) || (p->x == map->x_Master_Key && p->y == map->y_Master_Key) || is_pillor(map,p->x,p->y) || is_trap(map,p->x,p->y) || is_food(map,p->x,p->y) || is_spell(map,p->x,p->y) || is_wepon(map,p->x,p->y) || is_gold(map,p->x,p->y)){
                p->x = rand() % ((map->rooms[start_room].x + map->rooms[start_room].size - 1) - (map->rooms[start_room].x + 1) + 1) + ((map->rooms[start_room].x + 1));
                p->y = rand() % ((map->rooms[start_room].y + map->rooms[start_room].size - 1) - (map->rooms[start_room].y + 1) + 1) + ((map->rooms[start_room].y + 1));
            }
        }else{
            p->x = p->x_map3;
            p->y = p->y_map3;
        }
    }
    else if(number_map == 4){
        if(p->x_map4 == 0 && p->y_map4 == 0){
            int start_room = rand() % map->number_of_rooms;
            p->x = 0;
            p->y = 0;
            p->last_map = number_map;
            move(0,0);
            printw("Helth: %d  Food: %d  Gold: %d",p->health,p->food_number,p->gold);
            while(p->x == 0 || p->y == 0 || (p->x == map->x_stair && p->y == map->y_stair) || (p->x == map->x_create_paasword && p->y == map->y_create_paasword) || (p->x == map->x_fight_room && p->y == map->y_fight_room) || (p->x == map->x_Master_Key && p->y == map->y_Master_Key) || is_pillor(map,p->x,p->y) || is_trap(map,p->x,p->y) || is_food(map,p->x,p->y) || is_spell(map,p->x,p->y) || is_wepon(map,p->x,p->y) || is_gold(map,p->x,p->y)){
                p->x = rand() % ((map->rooms[start_room].x + map->rooms[start_room].size - 1) - (map->rooms[start_room].x + 1) + 1) + ((map->rooms[start_room].x + 1));
                p->y = rand() % ((map->rooms[start_room].y + map->rooms[start_room].size - 1) - (map->rooms[start_room].y + 1) + 1) + ((map->rooms[start_room].y + 1));
            }
        }else{
            p->x = p->x_map4;
            p->y = p->y_map4;
        }
    }
    move(0,0);
    printw("Helth: %d  Food: %d  Gold: %d",p->health,p->food_number,p->gold);
    mvprintw(p->y,p->x,"P");
    refresh();
    print(map,p->x,p->y);
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
            print(map,p->x,p->y);
            mvprintw(p->y,p->x,"P");
            refresh();
        }
        if(c == 'x'){
            regular_move(p,map,0,1,time_start);
            print(map,p->x,p->y);
            mvprintw(p->y,p->x,"P");
            refresh();
        }
        if(c == 'a'){
            regular_move(p,map,-1,0,time_start);
            print(map,p->x,p->y);
            mvprintw(p->y,p->x,"P");
            refresh();
        }
        if(c == 'd'){
            regular_move(p,map,1,0,time_start);
            print(map,p->x,p->y);
            mvprintw(p->y,p->x,"P");
            refresh();
        }
        if(c == 'e'){
            regular_move(p,map,1,-1,time_start);
            print(map,p->x,p->y);
            mvprintw(p->y,p->x,"P");
            refresh();
        }
        if(c == 'q'){
            regular_move(p,map,-1,-1,time_start);
            print(map,p->x,p->y);
            mvprintw(p->y,p->x,"P");
            refresh();
        }
        if(c == 'c'){
            regular_move(p,map,1,1,time_start);
            print(map,p->x,p->y);
            mvprintw(p->y,p->x,"P");
            refresh();
        }
        if(c == 'z'){
            regular_move(p,map,-1,1,time_start);
            print(map,p->x,p->y);
            mvprintw(p->y,p->x,"P");
            refresh();
        }
        if(c == 'f'){
            int c2 = getch();
            if(c2 == 'w'){
                f_move(p,map,0,-1,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'x'){
                f_move(p,map,0,1,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'd'){
                f_move(p,map,1,0,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'a'){
                f_move(p,map,-1,0,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'e'){
                f_move(p,map,1,-1,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'q'){
                f_move(p,map,-1,-1,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'c'){
                f_move(p,map,1,1,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'z'){
                f_move(p,map,-1,1,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
        }
        if(c == 'g'){
            int c2 = getch();
            if(c2 == 'w'){
                g_move(p,map,0,-1,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'x'){
                g_move(p,map,0,1,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'a'){
                g_move(p,map,-1,0,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'd'){
                g_move(p,map,1,0,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'e'){
                g_move(p,map,1,-1,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'q'){
                g_move(p,map,-1,-1,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'c'){
                g_move(p,map,1,1,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            if(c2 == 'z'){
                g_move(p,map,-1,1,time_start);
                print(map,p->x,p->y);
                mvprintw(p->y,p->x,"P");
                refresh();
            }
        }
        if(c == 's'){
            int index_room;
            index_room = is_room_and_index(map,p->x,p->y);
            if(index_room){
                if(index_room - 1 == 0){
                    for(int i = 0; i < 3; i++){
                        if(map->traps[i].number_room == 1 || map->traps[i].number_room == 2){
                            mvprintw(map->traps[i].y_trap,map->traps[i].x_trap,"^");
                            refresh();
                        }
                    }
                    if(map->number_Spell_room == 1 || map->number_Spell_room == 2){
                        mvprintw(map->rooms[map->number_Spell_room].doors[0].y_door,map->rooms[map->number_Spell_room].doors[0].x_door,"?");
                        mvprintw(map->rooms[map->number_Spell_room].doors[1].y_door,map->rooms[map->number_Spell_room].doors[1].x_door,"?");
                        refresh();
                    }
                }
                if(index_room - 1 == 1){
                    for(int i = 0; i < 3; i++){
                        if(map->traps[i].number_room == 0 || map->traps[i].number_room == 4){
                            mvprintw(map->traps[i].y_trap,map->traps[i].x_trap,"^");
                            refresh();
                        }
                    }
                    if(map->number_Spell_room == 0 || map->number_Spell_room == 4){
                        mvprintw(map->rooms[map->number_Spell_room].doors[0].y_door,map->rooms[map->number_Spell_room].doors[0].x_door,"?");
                        mvprintw(map->rooms[map->number_Spell_room].doors[1].y_door,map->rooms[map->number_Spell_room].doors[1].x_door,"?");
                        refresh();
                    }
                }
                if(index_room - 1 == 2){
                    for(int i = 0; i < 3; i++){
                        if(map->traps[i].number_room == 0 || map->traps[i].number_room == 3){
                            mvprintw(map->traps[i].y_trap,map->traps[i].x_trap,"^");
                            refresh();
                        }
                    }
                    if(map->number_Spell_room == 0 || map->number_Spell_room == 3){
                        mvprintw(map->rooms[map->number_Spell_room].doors[0].y_door,map->rooms[map->number_Spell_room].doors[0].x_door,"?");
                        mvprintw(map->rooms[map->number_Spell_room].doors[1].y_door,map->rooms[map->number_Spell_room].doors[1].x_door,"?");
                        refresh();
                    }
                }
                if(index_room - 1 == 3){
                    if(map->number_of_rooms >= 7){
                        for(int i = 0; i < 3; i++){
                            if(map->traps[i].number_room == 2 || map->traps[i].number_room == 6){
                                mvprintw(map->traps[i].y_trap,map->traps[i].x_trap,"^");
                                refresh();
                            }
                        }
                        if(map->number_Spell_room == 2 || map->number_Spell_room == 6){
                            mvprintw(map->rooms[map->number_Spell_room].doors[0].y_door,map->rooms[map->number_Spell_room].doors[0].x_door,"?");
                            mvprintw(map->rooms[map->number_Spell_room].doors[1].y_door,map->rooms[map->number_Spell_room].doors[1].x_door,"?");
                            refresh();
                        }
                    }else{
                        for(int i = 0; i < 3; i++){
                            if(map->traps[i].number_room == 2 || map->traps[i].number_room == 5){
                                mvprintw(map->traps[i].y_trap,map->traps[i].x_trap,"^");
                                refresh();
                            }
                        }
                        if(map->number_Spell_room == 2 || map->number_Spell_room == 5){
                            mvprintw(map->rooms[map->number_Spell_room].doors[0].y_door,map->rooms[map->number_Spell_room].doors[0].x_door,"?");
                            mvprintw(map->rooms[map->number_Spell_room].doors[1].y_door,map->rooms[map->number_Spell_room].doors[1].x_door,"?");
                            refresh();
                        }
                    }
                }
                if(index_room - 1 == 4){
                    for(int i = 0; i < 3; i++){
                        if(map->traps[i].number_room == 1 || map->traps[i].number_room == 5){
                            mvprintw(map->traps[i].y_trap,map->traps[i].x_trap,"^");
                            refresh();
                        }
                    }
                    if(map->number_Spell_room == 1 || map->number_Spell_room == 5){
                        mvprintw(map->rooms[map->number_Spell_room].doors[0].y_door,map->rooms[map->number_Spell_room].doors[0].x_door,"?");
                        mvprintw(map->rooms[map->number_Spell_room].doors[1].y_door,map->rooms[map->number_Spell_room].doors[1].x_door,"?");
                        refresh();
                    }
                }
                if(index_room - 1 == 5){
                    if(map->number_of_rooms == 6){
                        for(int i = 0; i < 3; i++){
                            if(map->traps[i].number_room == 4 || map->traps[i].number_room == 3){
                                mvprintw(map->traps[i].y_trap,map->traps[i].x_trap,"^");
                                refresh();
                            }
                        }
                        if(map->number_Spell_room == 4 || map->number_Spell_room == 3){
                            mvprintw(map->rooms[map->number_Spell_room].doors[0].y_door,map->rooms[map->number_Spell_room].doors[0].x_door,"?");
                            mvprintw(map->rooms[map->number_Spell_room].doors[1].y_door,map->rooms[map->number_Spell_room].doors[1].x_door,"?");
                            refresh();
                        }
                    }
                    if(map->number_of_rooms == 7){
                        for(int i = 0; i < 3; i++){
                            if(map->traps[i].number_room == 4 || map->traps[i].number_room == 6){
                                mvprintw(map->traps[i].y_trap,map->traps[i].x_trap,"^");
                                refresh();
                            }
                        }
                        if(map->number_Spell_room == 4 || map->number_Spell_room == 6){
                            mvprintw(map->rooms[map->number_Spell_room].doors[0].y_door,map->rooms[map->number_Spell_room].doors[0].x_door,"?");
                            mvprintw(map->rooms[map->number_Spell_room].doors[1].y_door,map->rooms[map->number_Spell_room].doors[1].x_door,"?");
                            refresh();
                        }
                    }
                    if(map->number_of_rooms == 8){
                        for(int i = 0; i < 3; i++){
                            if(map->traps[i].number_room == 4 || map->traps[i].number_room == 7){
                                mvprintw(map->traps[i].y_trap,map->traps[i].x_trap,"^");
                                refresh();
                            }
                        }
                        if(map->number_Spell_room == 4 || map->number_Spell_room == 7){
                            mvprintw(map->rooms[map->number_Spell_room].doors[0].y_door,map->rooms[map->number_Spell_room].doors[0].x_door,"?");
                            mvprintw(map->rooms[map->number_Spell_room].doors[1].y_door,map->rooms[map->number_Spell_room].doors[1].x_door,"?");
                            refresh();
                        }
                    }
                }
                if(index_room - 1 == 6){
                    if(map->number_of_rooms == 7){
                        for(int i = 0; i < 3; i++){
                            if(map->traps[i].number_room == 3 || map->traps[i].number_room == 5){
                                mvprintw(map->traps[i].y_trap,map->traps[i].x_trap,"^");
                                refresh();
                            }
                        }
                        if(map->number_Spell_room == 3 || map->number_Spell_room == 5){
                            mvprintw(map->rooms[map->number_Spell_room].doors[0].y_door,map->rooms[map->number_Spell_room].doors[0].x_door,"?");
                            mvprintw(map->rooms[map->number_Spell_room].doors[1].y_door,map->rooms[map->number_Spell_room].doors[1].x_door,"?");
                            refresh();
                        }
                    }
                    if(map->number_of_rooms == 8){
                        for(int i = 0; i < 3; i++){
                            if(map->traps[i].number_room == 3 || map->traps[i].number_room == 7){
                                mvprintw(map->traps[i].y_trap,map->traps[i].x_trap,"^");
                                refresh();
                            }
                        }
                        if(map->number_Spell_room == 3 || map->number_Spell_room == 7){
                            mvprintw(map->rooms[map->number_Spell_room].doors[0].y_door,map->rooms[map->number_Spell_room].doors[0].x_door,"?");
                            mvprintw(map->rooms[map->number_Spell_room].doors[1].y_door,map->rooms[map->number_Spell_room].doors[1].x_door,"?");
                            refresh();
                        }
                    }
                }
                if(index_room - 1 == 7){
                    for(int i = 0; i < 3; i++){
                        if(map->traps[i].number_room == 5 || map->traps[i].number_room == 6){
                            mvprintw(map->traps[i].y_trap,map->traps[i].x_trap,"^");
                            refresh();
                        }
                    }
                    if(map->number_Spell_room == 5 || map->number_Spell_room == 6){
                        mvprintw(map->rooms[map->number_Spell_room].doors[0].y_door,map->rooms[map->number_Spell_room].doors[0].x_door,"?");
                        mvprintw(map->rooms[map->number_Spell_room].doors[1].y_door,map->rooms[map->number_Spell_room].doors[1].x_door,"?");
                        refresh();
                    }
                }
            }
        }
        if(c == KEY_RIGHT){
            if(is_stair(map,p->x,p->y)){
                if(p->last_map == 1){
                    clear();
                    p->last_map = 2;
                    p->x_map1 = p->x;
                    p->y_map1 = p->y;
                    move_player(&game.maps[1],p,2);
                    return;
                }
                if(p->last_map == 2){
                    clear();
                    p->last_map = 3;
                    p->x_map2 = p->x;
                    p->y_map2 = p->y;
                    move_player(&game.maps[2],p,3);
                    return;
                }
                if(p->last_map == 3){
                    clear();
                    p->last_map = 4;
                    p->x_map3 = p->x;
                    p->y_map3 = p->y;
                    move_player(&game.maps[3],p,4);
                    return;
                }
            }
        }
        if(c == KEY_LEFT){
            if(is_stair(map,p->x,p->y)){
                if(p->last_map == 2){
                    clear();
                    p->last_map = 1;
                    p->x_map2 = p->x;
                    p->y_map2 = p->y;
                    move_player(&game.maps[0],p,1);
                    return;
                }
                if(p->last_map == 3){
                    clear();
                    p->last_map = 2;
                    p->x_map3 = p->x;
                    p->y_map3 = p->y;
                    move_player(&game.maps[1],p,2);
                    return;
                }
                if(p->last_map == 4){
                    clear();
                    p->last_map = 3;
                    p->x_map4 = p->x;
                    p->y_map4 = p->y;
                    move_player(&game.maps[2],p,3);
                    return;
                }
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

int panel(struct Player* p, struct Map *map) {
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    move(1, 70);
    printw("make your chice:");
    move(2, 70);
    printw("t.Use Mater Key  y.Enter last password  u.Exit");
    int choice;
    choice = getch();
    if (choice == 't') {
        if (p->have_master_key) {
            move(1, 70);
            clrtoeol();
            move(2, 70);
            clrtoeol();
            p->have_master_key = 0;
            map->x_password_door = 0;
            map->y_password_door = 0;
            return 1;
        } else {
            move(3, 70);
            printw("You don't have master key");
            sleep(2);
            move(1, 70);
            clrtoeol();
            move(2, 70);
            clrtoeol();
            move(3, 70);
            clrtoeol();
            return 0;
        }
    }

    if (choice == 'y') {
        move(3, 70);
        printw("Enter The password");

        move(4, 70);
        int password;
        nocbreak();
        echo();
        scanw("%d", &password);

        for (int i = 0; i < 3; i++) {
            if (map->last_password == password) {
                move(1, 70);
                clrtoeol();
                move(2, 70);
                clrtoeol();
                move(3, 70);
                clrtoeol();
                move(4, 70);
                clrtoeol();
                cbreak();
                noecho();
                map->x_password_door = 0;
                map->y_password_door = 0;
                return 1;
            } else {
                if (i == 0) {
                    move(4, 70);
                    clrtoeol();
                    attron(COLOR_PAIR(1));  // Set color pair to yellow
                    mvprintw(5, 70, "Wrong password!");
                    attroff(COLOR_PAIR(1)); // Turn off yellow color
                    sleep(1);
                    move(5, 70);
                    clrtoeol();
                    move(4, 70);
                    scanw("%d", &password);
                }
                if (i == 1) {
                    move(4, 70);
                    clrtoeol();
                    attron(COLOR_PAIR(2));  // Set color pair to red
                    mvprintw(5, 70, "Wrong password!");
                    attroff(COLOR_PAIR(2)); // Turn off red color
                    sleep(1);
                    move(5, 70);
                    clrtoeol();
                    move(4, 70);
                    scanw("%d", &password);
                }
                if (i == 2) {
                    move(0, 70);
                    clrtoeol();
                    move(1, 70);
                    clrtoeol();
                    move(3, 70);
                    clrtoeol();
                    move(4, 70);
                    clrtoeol();
                    cbreak();
                    noecho();
                    return 0;
                }
            }
        }
    }

    if (choice == 'u') {
        move(1, 70);
        clrtoeol();
        move(2, 70);
        clrtoeol();
        return 0;
    }

    move(1, 70);
    clrtoeol();
    move(2, 70);
    clrtoeol();
    move(3, 70);
    clrtoeol();
    move(4, 70);
    clrtoeol();
    move(5, 70);
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
        if(is_create_password(map,p->x + second_x,p->y + second_y) && (map->x_password_door != 0 && map->y_password_door != 0)){
            create_password(map,time_start);
        }
        if(is_trap(map,p->x,p->y)){
            mvprintw(p->y,p->x,"^");
            refresh();
        }
        else if(is_stair(map,p->x,p->y)){
            mvprintw(p->y,p->x,"<");
            refresh();
        }
        else if(is_door(map,p->x,p->y) && !is_password_door(map,p->x,p->y) && !is_secret_door(map,p->x,p->y)){
            mvprintw(p->y,p->x,"+");
            refresh();
        }
        else if(is_secret_door(map,p->x,p->y)){
            mvprintw(p->y,p->x,"?");
            refresh();
        }
        else if(is_password_door(map,p->x,p->y)){
            if(map->x_password_door == 0 && map->y_password_door == 0){
                start_color();
                init_pair(1,COLOR_GREEN,COLOR_WHITE);
                attron(COLOR_PAIR(1));
                mvprintw(p->y,p->x,"@");
                attroff(COLOR_PAIR(1));
                refresh();
            }else{
                start_color();
                init_pair(1,COLOR_RED,COLOR_WHITE);
                attron(COLOR_PAIR(1));
                mvprintw(p->y,p->x,"@");
                attroff(COLOR_PAIR(1));
                refresh();
            }
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
            if(is_corridor(map,p->x,p->y)){
                mvprintw(p->y,p->x,"#");
                refresh();
                p->y += second_y;
                p->x += second_x;
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            else if(is_door(map,p->x,p->y) && !is_password_door(map,p->x,p->y) && !is_secret_door(map,p->x,p->y)){
                mvprintw(p->y,p->x,"+");
                refresh();
                p->y += second_y;
                p->x += second_x;
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            else if(is_secret_door(map,p->x,p->y)){
                mvprintw(p->y,p->x,"?");
                refresh();
                p->y += second_y;
                p->x += second_x;
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            else if(is_password_door(map,p->x,p->y)){
                if(map->x_password_door == 0 && map->y_password_door == 0){
                    start_color();
                    init_pair(1,COLOR_GREEN,COLOR_WHITE);
                    attron(COLOR_PAIR(1));
                    mvprintw(p->y,p->x,"@");
                    attroff(COLOR_PAIR(1));
                    refresh();
                    p->y += second_y;
                    p->x += second_x;
                    mvprintw(p->y,p->x,"P");
                    refresh();
                }else{
                    start_color();
                    init_pair(1,COLOR_RED,COLOR_WHITE);
                    attron(COLOR_PAIR(1));
                    mvprintw(p->y,p->x,"@");
                    attroff(COLOR_PAIR(1));
                    refresh();
                    p->y += second_y;
                    p->x += second_x;
                    mvprintw(p->y,p->x,"P");
                    refresh();
                }
            }
        }
        if(is_door(map,p->x + second_x,p->y + second_y)){
            if(is_password_door(map,p->x + second_x,p->y + second_y) && (map->x_create_paasword != 0 && map->y_password_door != 0)){
                int resualt = panel(p,map);
                if(resualt){
                    if(is_corridor(map,p->x,p->y)){
                        mvprintw(p->y,p->x,"#");
                        refresh();
                        p->y += second_y;
                        p->x += second_x;
                        mvprintw(p->y,p->x,"P");
                        refresh();
                    }else{
                        start_color();
                        init_pair(1,COLOR_GREEN,COLOR_WHITE);
                        attron(COLOR_PAIR(1));
                        mvprintw(p->y,p->x,"@");
                        attroff(COLOR_PAIR(1));
                        refresh();
                        p->y += second_y;
                        p->x += second_x;
                        mvprintw(p->y,p->x,"P");
                        refresh();
                    }
                }
            }
            if(is_corridor(map,p->x,p->y)){
                mvprintw(p->y,p->x,"#");
                refresh();
                p->y += second_y;
                p->x += second_x;
                mvprintw(p->y,p->x,"P");
                refresh();
            }
            else{
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
    }
    else if(is_door(map,x_before,y_before) && !is_password_door(map,x_before,y_before) && !is_secret_door(map,x_before,y_before)){
        mvprintw(y_before,x_before,"+");
        refresh();
    }
    else if(is_secret_door(map,x_before,y_before)){
        mvprintw(y_before,x_before,"?");
        refresh();
    }
    else if(is_password_door(map,x_before,y_before)){
        if(map->x_password_door == 0 && map->y_password_door == 0){
            start_color();
            init_pair(1,COLOR_GREEN,COLOR_WHITE);
            attron(COLOR_PAIR(1));
            mvprintw(y_before,x_before,"@");
            attroff(COLOR_PAIR(1));
            refresh();
        }else{
            start_color();
            init_pair(1,COLOR_RED,COLOR_WHITE);
            attron(COLOR_PAIR(1));
            mvprintw(y_before,x_before,"@");
            attroff(COLOR_PAIR(1));
            refresh();
        }
    }else{

    }
    mvprintw(p->y,p->x,"P");
    refresh();
}

void g_move(struct Player *p,struct Map *map,int second_x,int second_y,time_t time_start){
    if(is_not_wall(map,p->x + second_x,p->y + second_y) && !is_pillor(map,p->x + second_x,p->y + second_y)){
        if(is_trap(map,p->x + second_x,p->y + second_y)){
            move_effect("trap",p,map,p->x + second_x,p->y + second_y);
        }
        if(is_fight_room(map,p->x + second_x,p->y + second_y)){
            move_effect("fight",p,map,p->x,p->y);
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
            mvprintw(p->y,p->x," ");
            refresh();
            p->y += second_y;
            p->x += second_x;
            mvprintw(p->y,p->x,"P");
            refresh();
        }
    }
}

int is_secret_door(struct Map *map,int x, int y){
    for(int i = 0; i < map->number_of_rooms; i++){
        if(map->rooms[i].doors[0].is_secret_door){
            if((map->rooms[i].doors[0].x_door == x && map->rooms[i].doors[0].y_door == y) || (map->rooms[i].doors[1].x_door == x && map->rooms[i].doors[1].y_door == y)){
                return 1;
            }
        }
    }
    return 0;
}

void save_map(char filename[100], struct Map *map,int number) {
    char perfix[20];
    switch (number)
    {
    case 1:
        strcpy(perfix, "-map1.bin");
        break;
    case 2:
        strcpy(perfix, "-map2.bin");
        break;
    case 3:
        strcpy(perfix, "-map3.bin");
        break;
    case 4:
        strcpy(perfix, "-map4.bin");
        break;
    }
    strcat(filename,perfix);   
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Unable to open file");
        return;
    }
    fwrite(map, sizeof(struct Map), 1, file);
    fclose(file);
}

void load_map(char filename[100], struct Map *map,int number) {
    char perfix[20];
    switch (number)
    {
    case 1:
        strcpy(perfix, "-map1.bin");
        break;
    case 2:
        strcpy(perfix, "-map2.bin");
        break;
    case 3:
        strcpy(perfix, "-map3.bin");
        break;
    case 4:
        strcpy(perfix, "-map4.bin");
        break;
    }
    strcat(filename,perfix);   
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Unable to open file");
        return;
    }
    fread(map, sizeof(struct Map), 1, file);
    fclose(file);
}

int is_room(struct Map *map, int x, int y) {
    for(int i = 0; i < map->number_of_rooms; i++) {
        int room_x1 = map->rooms[i].x;
        int room_x2 = map->rooms[i].x + map->rooms[i].size;
        int room_y1 = map->rooms[i].y;
        int room_y2 = map->rooms[i].y + map->rooms[i].size;

        if(x >= room_x1 && x <= room_x2 && y >= room_y1 && y <= room_y2) {
            map->rooms[i].is_seen = 1;
            return 1;
        }
    }
    return 0;
}

void print_corridor(struct Map *map){
    for(int i = 0; i < map->corridor_count; i++){
        if(map->corridors[i].is_seen){
            mvprintw(map->corridors[i].y_corrifer,map->corridors[i].x_corridor,"#");
            refresh();
        }
    }
}

void print_room(struct Map *map){
    for(int i = 0; i < map->number_of_rooms; i++){
        if(map->rooms[i].is_seen){
            int x_1 = map->rooms[i].x;  
            int x_2 = map->rooms[i].x + map->rooms[i].size;  
            int y_1 = map->rooms[i].y;  
            int y_3 = map->rooms[i].y + map->rooms[i].size;  
            for (int j = 0; j <= map->rooms[i].size; j++) {  
                move(y_1, x_1 + j);
                printw("_");  
                move(y_3, x_1 + j);  
                printw("_");  
            }  
            for (int j = 0; j < map->rooms[i].size; j++){  
                move(y_1 + j + 1, x_1);  
                printw("|");
                move(y_1 + j + 1, x_2);  
                printw("|");  
            }
            for(int j = 0; j < 2; j++){
                mvprintw(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door,"+");
                mvprintw(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door,"+");
            }
            if(i == map->number_Password_Doors_room){
                if(map->x_password_door == 0 && map->y_password_door == 0){
                    start_color();
                    init_pair(1,COLOR_GREEN,COLOR_WHITE);
                    attron(COLOR_PAIR(1));
                    mvprintw(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door,"@");
                    attroff(COLOR_PAIR(1));
                    mvprintw(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door,"+");
                    refresh();
                }else{
                    start_color();
                    init_pair(1,COLOR_RED,COLOR_WHITE);
                    attron(COLOR_PAIR(1));
                    mvprintw(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door,"@");
                    attroff(COLOR_PAIR(1));
                    mvprintw(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door,"+");
                    refresh();
                }
            }
            if(i == map->number_Spell_room){
                if(i == 0){
                    move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                    printw("|");
                    move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                    printw("_");
                }
                if(i == 1){
                    move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                    printw("|");
                    move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                    printw("|");
                }
                if(i == 2){
                    move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                    printw("_");
                    move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                    printw("|");
                }
                if(i == 3){
                    move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                    printw("|");
                    move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                    printw("|");
                }
                if(i == 4){
                    move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                    printw("|");
                    move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                    printw("|");
                }
                if(i == 5){
                    move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                    printw("|");
                    move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                    printw("_");
                }
                if(i == 6){
                    move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                    printw("|");
                    move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                    printw("|");
                }
                if(i == 7){
                    move(map->rooms[i].doors[0].y_door,map->rooms[i].doors[0].x_door);
                    printw("_");
                    move(map->rooms[i].doors[1].y_door,map->rooms[i].doors[1].x_door);
                    printw("|");
                }
            }
            for(int j = 0; j < 3; j++){
                if(map->foods[j].number_room == i){
                    mvprintw(map->foods[j].y_food,map->foods[j].x_food,"f");
                }
            }
            for(int j = 0; j < 3; j++){
                if(map->spells[j].number_room == i){
                    mvprintw(map->spells[j].y_spell,map->spells[j].x_spell,"S");
                }
            }
            for(int j = 0; j < 3; j++){
                if(map->wepons[j].number_room == i){
                    mvprintw(map->wepons[j].y_wepon,map->wepons[j].x_wepon,"W");
                }
            }
            for(int j = 0; j < 3; j++){
                if(map->golds[j].number_room == i){
                    mvprintw(map->golds[j].y_gold,map->golds[j].x_gold,"G");
                }
            }
            for(int j = 0; j < 3; j++){
                if(map->pillors[j].number_room == i){
                    mvprintw(map->pillors[j].y_pillar,map->pillors[j].x_pillar,"O");
                }
            }
            if(map->number_room_stair == i){
                mvprintw(map->y_stair,map->x_stair,"<");
            }
            if(map->number_Password_Doors_room == i){
                mvprintw(map->y_create_paasword,map->x_create_paasword,"&");
            }
            if(map->number_Master_Key_room == i){
                mvprintw(map->y_Master_Key,map->x_Master_Key,"K");
            }
        }
    }
}

void make_corrider_is_seen(struct Map *map,int x, int y){
    for(int i = 0; i < map->corridor_count; i++){
        if(map->corridors[i].x_corridor == x && map->corridors[i].y_corrifer == y){
            map->corridors[i].is_seen = 1;
        }
    }
}

void check_corrider(struct Map *map,int x, int y){
    if(is_corridor(map,x + 1,y)){
        make_corrider_is_seen(map,x + 1,y);        
    }
    if(is_corridor(map,x + 2,y)){
        make_corrider_is_seen(map,x + 2,y);        
    }
    if(is_corridor(map,x + 3,y)){
        make_corrider_is_seen(map,x + 3,y);        
    }
    if(is_corridor(map,x + 4,y)){
        make_corrider_is_seen(map,x + 4,y);        
    }
    if(is_corridor(map,x + 5,y)){
        make_corrider_is_seen(map,x + 5,y);        
    }
    if(is_corridor(map,x - 1,y)){
        make_corrider_is_seen(map,x - 1,y);        
    }
    if(is_corridor(map,x - 2,y)){
        make_corrider_is_seen(map,x - 2,y);        
    }
    if(is_corridor(map,x - 3,y)){
        make_corrider_is_seen(map,x - 3,y);        
    }
    if(is_corridor(map,x - 4,y)){
        make_corrider_is_seen(map,x - 4,y);        
    }
    if(is_corridor(map,x - 5,y)){
        make_corrider_is_seen(map,x - 5,y);        
    }
    if(is_corridor(map,x,y + 1)){
        make_corrider_is_seen(map,x,y + 1);        
    }
    if(is_corridor(map,x,y + 2)){
        make_corrider_is_seen(map,x,y + 2);        
    }
    if(is_corridor(map,x,y + 3)){
        make_corrider_is_seen(map,x,y + 3);        
    }
    if(is_corridor(map,x,y + 4)){
        make_corrider_is_seen(map,x,y + 4);        
    }
    if(is_corridor(map,x,y + 5)){
        make_corrider_is_seen(map,x,y + 5);        
    }
    if(is_corridor(map,x,y - 1)){
        make_corrider_is_seen(map,x,y - 1);        
    }
    if(is_corridor(map,x,y - 2)){
        make_corrider_is_seen(map,x,y - 2);        
    }
    if(is_corridor(map,x,y - 3)){
        make_corrider_is_seen(map,x,y - 3);        
    }
    if(is_corridor(map,x,y - 4)){
        make_corrider_is_seen(map,x,y - 4);        
    }
    if(is_corridor(map,x,y - 5)){
        make_corrider_is_seen(map,x,y - 5);        
    }
}

void print(struct Map *map,int x, int y){
    if(is_room(map,x,y)){
        print_room(map);
    }
    else{
        check_corrider(map,x,y);
        print_corridor(map);        
    }
}

int is_room_and_index(struct Map *map,int x,int y){
    for(int i = 0; i < map->number_of_rooms; i++){
        int room_x1 = map->rooms[i].x;
        int room_x2 = map->rooms[i].x + map->rooms[i].size;
        int room_y1 = map->rooms[i].y;
        int room_y2 = map->rooms[i].y + map->rooms[i].size;

        if(x >= room_x1 && x <= room_x2 && y >= room_y1 && y <= room_y2) {
            return i + 1;
        }
    }
    return 0;
}

void create_new_player(){
	clear();
	refresh();
	move(0,0);
	printw("Press any key to exit");
	FILE* players = fopen("Players.txt","a");
	move(1,0);
	char name[100];
	printw("Name: ");
	move(1,7);
	scanw("%s",name);
	while(!control_name(name)){
		move(1,0);
		clrtoeol();
		printw("Name: ");
		move(1,7);
		scanw("%s",name);
	}
	move(2,0);
	char password[20];
	printw("password: ");
	move(2,11);
	scanw("%s",password);
	while(!control_password(password)){
	 	move(2,0);
		clrtoeol();
		printw("password: ");
		move(2,11);
		scanw("%s",password);
	}
	char email[20];
	move(3,0);
	printw("email: ");
	move(3,8);
	scanw("%s",email);
	while(!control_email(email)){
		move(3,0);
		clrtoeol();
		printw("email: ");
		move(3,8);
		scanw("%s",email);
	}
	int score = 0;
	int gold = 0;
	int number_of_game = 0;
	int time = 0;
	fprintf(players,"%s %s %s %d %d %d %d\n",name,password,email,score,gold,number_of_game,time);
	fclose(players);
	getch();
	return;
}

int control_name(char name[100]) {
	FILE* ptr = fopen("Players.txt", "r");
	char name_existed[20];
	while(fscanf(ptr, "%s", name_existed) != EOF) {
		if (strcmp(name, name_existed) == 0) {
			mvprintw(10, 10, "This Username is already exist, please try another name");
			if(getch()){
				move(10,10);
				clrtoeol();
			}
			fclose(ptr);
			return 0;
		}
	}
	fclose(ptr); 
	return 1; 
}

int control_password(char password[20]){
	int len_password = strlen(password);
	int control1 = 0;
	int control2 = 0;
	if(len_password < 7){
		mvprintw(10, 10, "This password is too short!");
		if(getch()){
			move(10,10);
			clrtoeol();
		}
		return 0;
	}
	for(int i = 0; i < len_password; i++){
		if(password[i] >= 'a' && password[i] <= 'z'){
			control1 = 1;
			break;
		}
	}
	for(int i = 0; i < len_password; i++){
		if(password[i] >= 'A' && password[i] <= 'Z'){
			control2 = 1;
			break;
		}
	}
	if(control1 && control2){
		return 1;
	}
	mvprintw(10, 10, "You have to use atleast one lower or upper charector!");
	if(getch()){
		move(10,10);
		clrtoeol();
	}
	return 0;
}

int control_email(char email[20]) {
    int pointer = 0;
    while (email[pointer] != '@') {
        if (email[pointer] == '.' || email[pointer] == '\0') {
            mvprintw(10, 10, "Not valid!");
    		if (getch()) {
        		move(10, 10);
        		clrtoeol();
    		}
            return 0;
        }
        pointer++;
    }
    if (pointer == 0 || pointer == strlen(email) - 1) {
        mvprintw(10, 10, "Not valid!");
    	if (getch()) {
        	move(10, 10);
    		clrtoeol();
		}
        return 0;
    }    
    int point_at = pointer;
    pointer++;
    while (email[pointer] != '.') {
        if (email[pointer] == '@' || email[pointer] == '\0') {
            mvprintw(10, 10, "Not valid!");
    		if (getch()) {
        		move(10, 10);
        		clrtoeol();
    		}
            return 0;
        }
        pointer++;
    }
    if (pointer == point_at + 1 || pointer == strlen(email) - 1) {
        mvprintw(10, 10, "Not valid!");
    	if (getch()) {
    		move(10, 10);
    		clrtoeol();
		}
        return 0;
    }    
    int point_dot = pointer;
    pointer++;
    while (email[pointer] != '\0') {
        pointer++;
    }    
    if (pointer == point_dot + 1) {
        mvprintw(10, 10, "Not valid!");
    	if (getch()) {
    		move(10, 10);
    		clrtoeol();
		}
        return 0;
    }
    return 1;
}

int valid_name_and_password(char name[100], char password[20]) {
    FILE* players = fopen("Players.txt", "r");
    char name_existed[20];
    char password_existed[20];
    while (fscanf(players, "%s %s", name_existed, password_existed) != EOF) {
        if (strcmp(name, name_existed) == 0 && strcmp(password, password_existed) == 0) {
            fclose(players);
            return 1;
        }
    }
    mvprintw(10, 10, "%s", "Invalid name or password");
    if (getch()) {
        move(10, 10);
        clrtoeol();
    }
	fclose(players);
    return 0;
}

void enter_player() {
    clear();
	label:
    const char *choices[3] = {
        "sign in",
        "Guest",
        "back"
    };
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_YELLOW, COLOR_BLUE);
    WINDOW *menu = newwin(5,40,4,4);
    keypad(menu, TRUE);
    int current_item = 0;
    int ch;
    while (1) {
        for (int i = 0; i < 3; i++) {
            if (i == current_item) {
                wattron(menu, A_BOLD | COLOR_PAIR(2));
                mvwprintw(menu, i + 1, 1, "%s", choices[i]);
                wattroff(menu, A_BOLD | COLOR_PAIR(2));
            } else {
                wattron(menu, COLOR_PAIR(1));
                mvwprintw(menu, i + 1, 1, "%s", choices[i]);
                wattroff(menu, COLOR_PAIR(1));
            }
        }
        wrefresh(menu);
        ch = wgetch(menu);
        switch (ch) {
            case KEY_UP:
				if(current_item == 0){
					current_item = 3 - 1;
				}else{
					current_item -= 1;
				}
                break;
            case KEY_DOWN:
				if(current_item == 0 || current_item == 1){
					current_item += 1;
				}else{
					current_item = 0;
				}
                break;
            case 10:
                refresh();
				clear();
				nocbreak();
    			echo();
    			curs_set(1);
				if(current_item == 0){
					refresh();
					clear();
					move(1,0);
					printw("Name: ");
					char name[100];
					move(1,7);
					scanw("%s", name);
					move(2,0);
					printw("Password: ");
					char password[20];
					move(2,11);
					scanw("%s", password);
					while (!valid_name_and_password(name, password)) {
						move(1, 0);
						clrtoeol();
						printw("Name: ");
						move(1,7);
						scanw("%s", name);
						move(2, 0);
						clrtoeol();
						printw("Password: ");
						move(2,11);
						scanw("%s", password);
					}
					getch();
					players_menus(name);
					clear();
					refresh();
					goto label;
				}
				if(current_item == 1){
					guest();
					clear();
					refresh();
					goto label;
				}
				if(current_item == 2){
                	return;
				}
                break;
        }
    }
}

void table_of_players() {
	clear();
	refresh();
	FILE* players = fopen("Players.txt", "r");
	typedef struct {
    	char name[100];
    	char password[20];
    	char email[20];
    	int score;
    	int gold;
    	int number_of_game;
    	int time;
    	int rank;
	} user;
    user* users = (user*)malloc(20 * sizeof(user));
    int size_users = 0;
    while (fscanf(players, "%s %s %s %d %d %d %d",
                  users[size_users].name,
                  users[size_users].password,
                  users[size_users].email,
                  &users[size_users].score,
                  &users[size_users].gold,
                  &users[size_users].number_of_game,
                  &users[size_users].time) != EOF) {
        users[size_users].rank = size_users + 1;
        size_users++;
    }
    fclose(players);
    for (int i = 0; i < size_users - 1; i++) {
        for (int j = 0; j < size_users - i - 1; j++) {
            if (users[j].score < users[j + 1].score) {
                user temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
				int temp2 = users[j].rank;
                users[j].rank = users[j + 1].rank;
                users[j + 1].rank = temp2;
            }
        }
    }
	start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
	move(0,0);
	printw("Press any key to back");
    move(4, 14);
    printw("-------------------------------------------------------------");
    move(5, 14);
    printw("| Rank |         Name         | Score | Gold | Games | Time |");
    for (int i = 0; i < size_users; i++) {
        move(6 + i, 14);
        if (i == 0) {
            attron(A_REVERSE | COLOR_PAIR(1));
			move(6 + i,4);
			printw("(Goat)");
			move(6 + i, 14);
            printw("|%-6d|%-22s|%-7d|%-6d|%-7d|%-6d|", users[i].rank, users[i].name, users[i].score, users[i].gold, users[i].number_of_game, users[i].time);
            attroff(A_REVERSE | COLOR_PAIR(1));
        } else if (i == 1) {
            attron(A_BOLD | COLOR_PAIR(2));
			move(6 + i,4);
			printw("(Legend)");
			move(6 + i,14);
            printw("|%-6d|%-22s|%-7d|%-6d|%-7d|%-6d|", users[i].rank, users[i].name, users[i].score, users[i].gold, users[i].number_of_game, users[i].time);
            attroff(A_BOLD | COLOR_PAIR(2));
        } else if (i == 2) {
            attron(A_DIM | COLOR_PAIR(3));
			move(6 + i,4);
			printw("(Good)");
			move(6 + i,14);
            printw("|%-6d|%-22s|%-7d|%-6d|%-7d|%-6d|", users[i].rank, users[i].name, users[i].score, users[i].gold, users[i].number_of_game, users[i].time);
            attroff(A_DIM | COLOR_PAIR(3));
        } else {
            printw("|%-6d|%-22s|%-7d|%-6d|%-7d|%-6d|", users[i].rank, users[i].name, users[i].score, users[i].gold, users[i].number_of_game, users[i].time);
        }
    }
	move(6 + size_users,14);
	printw("-------------------------------------------------------------");
    free(users);
	getch();
	return;
}

void menus(){
	clear();
	label:
    const char *choices[3] = {
        "create new player",
        "Enter player",
        "table of players"
    };
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_YELLOW, COLOR_BLUE);
    WINDOW *menu = newwin(5,40,4,4);
    keypad(menu, TRUE);
    int current_item = 0;
    int ch;
    while (1) {
        for (int i = 0; i < 3; i++) {
            if (i == current_item) {
                wattron(menu, A_BOLD | COLOR_PAIR(2));
                mvwprintw(menu, i + 1, 1, "%s", choices[i]);
                wattroff(menu, A_BOLD | COLOR_PAIR(2));
            } else {
                wattron(menu, COLOR_PAIR(1));
                mvwprintw(menu, i + 1, 1, "%s", choices[i]);
                wattroff(menu, COLOR_PAIR(1));
            }
        }
        wrefresh(menu);
        ch = wgetch(menu);
        switch (ch) {
            case KEY_UP:
				if(current_item == 0){
					current_item = 3 - 1;
				}else{
					current_item -= 1;
				}
                break;
            case KEY_DOWN:
				if(current_item == 0 || current_item == 1){
					current_item += 1;
				}else{
					current_item = 0;
				}
                break;
            case 10:
                refresh();
				clear();
				nocbreak();
    			echo();
    			curs_set(1);
				if(current_item == 0){
					create_new_player();
					clear();
					refresh();
					goto label;
				}
				if(current_item == 1){
					enter_player();
					clear();
					refresh();
					goto label;
				}
				if(current_item == 2){
					table_of_players();
					clear();
					refresh();
					goto label;
				}
                break;
            case KEY_F(2):
                endwin();
                return;
        }
    }
}

void players_menus(char name[100]){
	const char *choices[4] = {
        "create new game",
		"continue last game",
        "seting menu",
        "profile"
    };
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_YELLOW, COLOR_BLUE);
    WINDOW *menu = newwin(5,40,4,4);
    keypad(menu, TRUE);
    int current_item = 0;
    int ch;
    while (1) {
        for (int i = 0; i < 4; i++) {
            if (i == current_item) {
                wattron(menu, A_BOLD | COLOR_PAIR(2));
                mvwprintw(menu, i + 1, 1, "%s", choices[i]);
                wattroff(menu, A_BOLD | COLOR_PAIR(2));
            } else {
                wattron(menu, COLOR_PAIR(1));
                mvwprintw(menu, i + 1, 1, "%s", choices[i]);
                wattroff(menu, COLOR_PAIR(1));
            }
        }
        wrefresh(menu);
        ch = wgetch(menu);
        switch (ch) {
            case KEY_UP:
				if(current_item == 0){
					current_item = 4 - 1;
				}else{
					current_item -= 1;
				}
                break;
            case KEY_DOWN:
				if(current_item == 0 || current_item == 1 || current_item == 2){
					current_item += 1;
				}else{
					current_item = 0;
				}
                break;
            case 10:
                refresh();
				clear();
				if(current_item == 0){
					create_new_game(name);
					clear();
					refresh();
				}
				if(current_item == 1){
					continue_last_game(name);
					clear();
					refresh();
				}
				if(current_item == 2){
					seting_menu(name);
					clear();
					refresh();
				}
				if(current_item == 3){
					profile(name);
					clear();
					refresh();
				}
                break;
            case KEY_F(2):
                endwin();
                return;
        }
    }	
}

void create_new_game(char name[100]){}

void continue_last_game(char name[100]){}

void seting_menu(char name[100]){}

void profile(char name[100]){}

void guest(){
    char name1[100] = "guest"; 
    char name2[100] = "guest"; 
    char name3[100] = "guest"; 
    char name4[100] = "guest"; 
    generate_map(&game.maps[0],name1,1);
    generate_map(&game.maps[1],name2,2);
    generate_map(&game.maps[2],name3,3);
    generate_map(&game.maps[3],name4,4);
    struct Player guest_player;
    guest_player.health = 1000;
    guest_player.food_number = 0;
    guest_player.gold = 0;
    guest_player.have_master_key = 0;
    guest_player.spell_number = 0;
    guest_player.wepon_number = 0;
    guest_player.x_map1 = 0;
    guest_player.x_map2 = 0;
    guest_player.x_map3 = 0;
    guest_player.x_map4 = 0;
    guest_player.y_map1 = 0;
    guest_player.y_map2 = 0;
    guest_player.y_map3 = 0;
    guest_player.y_map4 = 0;
    move_player(&game.maps[0],&guest_player,1);
}

void save_player(char filename[100], struct Player * p){}

void load_player(char filename[100], struct Player * p){}

int is_stair(struct Map *map,int x,int y){
    if(x == map->x_stair && y == map->y_stair){
        return 1;
    }
    return 0;
}