// Copyright 2025 <Tudorica Radu Andrei>
#ifndef SDA_TEMA1_SRC_WEB_STRUCT_H_
#define SDA_TEMA1_SRC_WEB_STRUCT_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct pageNode {
    int id;
    char url[50];
    char *description;
}*PageNode;

typedef struct stackNode {
    PageNode data;
    struct stackNode *next;
}*StackNode;

typedef struct stack {
    StackNode head;
} *Stack;

typedef struct tab {
    int id;
    PageNode currentPage;
    Stack backwardstack;
    Stack forwardstack;
}*Tab;

typedef struct tabsNode {
    Tab data;
    struct tabsNode *next;
    struct tabsNode *prev;
} *TabsNode;

typedef struct tabsList {
    TabsNode sentinel;
} *TabsList;

typedef struct browser {
    Tab current;
    TabsList list;
} *BrowserNode;

PageNode init_page();
Stack init_stack();
PageNode create_page0();
PageNode create_page(int id, const char *url, const char *description);
Stack insert_page(Stack stack, PageNode page);
PageNode search_page(Stack stack, int id);
Stack delete_page(Stack stack);
PageNode free_page(PageNode page);
Stack free_stack(Stack stack);


Tab init_tab();
TabsList init_tabs_list();
Tab search_tab(TabsList list, int id);
Tab create_tab(int id);
TabsNode insert_tab(TabsNode list, Tab tab);
TabsNode create_tab_node(Tab tab);
TabsList add_tab_to_list(TabsList list, Tab tab);
TabsList delete_tab(TabsList list, TabsNode node);
TabsNode free_tab(TabsNode tab);


BrowserNode init_browser();
BrowserNode free_browser(BrowserNode browser);

void new_tab(BrowserNode browser, int id);
void print(BrowserNode browser);
void close(BrowserNode browser);
void next(BrowserNode browser);
void prev(BrowserNode browser);
void backward(BrowserNode browser);
void forward(BrowserNode browser);
void print_history(BrowserNode browser, int id);
void open(BrowserNode browser, int id);
void page(BrowserNode browser, int id, Stack pages);

void print_stack(Stack stack);

#endif  // SDA_TEMA1_SRC_WEB_STRUCT_H_
