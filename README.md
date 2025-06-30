# Browser

1.Problem Description
   
  In this assignment, we will explore a browser history management system architecture,
  inspired by systems used in modern browsers. Below are the elements that will help in
  creating a system for tracking the browsing history of a browser that allows multiple tabs,
  each tab containing a sequence of visited pages.
  
  A web page is a document accessible via the Internet that may contain text, images,
  videos, and other interactive elements. In this assignment, we define a page using a structure
  with an ID (integer), a character string representing the URL (max 50 characters), and a
  variable-length string representing the page description (including letters, digits, spaces, and punctuation, ending with newline).

  Page structure:
  
      struct page {
          int id;
          char url[50];
          char *description;
      };
  
  There is a default page that is opened each time a new tab is created, with:
  
      ID = 0
      
      URL = "https://acs.pub.ro/"
      
      Description = "Computer Science"
  
  All pages (except the default one) are read from the input file. Maximum 50 pages may be defined, and you can store them using any method (e.g., list or array).
  
  A tab is a browser section that allows opening and navigating among multiple web pages
  simultaneously in the same window. A tab is defined by:
  
  a unique ID
  
  a pointer to the current page
  
  two stacks for the tab history:
  
  BACKWARD: pages visited before the current one
  
  FORWARD: pages visited after the current one
  
  Tab structure:
  
      struct tab {
          int id;
          struct page *currentPage;
          struct stack *backwardStack;
          struct stack *forwardStack;
      };
  
  A browser is an application allowing Internet access and navigation. It displays web pages
  visually and interactively. In this assignment, a browser will have:
  
  a pointer to the current tab
  
  a circular doubly linked list with a sentinel node for all tabs
  
  Browser structure:
  
      struct browser {
          struct tab *current;
          struct tabsList list;
      };
  
  Initially, the browser contains only one tab (ID 0) with the default page opened.
  
  Important Note:
  You must use the given structures, not just IDs. Work directly with the specified data structures!

2.Available Operations
  You must implement multiple functionalities to manage the history of each tab:
  
  NEW_TAB: Adds a new tab with the default page, assigns an incremented ID, and sets it as current.
  
  CLOSE: Closes the current tab. The left neighbor becomes the new current tab. Tab 0 cannot be closed (show error).
  
  OPEN : Switches to the tab with the specified ID. Error if nonexistent.
  
  NEXT: Switches to the next tab in the list.
  
  PREV: Switches to the previous tab in the list.
  
  PAGE : Opens a page in the current tab. Current page goes to BACKWARD, FORWARD is cleared. Error if ID not found.
  
  BACKWARD: Moves to the last page in BACKWARD. Current page goes to FORWARD. Error if BACKWARD is empty.
  
  FORWARD: Moves to the last page in FORWARD. Current page goes to BACKWARD. Error if FORWARD is empty.
  
  PRINT: Displays (on one line) the IDs of all tabs, starting from the current one moving right. On the next line, print the description of the current page in the current tab.
  
  PRINT_HISTORY : Displays the URLs of the tab with the specified ID in this order: FORWARD (oldest to newest), current page, BACKWARD (newest to oldest). Error if ID not found.
  
  Error Message: For any invalid operation (as specified), print:
  
    403 Forbidden
