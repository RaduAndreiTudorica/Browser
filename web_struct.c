// Copyright 2025 <Tudorica Radu Andrei>
#include "web_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_error() {
    FILE *file = fopen("tema1.out", "a");
    const char error[] = "403 Forbidden";
    if (file) {
        fprintf(file, "%s\n", error);
        fclose(file);
    } else {
        printf("Error opening file\n");
    }
}

PageNode init_page() {
    PageNode page = malloc(sizeof(struct pageNode));
    if (!page) {
        printf("Memory allocation failed for PageNode\n");
        return NULL;
    }
    page->id = 0;
    strncpy(page->url, "", sizeof(page->url) - 1);
    page->description = NULL;
    return page;
}

Stack init_stack() {
    Stack stack = malloc(sizeof(struct stack));
    if (!stack) {
        printf("Memory allocation failed for Stack\n");
        return NULL;
    }
    stack->head = NULL;
    return stack;
}

PageNode create_page0() {
    PageNode page = init_page();
    if (!page) {
        return NULL;
    }
    page->id = 0;
    strncpy(page->url, "https://acs.pub.ro/", sizeof(page->url) - 1);
    page->description = malloc(strlen("Computer Science") + 1);
    if (!page->description) {
        printf("Memory allocation failed for page description\n");
        free(page);
        return NULL;
    }
    strncpy(page->description, "Computer Science",
                strlen("Computer Science") + 1);
    return page;
}

PageNode create_page(int id, const char *url, const char *description) {
    PageNode page = init_page();
    if (!page) {
        return NULL;
    }
    page->id = id;
    strncpy(page->url, url, sizeof(page->url) - 1);
    page->description = malloc(strlen(description) + 1);
    if (!page->description) {
        printf("Memory allocation failed for page description\n");
        free(page);
        return NULL;
    }
    strncpy(page->description, description, strlen(description) + 1);
    return page;
}

Stack insert_page(Stack stack, PageNode page) {
    if (!stack || !page) {
        return NULL;
    }

    StackNode new_node = malloc(sizeof(struct stackNode));
    if (!new_node) {
        printf("Memory allocation failed for StackNode\n");
        return NULL;
    }
    new_node->data = page;
    new_node->next = stack->head;
    stack->head = new_node;

    return stack;
}

PageNode clone_page(PageNode page) {
    if (!page) {
        return NULL;
    }

    PageNode new_page = create_page(page->id, page->url, page->description);
    if (!new_page) {
        return NULL;
    }
    return new_page;
}

PageNode search_page(Stack stack, int id) {
    if (!stack || !stack->head) {
        return NULL;
    }

    StackNode temp = stack->head;
    while (temp) {
        if (temp->data->id == id) {
            return temp->data;
        }
        temp = temp->next;
    }
    return NULL;
}

Stack delete_page(Stack stack) {
    if (!stack || !stack->head) {
        return NULL;
    }

    StackNode temp = stack->head;
    stack->head = stack->head->next;
    free_page(temp->data);
    free(temp);

    return stack;
}

PageNode free_page(PageNode page) {
    if (!page) {
        return NULL;
    }
    free(page->description);
    free(page);
    return NULL;
}

Stack free_stack(Stack stack) {
    if (!stack) {
        return NULL;
    }
    StackNode temp = stack->head;
    while (temp) {
        StackNode next = temp->next;
        free_page(temp->data);
        free(temp);
        temp = next;
    }
    free(stack);
    return NULL;
}

Tab init_tab() {
    Tab tab = malloc(sizeof(struct tab));
    if (!tab) {
        printf("Memory allocation failed for Tab\n");
        return NULL;
    }
    tab->id = 0;
    tab->currentPage = NULL;
    tab->backwardstack = NULL;
    tab->forwardstack = NULL;
    return tab;
}

TabsList init_tabs_list() {
    TabsList list = malloc(sizeof(struct tabsList));
    if (!list) {
        printf("Memory allocation failed for TabsList\n");
        return NULL;
    }
    TabsNode sentinel = malloc(sizeof(struct tabsNode));
    if (!sentinel) {
        printf("Memory allocation failed for TabsNode\n");
        free(list);
        return NULL;
    }
    sentinel->data = NULL;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    list->sentinel = sentinel;
    return list;
}

Tab create_tab(int id) {
    Tab tab = init_tab();
    if (!tab) {
        return NULL;
    }
    tab->id = id;
    tab->currentPage = create_page0();
    if (!tab->currentPage) {
        free(tab);
        return NULL;
    }
    tab->backwardstack = init_stack();
    if (!tab->backwardstack) {
        free(tab->currentPage->description);
        free(tab->currentPage);
        free(tab);
        return NULL;
    }
    tab->forwardstack = init_stack();
    if (!tab->forwardstack) {
        free(tab->backwardstack);
        free(tab->currentPage->description);
        free(tab->currentPage);
        free(tab);
        return NULL;
    }
    return tab;
}

Tab search_tab(TabsList list, int id) {
    if (!list || !list->sentinel) {
        return NULL;
    }

    TabsNode iter = list->sentinel->next;
    while (iter != list->sentinel) {
        if (iter->data->id == id) {
            return iter->data;
        }
        iter = iter->next;
    }
    return NULL;
}

TabsNode insert_tab(TabsNode list, Tab tab) {
    if (!list || !tab) {
        return NULL;
    }

    TabsNode new_node = create_tab_node(tab);
    if (!new_node) return NULL;

    new_node->next = list->next;
    new_node->prev = list;
    list->next->prev = new_node;
    list->next = new_node;

    return new_node;
}

TabsList add_tab_to_list(TabsList list, Tab tab) {
    if (!list || !tab || !list->sentinel) {
        return NULL;
    }

    TabsNode new_node = create_tab_node(tab);
    if (!new_node) return NULL;

    TabsNode sentinel = list->sentinel;
    TabsNode last = sentinel->prev;

    new_node->next = sentinel;
    new_node->prev = last;
    last->next = new_node;
    sentinel->prev = new_node;

    return list;
}

TabsList delete_tab(TabsList list, TabsNode node) {
    if (!list || !node || node == list->sentinel) {
        return NULL;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    free_tab(node);

    return list;
}

TabsNode free_tab(TabsNode tab) {
    if (!tab) {
        return NULL;
    }

    if (tab->data) {
        if (tab->data->currentPage) {
            free_page(tab->data->currentPage);
        }
        if (tab->data->backwardstack) {
            free_stack(tab->data->backwardstack);
        }
        if (tab->data->forwardstack) {
            free_stack(tab->data->forwardstack);
        }
        free(tab->data);
    }
    free(tab);
    return NULL;
}

TabsNode create_tab_node(Tab tab) {
    TabsNode node = malloc(sizeof(struct tabsNode));
    if (!node) {
        printf("Memory allocation failed for TabsNode\n");
        return NULL;
    }
    node->data = tab;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

BrowserNode init_browser() {
    BrowserNode browser = malloc(sizeof(struct browser));
    if (!browser) {
        printf("Memory allocation failed for BrowserNode\n");
        return NULL;
    }

    browser->current = create_tab(0);
    if (!browser->current) {
        free(browser);
        return NULL;
    }

    browser->list = init_tabs_list();
    if (!browser->list) {
        free(browser->current);
        free(browser);
        return NULL;
    }

    add_tab_to_list(browser->list, browser->current);

    return browser;
}

BrowserNode free_browser(BrowserNode browser) {
    if (!browser) {
        return NULL;
    }

    if (browser->list) {
        TabsNode iter = browser->list->sentinel->next;

        while (iter != browser->list->sentinel) {
            TabsNode next = iter->next;
            free_tab(iter);
            iter = next;
        }

        free(browser->list->sentinel);
        free(browser->list);
    }

    free(browser);
    return NULL;
}

void new_tab(BrowserNode browser, int id) {
    if (!browser) {
        return;
    }

    Tab new_tab = create_tab(id);
    if (!new_tab) {
        return;
    }

    add_tab_to_list(browser->list, new_tab);
    browser->current = new_tab;
}

void print(BrowserNode browser) {
    FILE *file = fopen("tema1.out", "a");

    if (!browser) {
        return;
    }
    TabsNode iter = browser->list->sentinel->next;
    while (iter->data != browser->current) {
        iter = iter->next;
    }
    int first = 1;

    do {
        if (iter != browser->list->sentinel) {
            if (!first) {
                fprintf(file, " ");
            }
            fprintf(file, "%d", iter->data->id);
            first = 0;
        }
        iter = iter->next;
    } while (iter->data != browser->current);
    fprintf(file, "\n%s\n", browser->current->currentPage->description);
    fclose(file);
}

void close(BrowserNode browser) {
    if (!browser || !browser->current) {
        return;
    }

    if (browser->current->id == 0) {
        print_error();
        return;
    }

    TabsNode iter = browser->list->sentinel->next;
    while (iter != browser->list->sentinel) {
        if (iter->data == browser->current) {
            break;
        }
        iter = iter->next;
    }

    TabsNode next_current = iter->prev;
    delete_tab(browser->list, iter);
    browser->current = next_current->data;
}

void next(BrowserNode browser) {
    if (!browser || !browser->current) {
        return;
    }
    TabsNode iter = browser->list->sentinel->next;
    while (iter->data != browser->current) {
        iter = iter->next;
    }
    if (iter->next != browser->list->sentinel) {
        browser->current = iter->next->data;
    } else {
        browser->current = browser->list->sentinel->next->data;
    }
}

void prev(BrowserNode browser) {
    if (!browser || !browser->current) {
        return;
    }
    TabsNode iter = browser->list->sentinel->next;
    while (iter->data != browser->current) {
        iter = iter->next;
    }
    if (iter->prev != browser->list->sentinel) {
        browser->current = iter->prev->data;
    } else {
        browser->current = browser->list->sentinel->prev->data;
    }
}

void backward(BrowserNode browser)  {
    if (!browser || !browser->current) {
        return;
    }
    if (!browser->current->backwardstack ||
            !browser->current->backwardstack->head) {
        print_error();
        return;
    }

    browser->current->forwardstack = insert_page(browser->current->forwardstack,
            clone_page(browser->current->currentPage));
    PageNode page = clone_page(browser->current->backwardstack->head->data);
    browser->current->backwardstack =
        delete_page(browser->current->backwardstack);
    free_page(browser->current->currentPage);
    browser->current->currentPage = page;
}

void forward(BrowserNode browser) {
    if (!browser || !browser->current) {
        return;
    }
    if (!browser->current->forwardstack ||
            !browser->current->forwardstack->head) {
        print_error();
        return;
    }
    browser->current->backwardstack =
            insert_page(browser->current->backwardstack,
                clone_page(browser->current->currentPage));
    PageNode page = clone_page(browser->current->forwardstack->head->data);
    browser->current->forwardstack =
        delete_page(browser->current->forwardstack);
    free_page(browser->current->currentPage);
    browser->current->currentPage = page;
}

void reverse_print_stack(StackNode stack, FILE *file) {
    if (!stack) {
        return;
    }
    reverse_print_stack(stack->next, file);
    fprintf(file, "%s\n", stack->data->url);
}

void print_history(BrowserNode browser, int id) {
    FILE *file = fopen("tema1.out", "a");

    if (!browser || !browser->current) {
        return;
    }
    Tab tab = search_tab(browser->list, id);
    if (!tab) {
        print_error();
        return;
    }
    StackNode iter = tab->forwardstack->head;

    reverse_print_stack(tab->forwardstack->head, file);

    fprintf(file, "%s\n", tab->currentPage->url);
    iter = tab->backwardstack->head;
    while (iter) {
        fprintf(file, "%s\n", iter->data->url);
        iter = iter->next;
    }
    fclose(file);
}

void open(BrowserNode browser, int id) {
    if (!browser || !browser->current) {
        return;
    }
    TabsNode iter = browser->list->sentinel->next;
    while (iter != browser->list->sentinel) {
        if (iter->data->id == id) {
            browser->current = iter->data;
            return;
        }
        iter = iter->next;
    }
    print_error();
}

void page(BrowserNode browser, int id, Stack pages) {
    if (!browser || !browser->current) {
        return;
    }
    PageNode page = search_page(pages, id);
    if (!page) {
        print_error();
        return;
    }
    if (browser->current->currentPage) {
        browser->current->backwardstack =
            insert_page(browser->current->backwardstack,
                    clone_page(browser->current->currentPage));
        free_page(browser->current->currentPage);
        browser->current->currentPage = clone_page(page);
        browser->current->forwardstack =
            free_stack(browser->current->forwardstack);
        browser->current->forwardstack = init_stack();
    }
}
