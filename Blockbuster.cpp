/*
//--------------------------------------------------------------------------------
Assignment: Lab 4
Group Members: Lloyd Deng, Antong Cheng, Elias Alabssie
Date: March 20, 2019
//---------------------------------------------------------------------------------------

//------------------------ Drama.cpp -------------------------------------------------
//Parent: Movie
//Child: None

//description: implementation for the Drama class.

//-------------------------------------------------------------------------------------
*/

//#include <iostream>
//#include <string>

#include "Blockbuster.h"

Blockbuster::Blockbuster(){
    set<Classic> classics;
    set<Comedy> comedies;
    set<Drama> dramas;
    unordered_map<int, string> customers;
    vector<Command> commands;
}

Blockbuster::Blockbuster(const Blockbuster &other){
    this->classics = other.classics;
    this->comedies = other.comedies;
    this->dramas = other.dramas;
    this->customers = other.customers;
    this->commands = other.commands;
}

Blockbuster::~Blockbuster(){
    set<Classic> classics;
    set<Comedy> comedies;
    set<Drama> dramas;
    unordered_map<int, string> customers;
    vector<Command> commands;
}

void Blockbuster::printInventory() {
    PrintMovies();
}

void Blockbuster::printHistory(int ID){
    cout << endl;
    for (Command c : commands){
        if (c.getID() == ID) {
            cout << c << endl;
        }
    }
    cout << endl;
}

bool Blockbuster::movieBorrow(const Command& borrow){
	if (borrow.getGenre() == 'C'){
		for(Classic c : classics){
			if(c.getMonth() == borrow.getMonth() && c.getYear() == borrow.getYear()
               && c.getActor() == borrow.getActor()){
			    // c.setStock(c.getStock() - 1); //Elements of set may not be modified
                Classic insert = c; //Instead, deep copy
                classics.erase(c); //Remove original
                insert.setStock(insert.getStock() - 1); //Modify copy
                classics.insert(insert); //Insert copy
                return true; //Return successful.
            }
        }
    }
    else if (borrow.getGenre() == 'F'){
        for(Comedy f : comedies){
            if(f.getTitle() == borrow.getTitle() && f.getYear() == borrow.getYear()){
                Comedy insert = f;
                comedies.erase(f);
                insert.setStock(insert.getStock() - 1);
                comedies.insert(insert);
                return true;
            }
        }
    }
    else if (borrow.getGenre() == 'D'){
        for(Drama d : dramas){
            if(d.getDirector() == borrow.getDirector() && d.getTitle() == borrow.getTitle()){
                d.setStock(d.getStock() - 1);
                Drama insert = d;
                dramas.erase(d);
                insert.setStock(insert.getStock() - 1);
                dramas.insert(insert);
                return true;
            }
        }
    }
    else{
        cout << "incorrect data and/or incorrect command" << endl;
        //cout << "Failed to execute the following command: " << borrow << endl;
        return false;
    }
}

bool Blockbuster::movieReturn(const Command& other){
    if (other.getGenre() == 'C'){
        for(Classic c : classics){
            if(c.getMonth() == other.getMonth() && c.getYear() == other.getYear()
               && c.getActor() == other.getActor()){
                // c.setStock(c.getStock() - 1); //Elements of set may not be modified
                Classic insert = c; //Instead, deep copy
                classics.erase(c); //Remove original
                insert.setStock(insert.getStock() + 1); //Modify copy
                classics.insert(insert); //Insert copy
                return true; //Return successful.
            }
        }
    }
    else if (other.getGenre() == 'F'){
        for(Comedy f : comedies){
            if(f.getTitle() == other.getTitle() && f.getYear() == other.getYear()){
                Comedy insert = f;
                comedies.erase(f);
                insert.setStock(insert.getStock() + 1);
                comedies.insert(insert);
                return true;
            }
        }
    }
    else if (other.getGenre() == 'D'){
        for(Drama d : dramas){
            if(d.getDirector() == other.getDirector() && d.getTitle() == other.getTitle()){
                d.setStock(d.getStock() - 1);
                Drama insert = d;
                dramas.erase(d);
                insert.setStock(insert.getStock() + 1);
                dramas.insert(insert);
                return true;
            }
        }
    }
    else{
        cout << "incorrect data and/or incorrect command" << endl;
        //cout << "Failed to execute the following command: " << borrow << endl;
        return false;
    }
}

void Blockbuster::BuildCommands(istream& inFile){
    char action;
    int ID;
    char media;
    char genre;
    string title;
    string director;
    string actor;
    int month;
    int year;
    string flush;
    string temp;

    for(;;){
        inFile >> action;

        if (action == 'I') {
            Command insert(action);
            commands.push_back(insert);
        }
        else if (action == 'H') {
            getline(inFile, temp);
            ID = stoi(temp);
            Command insert(action, ID);
            commands.push_back(insert);

        }
        else if (action == 'B' | action == 'R') {
            inFile >> ID >> media >> genre;

            if (genre == 'C'){
                inFile >> month >> year;
                getline(inFile, temp);
                actor = temp;

                Command insert(action, ID, media, genre, month, year, actor);
                commands.push_back(insert);
            }
            else if (genre == 'D'){
                getline(inFile, temp, ',');
                director = temp;
                getline(inFile, temp, ',');
                title = temp;

                Command insert(action, ID, media, genre, director, title);
                commands.push_back(insert);
            }
            else if (genre == 'F'){
                getline(inFile, temp, ',');
                title = temp;
                inFile >> year;

                Command insert(action, ID, media, genre, title, year);
                commands.push_back(insert);
            }
            else{
                cout << "Invalid video code within data4commands.txt." << endl;
                getline(inFile, flush, '\n');//no nonsense
            }
        }
        else {
            cout << "Invalid action code within data4commands.txt." << endl;
            getline(inFile, flush, '\n');//no nonsense
        }

        if(inFile.eof()){
            break;
        }
    }
}

void Blockbuster::PrintCommands() {
    cout << endl;
    for (Command c : commands){
        cout << c << endl;
    }
    cout << endl;
}

void Blockbuster::ActivateCommands() {
    for (Command c : commands){
        if (c.getAction() == 'B'){
            movieBorrow(c);
        }
        else if (c.getAction() == 'R'){
            movieReturn(c);
        }
        else if (c.getAction() == 'I'){
            printInventory();
        }
        else if (c.getAction() == 'H'){
            printHistory(c.getID());
        }
        else{
            cout << "Invalid action code." << endl;
        }
    }
}

void Blockbuster::BuildCustomers(istream& inFile){
    int ID;
    string lastName, firstName, name;

    for(;;){
        inFile >> ID >> lastName >> firstName;
        name = firstName + " " + lastName;
        Customer insert(ID, name);
        customers[ID] = name;

        if(inFile.eof()){
            break;
        }
    }
}

void Blockbuster::PrintCustomers(){
    cout << endl;
    for(auto it = customers.cbegin(); it != customers.cend(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    cout << endl;
}

void Blockbuster::BuildMovies(istream& inFile){
    char genre;
    int stock, releaseMonth, releaseYear;
    string director, title, actor;
    string temp;

    for(;;){
        genre = inFile.get();
        if(genre == 'C'){
            getline(inFile, temp, ','); //flush the first comma
            getline(inFile, temp, ',');
            stock = atoi(temp.c_str());
            getline(inFile, temp, ',');
            director = temp;
            getline(inFile, temp, ',');
            title = temp;
            for(;;){
                getline(inFile, temp, ' ');
                string::const_iterator findInt = temp.begin();
                while(findInt != temp.end() && isdigit(*findInt)){
                    findInt++;
                }
                if(!temp.empty() && findInt == temp.end()){
                    releaseMonth = atoi(temp.c_str());
                    break;
                }
                else{
                    actor = actor + " " + temp;
                    continue;
                }
            }
            getline(inFile, temp, '\n');//flush return key
            releaseYear = atoi(temp.c_str());

            Classic input(stock, director, title, actor, releaseMonth, releaseYear); //create classic object
            actor = ""; //clear buffer
            classics.insert(input); //insert classic object into data structure
        }
        else if (genre == 'D'){
            getline(inFile, temp, ','); //flush the first comma
            getline(inFile, temp, ',');
            stock = atoi(temp.c_str());
            getline(inFile, temp, ',');
            director = temp;
            getline(inFile, temp, ',');
            title = temp;
            getline(inFile, temp);
            releaseYear = atoi(temp.c_str());

            Drama input(stock, director, title, releaseYear); //create drama object
            dramas.insert(input); //insert drama object into data structure
        }
        else if (genre == 'F'){
            getline(inFile, temp, ','); //flush the first comma
            getline(inFile, temp, ',');
            stock = atoi(temp.c_str());
            getline(inFile, temp, ',');
            director = temp;
            getline(inFile, temp, ',');
            title = temp;
            getline(inFile, temp);
            releaseYear = atoi(temp.c_str());

            Comedy input(stock, director, title, releaseYear); //create classic object
            comedies.insert(input); //insert classic object into data structure
        }
        else{
            cout << "Invalid video code within data4movies.txt." << endl;
            getline(inFile, temp, '\n');//flush return key
        }

        if(inFile.eof()){
            break;
        }
    }
}

void Blockbuster::PrintMovies() {
    cout << endl;
    for (Classic c : classics){
        cout << c << ' ' << endl;
    }
    for (Drama d : dramas){
        cout << d << ' ' << endl;
    }
    for (Comedy f : comedies){
        cout << f << ' ' << endl;
    }
    cout << endl;
}