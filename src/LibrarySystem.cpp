
#include "LibrarySystem.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
extern ofstream outputFile;

//default constructor
Movie::Movie(const int id, const string title, const int year) {
    this->id = id;
    this->title = title;
    this->year = year;
    this->userId = -1;
}


struct MovieList::Node {
    Movie *movie;
    Node *next;

    ~Node() {
        delete movie;
    }
};


MovieList::MovieList() {
    head = NULL;
}


// default constructor
User::User(const int id, const string name) {
    this->id = id;
    this->name = name;
    this->movieList = new MovieList();
}

struct UserList::Node {
    User *user;
    Node *next, *precedeUser;

    ~Node() {
        delete user;
    }
};


UserList::UserList() {
    head = NULL;
}

// destructor
User::~User() {
    if (movieList->head != NULL) {
        MovieList::Node *prev;
        MovieList::Node *cur;
        for (prev = movieList->head, cur = movieList->head->next; cur != movieList->head; prev = cur, cur = cur->next) {
            delete prev;
        }
        delete prev;
    }
    delete movieList;

}


// default consturctor
LibrarySystem::LibrarySystem() {
    movieList = new MovieList();
    userList = new UserList();

}

// destructor
LibrarySystem::~LibrarySystem() {
    if (movieList->head != NULL) {
        MovieList::Node *prev;
        MovieList::Node *cur;
        for (prev = movieList->head, cur = movieList->head->next; cur != movieList->head; prev = cur, cur = cur->next) {
            delete prev;
        }
        delete prev;
    }
    if (userList->head != NULL) {
        UserList::Node *prev;
        UserList::Node *cur;
        for (prev = userList->head, cur = userList->head->next; cur != userList->head; prev = cur, cur = cur->next) {
            delete prev;
        }
        delete prev;
    }
    delete movieList;
    delete userList;
}

// add movie to library
void LibrarySystem::addMovie(const int movieId, const string name, const int year) {
    if (movieId < 0)
        outputFile << "Movie id must be a positive number" << endl;
    else if (movieList->head == NULL) {
        movieList->add(movieId, name, year);
        outputFile << "Movie " << movieId << " has been added" << endl;
    } else {
        bool doesExist = false;
        MovieList::Node *cur;
        for (cur = movieList->head; cur->next != movieList->head; cur = cur->next) {
            if (cur->movie->id == movieId)
                doesExist = true;
        }
        // for the last movie in the list
        if (cur->movie->id == movieId)
            doesExist = true;
        if (doesExist)
            outputFile << "Movie " << movieId << " already exists" << endl;
        else {
            movieList->add(movieId, name, year);
            outputFile << "Movie " << movieId << " has been added" << endl;
        }

    }

}
// add movie to movie list
void MovieList::add(const int movieId, const string name, const int year) {
    Movie *movie = new Movie(movieId, name, year);
    Node *newPtr = new Node();
    newPtr->movie = movie;
    if (head == NULL) {
        head = newPtr;
        newPtr->next = newPtr;
    } else {
        Node *cur;
        Node *last;
        for (last = head, cur = head->next; cur != head; last = cur, cur = cur->next);
        newPtr->next = head;
        last->next = newPtr;
    }
}

// delete movie from movie list
void LibrarySystem::deleteMovie(const int movieId) {
    bool doesExist = false;
    MovieList::Node *movieNode;
    Movie *movie;
    if (movieList->head == NULL)
        outputFile << "There is no movie in the list" << endl;
    else {
        movieNode = movieList->findMovie(movieId);
        if (!movieNode && userList->head != NULL) {
            UserList::Node *cur;
            UserList::Node *prev;
            for (prev = userList->head, cur = userList->head->next;
                 cur != userList->head; prev = cur, cur = cur->next) {
                MovieList::Node *temp = prev->user->movieList->findMovie(movieId);
                if (temp) {
                    movie = temp->movie;
                    doesExist = true;
                }

            }
            // for the last user
            MovieList::Node *temp = prev->user->movieList->findMovie(movieId);
            if (temp) {
                movie = temp->movie;
                doesExist = true;
            }
        } else if (movieNode) {
            movie = movieNode->movie;
            doesExist = true;
        }
        if (doesExist) {
            if (movie->userId != -1)
                returnMovie(movieId);

            movieList->removeMovie(movieId);
            if (movieNode)
                outputFile << "Movie " << movieId << " has not been checked out" << endl;
            outputFile << "Movie " << movieId << " has been deleted" << endl;
        } else
            outputFile << "Movie " << movieId << " does not exist in the library" << endl;
    }


}

// delete movie from movie list
bool MovieList::removeMovie(const int movieId) {

    if (head->movie->id == movieId) {
        Node *lastNode;
        for (lastNode = head; lastNode->next != head; lastNode = lastNode->next);
        if (head == lastNode) {
            delete head;
            head = NULL;
        } else {
            Node *temp = head;
            head = head->next;
            lastNode->next = head;
            delete temp;
        }
        return true;
    } else if (head != NULL) {
        Node *cur;
        bool found = false;
        for (cur = head; cur->next != head; cur = cur->next) {
            if (cur->next->movie->id == movieId) {
                found = true;
                break;
            }
        }
        // For the last movie in the list
        if (cur->next->movie->id == movieId)
            found = true;
        if (found) {
            Node *nodeToRemove = cur->next;
            cur->next = cur->next->next;
            delete nodeToRemove;
            return true;
        }
        return false;
    }
    return false;
}

// add new user to library
void LibrarySystem::addUser(const int userId, const string name) {
    if (userId < 0)
        outputFile << "User id must be a positive integer" << endl;
    else if ((*userList).head == NULL) {
        (*userList).add(userId, name);
        outputFile << "User " << userId << " has been added" << endl;
    } else {
        bool doesExist = false;
        UserList::Node *cur;
        for (cur = userList->head; cur->next != userList->head; cur = cur->next) {
            if (cur->user->id == userId)
                doesExist = true;
        }
        // For the last user in the list
        if (cur->user->id == userId)
            doesExist = true;
        if (doesExist)
            outputFile << "User " << userId << " already exists" << endl;
        else {
            (*userList).add(userId, name);
            outputFile << "User " << userId << " has been added" << endl;
        }
    }


}

// add new user to user list
void UserList::add(const int userId, const string name) {
    User *newUser = new User(userId, name);
    Node *newPtr = new Node();
    newPtr->user = newUser;
    if (head == NULL) {
        head = newPtr;
        newPtr->next = newPtr;
        newPtr->precedeUser = newPtr;
    } else {
        Node *prev = head->precedeUser;

        prev->next = newPtr;
        newPtr->next = head;
        newPtr->precedeUser = prev;
        head->precedeUser = newPtr;
    }
}

MovieList::Node *MovieList::findMovie(const int movieId) {
    Node *cur;
    if (head != NULL) {
        for (cur = head; cur->next != head; cur = cur->next) {
            if (cur->movie->id == movieId)
                return cur;
        }
        // For the last movie in the list
        if (cur->movie->id == movieId)
            return cur;
    }
    return NULL;
}

// find the user with id
UserList::Node *UserList::findUser(const int userId) {
    if (head == NULL)
        return NULL;
    Node *cur;
    for (cur = head; cur->next != head; cur = cur->next) {
        if (cur->user->id == userId)
            return cur;
    }
    if (cur->user->id == userId)
        return cur;
    return NULL;
}

// delete user from library
void LibrarySystem::deleteUser(const int userId) {
    UserList::Node *cur = userList->findUser(userId);
    if (cur != NULL) {
        MovieList::Node *curMovie = cur->user->movieList->head;
        MovieList::Node *prevMovie = curMovie;
        if (curMovie != NULL) {
            curMovie = curMovie->next;
            for (; curMovie != cur->user->movieList->head; prevMovie = curMovie, curMovie = curMovie->next) {
                returnMovie(prevMovie->movie->id);
            }
            returnMovie(prevMovie->movie->id);
        }
        UserList::Node *prev = cur->precedeUser;
        prev->next = cur->next;
        cur->next->precedeUser = prev;
        if (cur == userList->head) {
            userList->head = cur->next;
            if (cur->next == cur)
                userList->head = NULL;
        }

        delete cur;
        outputFile << "User " << userId << " has been deleted" << endl;
    } else
        outputFile << "User " << userId << " does not exist" << endl;
}

void UserList::display() {
    outputFile <<  " " << "User id" << " " << "User name" << endl;

    Node *cur;
    if (head != NULL) {
        for (cur = head; cur->next != head; cur = cur->next) {
            User *curUser = cur->user;
            outputFile <<  " " << curUser->id << " " << (curUser->name).c_str() << endl;
        }
        // For the last user
        User *lastUser = cur->user;
        outputFile <<  " " << lastUser->id << " " << (lastUser->name).c_str() << endl;
    }
}

void LibrarySystem::showAllMovies() {
    outputFile << "Movie id" << " - " << "Movie name" << " - " << "Year" << " - "
         << "Status" << endl;
    movieList->display();
    if (userList->head != NULL) {
        UserList::Node *cur;
        UserList::Node *prev;
        for (prev = userList->head, cur = userList->head->next; cur != userList->head; prev = cur, cur = cur->next)
            prev->user->movieList->display();
        // for the last user
        prev->user->movieList->display();
    }
}

void MovieList::display() {
    Node *cur;
    if (head != NULL) {
        for (cur = head; cur->next != head; cur = cur->next) {
            Movie *curMovie = cur->movie;
            outputFile << curMovie->id << " " << (curMovie->title).c_str() << " "<< curMovie->year << " ";

            if (curMovie->userId != -1)
                outputFile << "Checked out by User " << curMovie->userId << endl;
            else
                outputFile << "Not checked out" << endl;

        }
        // For the last movie
        Movie *lastMovie = cur->movie;
        outputFile << lastMovie->id << " " << (lastMovie->title).c_str() << " "<< lastMovie->year <<" ";
        if (lastMovie->userId != -1)
            outputFile << "Checked out by User " << lastMovie->userId << endl;
        else
            outputFile << "Not checked out" << endl;
    }
}

void LibrarySystem::checkoutMovie(const int movieId, const int userId) {

    bool doesExist = false;
    MovieList::Node *movieNode = movieList->findMovie(movieId);
    Movie *movie;
    if (movieNode) {
        doesExist = true;
        movie = movieNode->movie;
    } else {
        UserList::Node *cur;
        UserList::Node *prev;
        if (userList->head != NULL) {
            for (prev = userList->head, cur = userList->head->next;
                 cur != userList->head; prev = cur, cur = cur->next) {
                MovieList::Node *temp = prev->user->movieList->findMovie(movieId);
                if (temp) {
                    doesExist = true;
                    movie = temp->movie;
                }
            }
            //For the last user
            MovieList::Node *temp = prev->user->movieList->findMovie(movieId);
            if (temp) {
                doesExist = true;
                movie = temp->movie;
            }
        }
    }
    if (doesExist) {
        const int id = movie->id;
        const string title = movie->title;
        const int year = movie->year;

        User *user;
        UserList::Node *userNode = userList->findUser(userId);
        if (userNode != NULL) {
            user = userNode->user;
            if (movie->userId == -1) {
                user->movieList->add(id, title, year);
                movieList->removeMovie(id);
                Movie *addedMovie = user->movieList->findMovie(id)->movie;
                addedMovie->userId = userId;
                outputFile << "Movie " << movieId << " has been checked out by User " << userId << endl;
            } else
                outputFile << "Movie " << movieId << " has been already checked out by another user" << endl;
        } else {

            outputFile << "User " << userId << " does not exist for checkout" << endl;
        }
    } else
        outputFile << "Movie " << movieId << " does not exist for checkout" << endl;

}

void LibrarySystem::returnMovie(const int movieId) {

    bool doesExist = false;
    MovieList::Node *movieNode = movieList->findMovie(movieId);
    Movie *movie;
    if (movieNode) {
        doesExist = true;
        movie = movieNode->movie;
    } else {
        UserList::Node *cur;
        UserList::Node *prev;
        if (userList->head != NULL) {
            for (prev = userList->head, cur = userList->head->next;
                 cur != userList->head; prev = cur, cur = cur->next) {
                MovieList::Node *temp = prev->user->movieList->findMovie(movieId);
                if (temp) {
                    doesExist = true;
                    movie = temp->movie;
                }
            }
            //For the last user
            MovieList::Node *temp = prev->user->movieList->findMovie(movieId);
            if (temp) {
                doesExist = true;
                movie = temp->movie;
            }
        }
    }
    if (doesExist) {
        int userId = movie->userId;
        if (userId == -1)
            outputFile << "Movie " << movieId << " has not been checked out" << endl;
        else {
            User *user = userList->findUser(userId)->user;

            const string title = movie->title;
            const int year = movie->year;

            user->movieList->removeMovie(movieId);
            movieList->add(movieId, title, year);
            outputFile << "Movie " << movieId << " has been returned" << endl;
        }

    } else
        outputFile << "Movie " << movieId << " not exist in the library" << endl;
}

void LibrarySystem::showMovie(const int movieId) {
    bool doesExist = false;
    MovieList::Node *movieNode = movieList->findMovie(movieId);
    Movie *movie;
    if (movieNode) {
        movie = movieNode->movie;
        outputFile << movie->id << " " << movie->title << " " << movie->year << " "
             << "Not checked out" << endl;
        doesExist = true;
    } else if (userList->head != NULL) {
        UserList::Node *cur;
        UserList::Node *prev;
        for (prev = userList->head, cur = userList->head->next; cur != userList->head; prev = cur, cur = cur->next) {
            MovieList::Node *movies = prev->user->movieList->findMovie(movieId);
            if (movies) {
                doesExist = true;
                Movie *theMovie = movies->movie;
                outputFile << theMovie->id << " " << theMovie->title << " "
                     << theMovie->year << " " << "Checked out by User " << theMovie->userId << endl;

            }
        }
        // For the last movie
        MovieList::Node *movies = prev->user->movieList->findMovie(movieId);
        if (movies) {
            doesExist = true;
            Movie *theMovie = movies->movie;
            outputFile <<  theMovie->id << " " << theMovie->title << " " << theMovie->year
                 << " " << "Checked out by User " << theMovie->userId << endl;
        }
    }
    if (!doesExist)
        outputFile << "Movie with the id " << movieId << " does not exist" << endl;
}

void LibrarySystem::showUser(const int userId) {
    UserList::Node *userNode = userList->findUser(userId);
    User *user;
    if (userNode) {
        user = userNode->user;
        outputFile << "User id: " << user->id << " User name: " << user->name << endl;
        if (user->movieList->head) {
            outputFile << "User " << user->id << " checked out the following Movies:" << endl;
            outputFile << "Movie id" << " - " << "Movie name" << " - " << "Year" << endl;
            MovieList::Node *cur = user->movieList->head;
            Movie *firstMovie = cur->movie;
            cur = cur->next;
            for (; cur != user->movieList->head; cur = cur->next) {
                Movie *curMovie = cur->movie;
                outputFile << curMovie->id << " " << (curMovie->title).c_str() << " "
                     << curMovie->year <<  endl;
            }
            outputFile << firstMovie->id << " " << (firstMovie->title).c_str() << " "
                 << firstMovie->year << endl;
        } else
            outputFile << "User " << userId << " has no movies" << endl;
    } else
        outputFile << "User " << userId << " does not exist" << endl;
}
