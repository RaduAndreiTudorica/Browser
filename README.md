# Browser History Management System

This project simulates a browser history management system inspired by the architecture used in modern web browsers. It supports multiple tabs, each maintaining its own navigation history using stacks for forward and backward navigation.

## Problem Description

A web page is represented by the following structure:

```c
struct page {
    int id;
    char url[50];
    char *description;
};
```

### Default Page

When a new tab is created, it automatically loads a default page:

- ID: `0`
- URL: `https://acs.pub.ro/`
- Description: `"Computer Science"`

Up to 50 custom pages (besides the default) can be defined from an input file.

## Tab Structure

Each tab represents a browsing session and is defined by:

```c
struct tab {
    int id;
    struct page *currentPage;
    struct stack *backwardStack;
    struct stack *forwardStack;
};
```

Each tab maintains:

- `backwardStack`: stack of previously visited pages  
- `forwardStack`: stack of pages navigated forward to

## Browser Structure

The browser is defined as:

```c
struct browser {
    struct tab *current;
    struct tabsList list;
};
```

- `current`: pointer to the currently active tab  
- `list`: circular doubly linked list with a sentinel node to manage all tabs

At initialization, the browser contains:

- One tab (ID `0`)  
- The default page opened

## Supported Operations

| Command               | Description |
|------------------------|-------------|
| `NEW_TAB`              | Creates a new tab with the default page. The tab ID auto-increments and becomes the current tab. |
| `CLOSE`                | Closes the current tab. The left neighbor becomes current. Cannot close tab 0. |
| `OPEN <ID>`            | Switches to the tab with specified ID. Error if nonexistent. |
| `NEXT`                 | Switches to the next tab in the circular list. |
| `PREV`                 | Switches to the previous tab. |
| `PAGE <ID>`            | Opens a page by its ID in the current tab. Pushes current page to BACKWARD and clears FORWARD. Error if ID not found. |
| `BACKWARD`             | Moves to the last page in BACKWARD. Current page goes to FORWARD. Error if BACKWARD is empty. |
| `FORWARD`              | Moves to the last page in FORWARD. Current page goes to BACKWARD. Error if FORWARD is empty. |
| `PRINT`                | Prints tab IDs starting from the current tab (moving right) on one line. On the next line: description of the current page. |
| `PRINT_HISTORY <ID>`   | Prints the history of the specified tab: FORWARD (oldest to newest), current page, BACKWARD (newest to oldest). Error if ID not found. |

## Error Handling

For any invalid operation, the system prints:

```
403 Forbidden
```

Examples of invalid operations:

- Closing tab `0`
- Opening a non-existent tab
- Opening a page with a non-existent ID
- Navigating back or forward with an empty stack

## Implementation Notes

- Use the provided `struct` definitions directly — work with the actual data structures.
- Implement your own stack and circular doubly linked list data structures.
- Organize pages in a container (e.g., array or list) for quick lookup by ID.
- Carefully manage memory for `char *description` using dynamic allocation.

## Example Input

```
NEW_TAB
PAGE 3
BACKWARD
FORWARD
PRINT_HISTORY 1
```

## Suggested File Structure

```
browser-history/
├── main.c
├── browser.c
├── browser.h
├── stack.c
├── stack.h
├── tabs_list.c
├── tabs_list.h
└── README.md
```

## License

This project is intended for educational purposes only.
