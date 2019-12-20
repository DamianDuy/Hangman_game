#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <unistd.h>
#include <string>
#include <boost/algorithm/string.hpp>

std::string reading_from_the_titles(int random_number);
std::string reading_from_the_authors(int random_number);
void menu();
void users_input(std::string title, int difficulty, std::string author);
int if_correct_author (std::string author);
void draw_if_won();
void draw_if_author_is_false();
void draw_if_lost();

int main()
{
 std::cout << "Welcome to the game." << std::endl;
 sleep(2);
 std::cout << "The rules are pretty simple. It is basically a Hangman game with words to guess being different books' titles." << std::endl;
 sleep(3);
 std::cout << "Remember though, to win you also have to give a name of the author of the book. Good luck!" << std::endl;
 srand(time(NULL));
 int random_number = (std::rand() % 7) + 1;
 sleep(2);
 std::string title = reading_from_the_titles(random_number);
 std::string author = reading_from_the_authors(random_number);
 int difficulty = 0;
 menu();
 int choice = 0;
 std::cin >> choice;
 if (std::cin.fail())
    {
       std::cout << "Invalid input. Program will be terminated.";
       exit (EXIT_FAILURE);
    }
 while (choice != 0 && choice != 1)
 {
    std::cout << "No such choice in the menu. Try again." << std::endl;
    std::cin >> choice;
    if (std::cin.fail())
     {
       std::cout << "Invalid input. Program will be terminated.";
       exit (EXIT_FAILURE);
     }
 }
 while (choice == 1)
  {
    std::cout << "Choose your difficulty (the number of times that you can guess the letter)." << std::endl;
    std::cout << "Please insert the number between 1 to 10: ";
    std::cin >> difficulty;
    if (difficulty > 10 || difficulty < 1)
    {
        std::cout << "Invalid input. Program will be terminated.";
        exit (EXIT_FAILURE);
    }
    std::cout << std::endl;
    users_input(title,difficulty,author);
    random_number = (std::rand() % 7) + 1;
    title = reading_from_the_titles(random_number);
    author = reading_from_the_authors(random_number);
    menu();
    std::cin >> choice;
    if (std::cin.fail())
    {
       std::cout << "Invalid input. Program will be terminated.";
       exit (EXIT_FAILURE);
    }
    while (choice != 0 && choice != 1)
    {
      std::cout << "No such choice in the menu. Try again." << std::endl;
      std::cin >> choice;
      if (std::cin.fail())
      {
         std::cout << "Invalid input. Program will be terminated.";
         exit (EXIT_FAILURE);
      }
    }
  }
 std::cout << "Thank you for playing!";
}
std::string reading_from_the_titles(int random_number)//Function that reads the random title of the book from the file
{
    std::fstream titlesFile;
    titlesFile.open("Books'_Titles.txt");
    if (!titlesFile.good())
    {
        std::cout << "Could not open the file. Program will be terminated. Check if the file" << std::endl << "\"Books'_Titles.txt\" is in the folder.";
        exit(EXIT_FAILURE);
    }
    std::string title;
    std::string line;
    int line_number = 1;
    while(getline(titlesFile,line))
    {
        if (line_number == random_number)
        {
            title = line;
            break;
        }
        line_number++;
    }
    titlesFile.close();
    return title;
}
std::string reading_from_the_authors(int random_number)//Function that reads the author of the chosen book from the file
{
    std::fstream authorsFile;
    authorsFile.open("Books'_Authors.txt");
    if (!authorsFile.good())
    {
        std::cout << "Could not open the file. Program will be terminated. Check if the file" << std::endl << "\"Books'_Authors.txt\" is in the folder.";
        exit(EXIT_FAILURE);
    }
    std::string author;
    std::string line;
    int line_number = 1;
    while(getline(authorsFile,line))
    {
        if (line_number == random_number)
        {
            author = line;
            break;
        }
        line_number++;
    }
    authorsFile.close();
    return author;
}
void users_input (std::string title, int difficulty, std::string author)//Function  that controls the game, gets user input and return the output while also counting the number of correct guesses
{
  {
    std::string input;
    std::string abs_title = boost::to_upper_copy(title);
    std::string to_show (title);
    //Setting string to_show to beginning value
    for (std::string::size_type i = 0; i < title.size(); i++)
    {
        if (title[i] != ' ') to_show[i] = '*';
        else to_show[i] = ' ';
    }
    std::cout << to_show << std::endl;
    std::cin.ignore(1000,'\n');
    //Handling user's input
    while (true)
    {
        if (difficulty == 0){std::cout << "Wrong! the correct title was " << title <<" by " << author <<"." << std::endl;draw_if_lost(); break;}
        if (difficulty == 1) std::cout << "This is your last chance. Guess the title: " << std::endl;
        else std::cout << "Guess the letter or the title: ";
        std::getline (std::cin,input);
        std::string abs_input = boost::to_upper_copy(input); //Using boost library
        if (abs_input == abs_title) //User can insert title in both upper and lower case
        {
          std::cout << "Congratulations! You guessed the book!" << std::endl;
          if_correct_author(author);
          break;
        }
        else
        {
          for (std::string::size_type i = 0; i < title.size(); i++)
            {
                if (title[i] == toupper(input[0]) || title[i] == tolower(input[0])) to_show[i] = title[i]; //User can insert both upper and lower case letters
            }
        }
        std::cout << to_show << std::endl;
        difficulty--;
        std::cout << "You have " << difficulty << " guesses left. " << std::endl;
        std::cin.clear();
     }
  }
}
int if_correct_author(std::string author)//Checks If user guessed the author and shows the game results
{
    std::string user_input;
    std::cout << "Who is the author of this book?" << std::endl;
    std::cin.clear();
    std::getline (std::cin,user_input);
    std::string abs_user_input = boost::to_upper_copy(user_input);
    std::string abs_author = boost::to_upper_copy(author);
    if (abs_user_input == abs_author)
    {
        draw_if_won();
        return 0;
    }
    else
    {
        std::cout << "Wrong, the correct author was " << author <<"." << std::endl;
        draw_if_author_is_false();
        return 0;
    }
}
void menu()
{
    std::cout << std::endl;
    std::cout << "0) Exit" << std::endl
              << "1) Play" << std::endl;
}
void draw_if_won()//Display a drawing if player won the game
{
  std::cout << std::endl<< "            0" << std::endl
            <<"           -|-" << std::endl
            <<"            ^" << std::endl
            <<"      CONGRATULATIONS!";
}
void draw_if_author_is_false()//Display a drawing if player won but did not guess the author
{
 std::cout << std::endl<< "            0" << std::endl
            <<"            | " << std::endl
            <<"            ^" << std::endl
            <<"        ALMOST...";
}
void draw_if_lost()//Display a drawing if player lost
{
 std::cout << std::endl<< "          <-0--" << std::endl
            <<"            | " << std::endl
            <<"            ^" << std::endl
            <<"        YOU HAVE LOST.";
}
