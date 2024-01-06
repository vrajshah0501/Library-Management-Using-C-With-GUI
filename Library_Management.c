#include <gtk/gtk.h>
#include <string.h>

#define MAX_BOOKS 100

// Structure to represent a book
struct Book {
    char title[100];
    char author[100];
    int year;
};

struct {
    GtkWidget *entry_title;
    GtkWidget *entry_author;
    GtkWidget *entry_year;
    GtkWidget *text_view;
    struct Book library[MAX_BOOKS];
    int numBooks;
} app;

// Function to add a book to the library
void addBook() {
    const char *title = gtk_entry_get_text(GTK_ENTRY(app.entry_title));
    const char *author = gtk_entry_get_text(GTK_ENTRY(app.entry_author));
    const char *year_str = gtk_entry_get_text(GTK_ENTRY(app.entry_year));

    if (app.numBooks < MAX_BOOKS) {
        strncpy(app.library[app.numBooks].title, title, sizeof(app.library[app.numBooks].title) - 1);
        strncpy(app.library[app.numBooks].author, author, sizeof(app.library[app.numBooks].author) - 1);
        app.library[app.numBooks].year = atoi(year_str);

        app.numBooks++;

        // Update the text view with the new book
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app.text_view));
        gtk_text_buffer_insert_at_cursor(buffer, "\nBook added successfully!\n", -1);
    } else {
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app.text_view));
        gtk_text_buffer_insert_at_cursor(buffer, "\nLibrary is full. Cannot add more books.\n", -1);
    }
}

// Function to display all books in the library
void displayBooks() {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app.text_view));
    gtk_text_buffer_set_text(buffer, "", -1);

    gtk_text_buffer_insert_at_cursor(buffer, "Library Catalog:\n", -1);
    gtk_text_buffer_insert_at_cursor(buffer, "--------------------------------------------------\n", -1);
    gtk_text_buffer_insert_at_cursor(buffer, "Title                  Author                 Year\n", -1);
    gtk_text_buffer_insert_at_cursor(buffer, "--------------------------------------------------\n", -1);

    for (int i = 0; i < app.numBooks; ++i) {
        char entry[256];
        snprintf(entry, sizeof(entry), "%-22s %-22s %-4d\n", app.library[i].title, app.library[i].author, app.library[i].year);
        gtk_text_buffer_insert_at_cursor(buffer, entry, -1);
    }

    gtk_text_buffer_insert_at_cursor(buffer, "--------------------------------------------------\n", -1);
}

// Function to search for a book by title
void searchBook(const char *title) {
    int found = 0;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app.text_view));

    for (int i = 0; i < app.numBooks; ++i) {
        if (strcmp(app.library[i].title, title) == 0) {
            found = 1;
            char entry[256];
            snprintf(entry, sizeof(entry), "\nBook found!\nTitle: %s\nAuthor: %s\nYear: %d\n",
                     app.library[i].title, app.library[i].author, app.library[i].year);
            gtk_text_buffer_insert_at_cursor(buffer, entry, -1);
            break;
        }
    }

    if (!found) {
        gtk_text_buffer_insert_at_cursor(buffer, "\nBook not found in the library.\n", -1);
    }
}

// Function to delete a book by title
void deleteBook(const char *title) {
    int found = 0;

    for (int i = 0; i < app.numBooks; ++i) {
        if (strcmp(app.library[i].title, title) == 0) {
            found = 1;

            // Shift the remaining books to fill the gap
            for (int j = i; j < app.numBooks - 1; ++j) {
                strcpy(app.library[j].title, app.library[j + 1].title);
                strcpy(app.library[j].author, app.library[j + 1].author);
                app.library[j].year = app.library[j + 1].year;
            }

            app.numBooks--;
            GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app.text_view));
            gtk_text_buffer_insert_at_cursor(buffer, "\nBook deleted successfully!\n", -1);
            break;
        }
    }

    if (!found) {
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app.text_view));
        gtk_text_buffer_insert_at_cursor(buffer, "\nBook not found in the library. Deletion failed.\n", -1);
    }
}

// Function to display books by a specific author
void displayBooksByAuthor(const char *author) {
    int found = 0;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app.text_view));

    gtk_text_buffer_insert_at_cursor(buffer, "\nBooks by ", -1);
    gtk_text_buffer_insert_at_cursor(buffer, author, -1);
    gtk_text_buffer_insert_at_cursor(buffer, ":\n", -1);
    gtk_text_buffer_insert_at_cursor(buffer, "--------------------------------------------------\n", -1);
    gtk_text_buffer_insert_at_cursor(buffer, "Title                  Author                 Year\n", -1);
    gtk_text_buffer_insert_at_cursor(buffer, "--------------------------------------------------\n", -1);

    for (int i = 0; i < app.numBooks; ++i) {
        if (strcmp(app.library[i].author, author) == 0) {
            found = 1;
            char entry[256];
            snprintf(entry, sizeof(entry), "%-22s %-22s %-4d\n", app.library[i].title, app.library[i].author, app.library[i].year);
            gtk_text_buffer_insert_at_cursor(buffer, entry, -1);
        }
    }

    if (!found) {
        gtk_text_buffer_insert_at_cursor(buffer, "No books found by ", -1);
        gtk_text_buffer_insert_at_cursor(buffer, author, -1);
        gtk_text_buffer_insert_at_cursor(buffer, ".\n", -1);
    }

    gtk_text_buffer_insert_at_cursor(buffer, "--------------------------------------------------\n", -1);
}

// GTK callback for the Add Book button
void on_add_book_button_clicked(GtkWidget *widget, gpointer data) {
    addBook();
    displayBooks();
}

// GTK callback for the Display Books button
void on_display_books_button_clicked(GtkWidget *widget, gpointer data) {
    displayBooks();
}

// GTK callback for the Search Book button
void on_search_book_button_clicked(GtkWidget *widget, gpointer data) {
    const char *title = gtk_entry_get_text(GTK_ENTRY(app.entry_title));
    searchBook(title);
}

// GTK callback for the Delete Book button
void on_delete_book_button_clicked(GtkWidget *widget, gpointer data) {
    const char *title = gtk_entry_get_text(GTK_ENTRY(app.entry_title));
    deleteBook(title);
    displayBooks();
}

// GTK callback for the Display Books by Author button
void on_display_books_by_author_button_clicked(GtkWidget *widget, gpointer data) {
    const char *author = gtk_entry_get_text(GTK_ENTRY(app.entry_author));
    displayBooksByAuthor(author);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label_title;
    GtkWidget *label_author;
    GtkWidget *label_year;
    GtkWidget *button_add_book;
    GtkWidget *button_display_books;
    GtkWidget *button_search_book;
    GtkWidget *button_delete_book;
    GtkWidget *button_display_books_by_author;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Library Management System");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    label_title = gtk_label_new("Title:");
    app.entry_title = gtk_entry_new();
    label_author = gtk_label_new("Author:");
    app.entry_author = gtk_entry_new();
    label_year = gtk_label_new("Year:");
    app.entry_year = gtk_entry_new();

    button_add_book = gtk_button_new_with_label("Add Book");
    g_signal_connect(button_add_book, "clicked", G_CALLBACK(on_add_book_button_clicked), NULL);

    button_display_books = gtk_button_new_with_label("Display Books");
    g_signal_connect(button_display_books, "clicked", G_CALLBACK(on_display_books_button_clicked), NULL);

    button_search_book = gtk_button_new_with_label("Search Book");
    g_signal_connect(button_search_book, "clicked", G_CALLBACK(on_search_book_button_clicked), NULL);

    button_delete_book = gtk_button_new_with_label("Delete Book");
    g_signal_connect(button_delete_book, "clicked", G_CALLBACK(on_delete_book_button_clicked), NULL);

    button_display_books_by_author = gtk_button_new_with_label("Display Books by Author");
    g_signal_connect(button_display_books_by_author, "clicked", G_CALLBACK(on_display_books_by_author_button_clicked), NULL);

    app.text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(app.text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(app.text_view), FALSE);

    gtk_grid_attach(GTK_GRID(grid), label_title, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), app.entry_title, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_author, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), app.entry_author, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_year, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), app.entry_year, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_add_book, 0, 3, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), button_display_books, 0, 4, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), button_search_book, 0, 5, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), button_delete_book, 0, 6, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), button_display_books_by_author, 0, 7, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), app.text_view, 0, 8, 2, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
