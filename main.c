#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
int control_name(char name[20]);
int control_email(char email[20]);
int control_password(char password[20]);
void create_new_player();
int valid_name_and_password(char name[20], char password[20]);
void enter_player();
// void menu_before_game();
// void create_new_game();
// void seting_menu();
// void profile();
void table_of_players();
void menus();
// void players_menus();


int main(){
    initscr();
	while (1){
		//create_new_player();
		//enter_player();
		//before_game();
		//table_of_players();
		menus();
		getch();
		break;
	}
	endwin();
	return 0;
}


void create_new_player(){
	clear();
	refresh();
	move(0,0);
	printw("Press any key to exit");
	FILE* players = fopen("Players.txt","a");
	move(1,0);
	char name[20];
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
	getch();
	return;
}


int control_name(char name[20]) {
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


int valid_name_and_password(char name[20], char password[20]) {
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
	refresh();
	move(0,0);
	printw("Press f1 to continue or f2 to exit");
	move(1,0);
	printw("Name: ");
    char name[20];
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
	char ch = getch();
	if(ch == KEY_F(1)){
		//players_menus();
		return;
	}
	if(ch == KEY_F(2)){
		return;
	}
    //ba tavajo be bazikon bayad be file makhsose o beravim
}


void table_of_players() {
	clear();
	refresh();
	FILE* players = fopen("Players.txt", "r");
	typedef struct {
    	char name[20];
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


void players_menus(){
	const char *choices[3] = {
        "menu_before_game",
        "seting_menu",
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
				if(current_item == 0){
					//menu_before_game();
					clear();
					refresh();
				}
				if(current_item == 1){
					//seting_menu();
					clear();
					refresh();
				}
				if(current_item == 2){
					//profile();
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