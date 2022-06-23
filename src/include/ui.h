#ifndef UI_H
#define UI_H

#include <curses.h>
#include <menu.h>

#include <vector>
#include <string>

class UI {
private:
    static inline ITEM** items;
    static inline MENU* menu;
    static inline char** entries_c;
    static inline int entries_size;
    static inline WINDOW* menu_window;
public:
    static void setup_ui();
    static void destroy_ui();
    static void setup_menu(std::vector<std::string> entries);
    static void draw_menu();
    static void destroy_menu();
};

#endif
