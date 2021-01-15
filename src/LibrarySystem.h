#ifndef LIB1_LIBRARYSYSTEM_H
#define LIB1_LIBRARYSYSTEM_H

using namespace std;

#include <string>


// movie class that store the information of movies
class Movie {
public:
    int id;
    string title;
    int year;
    int userId;

    Movie(const int = 0, const string = "", const int = 0);

    friend class MovieList;
    friend class LibrarySystem;
};


class MovieList {
public:
    struct Node;
    Node *head;

    // default constructor
    MovieList();
    void add(const int movieId, const string name, const int year);
    bool removeMovie(const int movieId);
    Node *findMovie(const int movieId);
    void display();
    friend class LibrarySystem;
};

class User {
public:
    // default constructor
    int id;
    string name;
    MovieList *movieList;

    User(const int id, const string name);

    ~User();

    friend class UserList;

    friend class LibrarySystem;

    friend class MovieList;
};

// circular linked list that store users
class UserList {
    struct Node;
    Node *head;

public:
    UserList();

    void add(const int userId, const string name);

    void deleteUser(const int userId);

    Node *findUser(const int userId);

    void display();

    friend class LibrarySystem;
};

class LibrarySystem {
public:
    MovieList *movieList;
    UserList *userList;

    LibrarySystem();

    ~LibrarySystem();

    void addMovie(const int movieId, const string name, const int year);

    void deleteMovie(const int movieId);

    void addUser(const int userId, const string name);

    void deleteUser(const int userId);

    void checkoutMovie(const int movieId, const int userId);

    void returnMovie(const int movieId);

    void showAllMovies();

    void showMovie(const int movieId);

    void showUser(const int userId);
};


#endif //LIB1_LIBRARYSYSTEM_H
