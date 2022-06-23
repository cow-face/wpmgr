#include "ui.h"

#include <cstring>

#include <stdlib.h>
#include <stdio.h>

#define CTRLD 	4

void UI::setup_ui() {
    initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
}

void UI::destroy_ui() {
    endwin();
}

void UI::setup_menu(std::vector<std::string> entries) {
    // Copy entries into C-friendly data structure
    UI::entries_size = entries.size();
    UI::entries_c = (char**) calloc(UI::entries_size, sizeof(char*));
    for (int i = 0; i < UI::entries_size; i++) {
        const int cstr_size = entries[i].length() + 1;
        const char* cstr = entries[i].c_str();
        UI::entries_c[i] = (char*) malloc(cstr_size);
        std::memcpy(UI::entries_c[i], cstr, cstr_size);
    }

    // Warning: super ugly ncurses example code 
    UI::items = (ITEM**) calloc(UI::entries_size + 1, sizeof(ITEM*));

	for(int i = 0; i < UI::entries_size; i++) {
        UI::items[i] = new_item("Thread:", UI::entries_c[i]);
    }
    UI::items[UI::entries_size] = (ITEM*) NULL;
}

void UI::draw_menu() {
    UI::menu = new_menu((ITEM**) UI::items);
	
    UI::menu_window = newwin(LINES, 22, 0, 0);
    box(UI::menu_window, 0, 0);
    keypad(UI::menu_window, TRUE);
    set_menu_win(UI::menu, UI::menu_window);
    set_menu_sub(UI::menu, derwin(UI::menu_window, LINES - 1, 20, 1, 1));
    set_menu_format(UI::menu, LINES - 2, 1);
    set_menu_mark(UI::menu, "*");

    post_menu(UI::menu);
	wrefresh(UI::menu_window);

    int c;
	while((c = wgetch(UI::menu_window)) != KEY_F(1))
	{   switch(c)
	    {	case KEY_DOWN:
		        menu_driver(UI::menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(UI::menu, REQ_UP_ITEM);
				break;
            case KEY_NPAGE:
                menu_driver(UI::menu, REQ_SCR_DPAGE);
                break;
            case KEY_PPAGE:
                menu_driver(UI::menu, REQ_SCR_UPAGE);
                break;
		}
        wrefresh(UI::menu_window);
	}

}

void UI::destroy_menu() {
    // Clean up our C data structures
    for (int i = 0; i < UI::entries_size; i++) {
        free_item(UI::items[i]);
        free(UI::entries_c[i]);
    }
    free_item(UI::items[UI::entries_size]);
    free(UI::items);
    unpost_menu(UI::menu);
    free_menu(UI::menu);
    delwin(UI::menu_window);
    free(UI::entries_c);
}
