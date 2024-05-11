#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include<time.h>

using namespace std;

void registerPlayer(string name, string ID);  //will register new players into the game 
bool findPlayer(string newID);  //will check if a username that a player has entered already exists or not
string displayInfo(string ID); //will display a user's info based on their ID
void addWin(string userID); //will add a win to a person's record
void addLoss(string userID); //will add a loss to a person's record
void start(char word[], char hint[], string playerName_1); //will initialize the game
void game(const char word[], const char hint[], string playerName_1, string playerName_2, string userID_1, string userID_2); //The pvp Game
bool all_letters_guessed(const bool guessed[], int len);//function to check if all the letters have been gussed or not 
void hangmanStatus(int livesLeft); // will display the current status of the hangman
void display_word(const char word[], const bool guessed[]); // will display the current status of the word being guessed
void reveal(const char word[], int len); //will reveal the word at the end of the game
string generateWord(); //being used to choose a random word for the PVC mode
void pcgame(const char word[], string playerName, string userID); //the pvc game


int main()
{
    // Constants for the maximum word length and number of attempts allowed in the game
    const int word_length_max = 1000;
    const int attempts = 6;

    // Dynamic allocation of memory for character arrays to store word and hint
    char* word = new char[word_length_max];
    char* hint = new char[word_length_max];

    string modeOption;

    // Display the welcome message and options to start the game
    cout << "\t\t\t\t\t+--------------------------------+" << endl;
    cout << "\t\t\t\t\t| WELCOME TO HANGMAN WITH FRIENDS|" << endl;
    cout << "\t\t\t\t\t+--------------------------------+" << endl << endl;

    // Loop to manage the game menu and user interactions
    while (true)
    {
        // Prompt the user to choose game mode or exit
        cout << "Press 'A' to play PVP mode, 'B' to play PVC mode or 'T' to exit the game => ";
        cin >> modeOption;

        // Check the chosen option and take appropriate actions based on user input
        if (modeOption.length() > 1)
        {
            // Notify the user of an invalid option and prompt to try again
            cout << "Invalid option, please try again.\n";
        }
        else if (tolower(modeOption[0]) == 'a')
        {
            // Player vs Player mode selected
            string playerOption;
            string userID_1, userID_2, playerName_1, playerName_2;

            // Handling Player 1's account access or registration
            while (true)
            {
                // Prompt Player 1 to access an existing account or register as a new player
                cout << "Player 1: Press 'A' to access your existing account or 'B' to register as a new player: ";
                cin >> playerOption;
                
                // Check Player 1's chosen option and take necessary actions
                if (playerOption.length() > 1)
                {
                    // Notify of an invalid input and prompt to try again
                    cout <<"Invalid input. Please try again.\n";
                }
                else if (tolower(playerOption[0] == 'a'))
                {
                    // Player 1 chooses to access an existing account
                    // Loop to prompt the user to enter a username until it is found
                    while (true)
                    {
                        cout << "Enter your unique username to access your account: ";
                        cin >> userID_1;
                        // Check if the entered username exists
                        if (findPlayer(userID_1) == true)
                        {
                            // Display player information and break the loop if the username is found
                            playerName_1 = displayInfo(userID_1);
                            break;
                        }
                        else
                        {
                            // Notify that the entered username does not exist and prompt to try again
                            cout << "The username you entered does not exist, please try again. \n";
                        }
                    }
                    break;
                }
                else if (tolower(playerOption[0]) == 'b')
                {
                    // Player 1 chooses to register as a new player
                    cout << "Enter your name: ";
                    cin.ignore(); // Clear the input buffer
                    getline(cin, playerName_1); // Read the entire line for the player's name

                    // Loop to prompt the user to enter a unique username until it is found
                    while (true)
                    {
                        cout << "Choose a unique username for yourself: ";
                        cin >> userID_1;
                        // Check if the entered username is unique
                        if (findPlayer(userID_1) == false)
                        {
                            // Register the new player and break the loop if the username is unique
                            break;
                        }
                        else
                        {
                            // Notify that the entered username is already in use and prompt to try again
                            cout << "The username you entered is already in use, please try again. \n";
                        }
                    }

                    registerPlayer(userID_1, playerName_1); // Register the new player
                    displayInfo(userID_1);
                    break;
                }
                else
                {
                    // Notify of an invalid option and prompt to try again
                    cout << "Invalid option, please try again.\n";
                }
            }

            //same process for player 2 
            while (true)
            {
                cout << "Player 2: Press 'A' to access your existing account or 'B' to register as a new player: ";
                cin >> playerOption;

                if (playerOption.length() > 1)
                {
                    cout <<"Invalid input. Please try again.\n";
                }
                else if (tolower(playerOption[0] == 'a'))
                {
                    //loop which prompts the user to enter a username until it is found
                    while (true)
                    {
                        cout << "Enter your unique username to access your account: ";
                        cin >> userID_2;
                        if (findPlayer(userID_2) == true)
                        {
                            playerName_2 = displayInfo(userID_2);
                            break; //break the loop if the entered username is found
                        }
                        else
                        {
                            cout << "The username you entered does not exist, please try again. \n";
                        }
                    }
                    break;

                }
                else if (tolower(playerOption[0]) == 'b')
                {
                    cout << "Enter your name: ";
                    cin.ignore(); // Clear the input buffer
                    getline(cin, playerName_2); // Read the entire line for the player's name

                    //loop which prompts the user to enter a username until it is found to be unique
                    while (true)
                    {
                        cout << "Choose a unique username for yourself: ";
                        cin >> userID_2;
                        if (findPlayer(userID_2) == false)
                        {
                            break; //break the loop if the entered username is unique
                        }
                        else
                        {
                            cout << "The username you entered is already in use, please try again. \n";
                        }
                    }

                    registerPlayer(userID_2, playerName_2); //register the new player
                    displayInfo(userID_2);
                    break;

                } else
                {
                    cout << "Invalid option. Please try again/\n";
                }
                
            }
            

            // clearing the screen to start the game
            system("PAUSE");
            system("CLS");

            start(word, hint, playerName_1);
            game(word, hint, playerName_1, playerName_2, userID_1, userID_2);

            //clearing the screen for the 2nd player's turn
            system("PAUSE");
            system("CLS");

            start(word, hint, playerName_2);
            game(word, hint, playerName_2, playerName_1, userID_2, userID_1);

            system("PAUSE");
            system("CLS");
        }

        else if (tolower(modeOption[0] == 'b'))
        {
            // Player vs Computer mode selected
            string playerOption;
            string userID, playerName;

            // Generate a mystery word for the game
            string mysteryWord = generateWord();

            // Measure the length of the generated word using strlen function
            int wordLength = mysteryWord.length();

            // Convert the mystery word to lowercase using tolower built-in function
            // and then assign it to the 'word' array
            for (int i = 0; i < wordLength; ++i) {
                mysteryWord[i] = tolower(mysteryWord[i]);
            }

            // Copy the characters of the mystery word to the 'word' array
            for (int i = 0; i < wordLength; i++)
            {
                word[i] = mysteryWord[i];
            }

            word[wordLength] = '\0'; // Ensure proper null-termination

            // Handle the player's account access or registration
            while (true)
            {
                cout << "Press 'A' to access your existing account or 'B' to register as a new player: ";
                cin >> playerOption;

                // Check if the player is accessing an existing account
                if (playerOption.length() > 1)
                {
                    // Notify of invalid input and prompt to try again
                    cout <<"Invalid input. Please try again.\n";
                }
                else if (tolower(playerOption[0]) == 'a')
                {
                    // Loop to prompt the user to enter a username until it is found
                    while (true)
                    {
                        cout << "Enter your unique username to access your account: ";
                        cin >> userID;
                        // Check if the entered username exists
                        if (findPlayer(userID) == true)
                        {
                            // Display player information and break the loop if the username is found
                            playerName = displayInfo(userID);
                            break;
                        }
                        else
                        {
                            // Notify that the entered username does not exist and prompt to try again
                            cout << "The username you entered does not exist, please try again. \n";
                        }
                    }
                    break;
                }
                else if (tolower(playerOption[0]) == 'b')
                {
                    // Prompt the user to enter their name
                    cout << "Enter your name: ";
                    cin.ignore(); // Clear the input buffer
                    getline(cin, playerName); // Read the entire line for the player's name

                    // Loop to prompt the user to enter a username until it is found to be unique
                    while (true)
                    {
                        cout << "Choose a unique username for yourself: ";
                        cin >> userID;
                        // Check if the entered username is unique
                        if (findPlayer(userID) == false)
                        {
                            // Register the new player and break the loop if the username is unique
                            break;
                        }
                        else
                        {
                            // Notify that the entered username is already in use and prompt to try again
                            cout << "The username you entered is already in use, please try again. \n";
                        }
                    }

                    registerPlayer(userID, playerName); // Register the new player
                    displayInfo(userID);
                    break;
                }
                else {
                    // Notify of invalid input and prompt to try again
                    cout << "Invalid input, please try again.\n";
                }
            }

            system("PAUSE");
            system("CLS");

            // Start the Player vs Computer game
            pcgame(word, playerName, userID);

            system("PAUSE");
            system("CLS");
        }
        else if (tolower(modeOption[0]) == 't')
        {
            // Exit the game if 'T' is chosen
            break;
        }
        else
        {
            // Notify of an invalid option and prompt to try again
            cout << "Invalid option. Please try again\n";
        }
        
        delete[]word;
        delete[]hint;
    }
}



//function to register a new player into the file
void registerPlayer(string ID, string name)
{
    string line = ID + "," + name + ",0,0,"; //will store the line which will be appended to the text file, each value is seperated by a comma

    fstream playerRegister("PlayerRegister.txt", ios::app); //open the text file in append mode

    if (playerRegister.is_open()) //if the file was opened successfully
    {
        playerRegister << line << "\n"; //append the line to the text file
        cout << "Player registered successfully!\n"; //output a statement indicating whether the program was successful or not
    }
    else
    {
        cout << "Unable to register player due to some error!\n";
    }

    playerRegister.close(); //close the text file

}


//function to check if an ID that a user has entered is unique
bool findPlayer(string newID)
{

    bool found = false; // The return variable is initially set to false 
    string line; // Will store each line from the text file


    fstream playerRegister("PlayerRegister.txt", ios::in); //open the text file in read mode

    if (playerRegister.is_open()) //used to check if the file was opened successfully
    {

        // conditional loop which is running while there are lines left in the text file and the ID has not been found
        while (getline(playerRegister, line) && found == false)
        {

            string existingID = ""; // will store the ID that has been extracted from each line
            int i = 0; //used to iterate through the string in each line of the file


            //loop to iterate through the current line and extract the ID
            while (line[i] != ',')
            {
                existingID += line[i];
                i++;
            }

            //if the ID in the line matches the ID that the new user entered set found to true
            if (existingID == newID)
            {
                found = true;
                break;
            }

        }

    }
    else //if there was an error in opening the file
    {
        cout << "File was not opened due to some error.";
    }

    playerRegister.close(); //close the text file

    return found;

}


//function to display a user's info using ther ID as a parameter
string displayInfo(string ID)
{

    bool found = false; // The return variable is   initially set to false 
    string line; // Will store each line from the text file
    string name = "";
    string wins = "";
    string losses = "";



    fstream playerRegister("PlayerRegister.txt", ios::in); //open the text file in read mode

    if (playerRegister.is_open()) //used to check if the file was opened successfully
    {

        // conditional loop which is running while there are lines left in the text file and the ID has not been found
        while (getline(playerRegister, line) && found == false)
        {

            string existingID = ""; // will store the ID that has been extracted from each line
            int i = 0; //used to iterate through the string in each line of the file


            //loop to iterate through the current line and extract the ID
            while (line[i] != ',')
            {
                existingID += line[i];
                i++;
            }

            //if the ID in the line matches the ID that the new user entered set found to true
            if (existingID == ID)
            {
                found = true;
                i++;
            }

            if (found == true) //if the ID has been found then
            {
                while (line[i] != ',')
                {
                    name += line[i];  //extract the player's name from the line
                    i++;
                }

                i++;

                while (line[i] != ',')
                {
                    wins += line[i];  //extract the player's wins from the line
                    i++;
                }

                i++;

                while (line[i] != ',')
                {
                    losses += line[i]; // extract the player's losses from the line
                    i++;
                }

                cout << "Welcome " << name << " Your current record is: " << wins << " wins and " << losses << " losses \n";  // display the player's info
            }


        }

    }
    else //if there was an error in opening the file
    {
        cout << "File was not opened due to some error.";
    }

    playerRegister.close(); //close the text file

    return name;



}

//function to add a win to a person's record
void addWin(string userID)
{
    string line; // Will store each line from the text file


    fstream playerRegister("PlayerRegister.txt", ios::in); //open the text file in read mode
    fstream temporary("temporaryfile.txt", ios::app); //open a temporary file to append the existing text file into with the necessary changes

    if (playerRegister.is_open() && temporary.is_open()) //used to check if the file was opened successfully
    {

        // conditional loop which is running while there are lines left in the text file and the ID has not been found
        while (getline(playerRegister, line))
        {

            string existingID = ""; // will store the ID that has been extracted from each line
            string existingName = "";
            string existingWins = "";
            string existingLosses = "";
            int i = 0; //used to iterate through the string in each line of the file


            //loops to iterate through the current line and extract the ID, name, wins and losses from the text file

            while (line[i] != ',')
            {
                existingID += line[i]; //extracting the ID
                i++;
            }

            i++;

            while (line[i] != ',')
            {
                existingName += line[i]; //extracting the name
                i++;
            }

            i++;

            while (line[i] != ',')
            {
                existingWins += line[i]; //extracting the wins
                i++;
            }

            i++;

            while (line[i] != ',')
            {
                existingLosses += line[i]; //extracting the losses
                i++;
            }


            //if the ID in the line matches the ID that the new user entered set found to true
            if (existingID == userID)
            {
                int temp = stoi(existingWins) + 1;
                existingWins = to_string(temp);    //change the person's wins to increment by 1
                cout << "Congratulations " << existingName << " Your record is now " << existingWins << " wins and " << existingLosses << " losses\n";
            }

            //append the lines to the new text file

            line = existingID + ',' + existingName + ',' + existingWins + ',' + existingLosses + ',';
            temporary << line << "\n";

        }

    }
    else //if there was an error in opening the file
    {
        cout << "File was not opened due to some error.";
    }

    playerRegister.close(); //close the text file
    temporary.close();

    std::remove("PlayerRegister.txt"); //delete the old text file
    std::rename("temporaryfile.txt", "PlayerRegister.txt"); //rename the new textfile back to the original textfile's name


}


//function to add a loss to a person's record
void addLoss(string userID)
{
    string line; // Will store each line from the text file


    fstream playerRegister("PlayerRegister.txt", ios::in); //open the text file in read mode
    fstream temporary("temporaryfile.txt", ios::app); //open a temporary file to append the existing text file into with the necessary changes

    if (playerRegister.is_open() && temporary.is_open()) //used to check if the file was opened successfully
    {

        // conditional loop which is running while there are lines left in the text file and the ID has not been found
        while (getline(playerRegister, line))
        {

            string existingID = ""; // will store the ID that has been extracted from each line
            string existingName = "";
            string existingWins = "";
            string existingLosses = "";
            int i = 0; //used to iterate through the string in each line of the file


            //loops to iterate through the current line and extract the ID, name, wins and losses from the text file

            while (line[i] != ',')
            {
                existingID += line[i]; //extracting the ID
                i++;
            }

            i++;

            while (line[i] != ',')
            {
                existingName += line[i]; //extracting the name
                i++;
            }

            i++;

            while (line[i] != ',')
            {
                existingWins += line[i]; //extracting the wins
                i++;
            }

            i++;

            while (line[i] != ',')
            {
                existingLosses += line[i]; //extracting the losses
                i++;
            }


            //if the ID in the line matches the ID that the new user entered set found to true
            if (existingID == userID)
            {
                int temp = stoi(existingLosses) + 1;
                existingLosses = to_string(temp);    //change the person's losses to increment by 1
                cout << "Commiserations " << existingName << " Your record is now " << existingWins << " wins and " << existingLosses << " losses\n";
            }

            //append the lines to the new text file

            line = existingID + ',' + existingName + ',' + existingWins + ',' + existingLosses + ',';
            temporary << line << "\n";

        }

    }
    else //if there was an error in opening the file
    {
        cout << "File was not opened due to some error.";
    }

    playerRegister.close(); //close the text file
    temporary.close();

    std::remove("PlayerRegister.txt"); //delete the old text file
    std::rename("temporaryfile.txt", "PlayerRegister.txt"); //rename the new textfile back to the original textfile's name

}




//start function to start the game
void start(char word[], char hint[], string playerName_1) {
    const int word_length_max = 1000;
    const int attempts = 6;

    cout << "\t\t\t\t\t+-------------------------------+" << endl;
    cout << "\t\t\t\t\t| PLAYER Vs PLAYER HANGMAN GAME |" << endl;
    cout << "\t\t\t\t\t+-------------------------------+" << endl << endl;
    //giving the player the instrurctions
    cout << "Instructions:" << endl;
    cout << "1. Save a man from being hanged by guessing the letters in the word." << endl;
    cout << "2. The second player will guess the word given by the first player using the hint." << endl;
    cout << "3. Be careful; you only have " << attempts << " attempts." << endl << endl;
    //taking input of the player for the start of the example
    cout << "***" << playerName_1 << "'s turn***" << endl;
    cout << "Please enter a word/sentence for your opponent to guess: ";
    //using getline function to get input
    cin.ignore();
    cin.getline(word, word_length_max);
    //using strlen function to measure the length of the word entered
    int wordLength = strlen(word);
    // Converting the word to lowercase using tolower builtin function and then printing it
    for (int i = 0; i < wordLength; ++i) {
        word[i] = tolower(word[i]);
    }
    //asking the first player to enter hint for the second player using getline function
    cout << "Also enter a hint for the second player: ";
    //asking the first player to enter hint for the second player using getline function
    cin.getline(hint, word_length_max);
    //pausing and clearing the screen for the second player to start the game
    system("PAUSE");
    system("CLS");
}


// The game function
void game(const char word[], const char hint[], string playerName_1, string playerName_2, string userID_1, string userID_2) {
    int attempts = 6;
    cout << "\t\t\t\t\t+-------------------------------+" << endl;
    cout << "\t\t\t\t\t| PLAYER Vs PLAYER HANGMAN GAME |" << endl;
    cout << "\t\t\t\t\t+-------------------------------+" << endl << endl;
    cout << "\nWelcome to Hangman game" << endl;

    // now second player's turn to guess the letters
    cout << "\n***" << playerName_2 << "'s turn ***" << endl;
    cout << "\nThe hint is: " << hint << endl;

    int wordLength = strlen(word);

    // dynamically allocating an array for the guessed letters
    bool* guessedLetters = new bool[wordLength] {};

    int attemptsLeft = attempts;

    // Initialize allGuessed to false
    bool allGuessed = false;

    // Loop until attempts run out or the word is guessed
    while (attemptsLeft > 0 && !allGuessed) {
        // calling the functions draw hangman and displaying the word
        hangmanStatus(attemptsLeft);
        display_word(word, guessedLetters);

        // taking input for the guess
        char guess;
        cout << "\nEnter a letter: ";
        input: cin >> guess;
        try {
            if (isalpha(guess)) {
                cout  << endl;
            }
            else
                throw 403;
        }
        catch (...) {
            cout << "Enter an alphabet or a digit:" << endl;
            goto input;
        }
        // converting the letters to lowercase
        guess = tolower(guess);
       
        // checking if the guessed letter is in the word or not
        bool letterGuessed = false;
        for (int i = 0; i < wordLength; ++i) {
            if (word[i] == guess && !guessedLetters[i]) {
                // printing all the correct letters
                guessedLetters[i] = true;
                letterGuessed = true;
            }
        }

        // decrement attempts only if the letter is not guessed
        if (!letterGuessed) {
            --attemptsLeft;
            cout << "\nOOPS! That is incorrect!" << endl;
            cout << "You have " << attemptsLeft << " attempts left." << endl;
        }

        // Check if all letters have been guessed
        allGuessed = true;
        for (int i = 0; i < wordLength; ++i) {
            if (!guessedLetters[i] && isalpha(word[i])) {
                allGuessed = false;
                break;  // No need to continue checking if one letter is not guessed
            }
        }
    }

    // clear the system
    system("CLS");

    // if all letters are guessed then print the message that 2P has won and also display the word
    if (allGuessed) {
        display_word(word, guessedLetters);
        cout << "YAYY!!THE MAN HAS BEEN SAVED!!\nA WIN HAS BEEN ADDED TO YOUR RECORD\n";
        addWin(userID_2);
        cout << endl;
    }
    else {
        //if all letters are not guessed then display the correct word and also draw hangman
        hangmanStatus(attemptsLeft);
        cout << "\nWhoops! Sorry you ran out of attempts. The man has been hanged.\nA loss has been added to your record\n";
        addLoss(userID_2);
        cout << "\nThe correct word/sentence was: ";
        //calling the reveal function
        reveal(word, wordLength);

    }
    // deleting the memory allocated to the guessed letter array
    delete[] guessedLetters;
}

//writing the function to check if all the letters have been guessed 
bool all_letters_guessed(const bool guessed[], int len) {
    for (int i = 0; i < len; ++i) {
        // If any element is false that indicates that the corresponding letter has not been guessed
        if (!guessed[i]) {
            return false;
        }
    }
    // If the loop completes without returning false, it means all letters have been guessed.
    return true;
}

void hangmanStatus(int livesLeft) { // Function to output the current state of the hangman to the player

    cout << "\nYou have " << livesLeft << " lives left." << endl;

    switch (livesLeft) {

    case 6: // When the player has six lives left

        cout << "  _______  " << endl;
        cout << "  |     |  " << endl;
        cout << "  |        " << endl;
        cout << "  |        " << endl;
        cout << "  |        " << endl;
        cout << "  |        " << endl;
        cout << "__|________" << endl << endl;
        cout << "=============================================================================" << endl << endl;

        break;

    case 5: // When the player has five lives left

        cout << "  _______  " << endl;
        cout << "  |     |  " << endl;
        cout << "  |     O  " << endl;
        cout << "  |        " << endl;
        cout << "  |        " << endl;
        cout << "  |        " << endl;
        cout << "__|________" << endl << endl;
        cout << "=============================================================================" << endl << endl;

        break;

    case 4: // When the player has four lives left

        cout << "  _______  " << endl;
        cout << "  |     |  " << endl;
        cout << "  |     O  " << endl;
        cout << "  |     |  " << endl;
        cout << "  |        " << endl;
        cout << "  |        " << endl;
        cout << "__|________" << endl << endl;
        cout << "=============================================================================" << endl << endl;

        break;

    case 3: // When the player has three lives left

        cout << "  _______  " << endl;
        cout << "  |     |  " << endl;
        cout << "  |     O  " << endl;
        cout << "  |    /|  " << endl;
        cout << "  |        " << endl;
        cout << "  |        " << endl;
        cout << "__|________" << endl << endl;
        cout << "=============================================================================" << endl << endl;

        break;

    case 2: // When the player has two lives left

        cout << "  _______  " << endl;
        cout << "  |     |  " << endl;
        cout << "  |     O  " << endl;
        cout << "  |    /|\\ " << endl;
        cout << "  |        " << endl;
        cout << "  |        " << endl;
        cout << "__|________" << endl << endl;
        cout << "=============================================================================" << endl << endl;

        break;

    case 1: // When the player has one life left

        cout << "  _______  " << endl;
        cout << "  |     |  " << endl;
        cout << "  |     O  " << endl;
        cout << "  |    /|\\ " << endl;
        cout << "  |    /   " << endl;
        cout << "  |        " << endl;
        cout << "__|________" << endl << endl;
        cout << "=============================================================================" << endl << endl;

        break;

    case 0: // When the player loses

        cout << "  _______  " << endl;
        cout << "  |     |  " << endl;
        cout << "  |     X  " << endl;
        cout << "  |    /|\\ " << endl;
        cout << "  |    / \\  " << endl;
        cout << "  |        " << endl;
        cout << "__|________" << endl << endl;
        cout << "=============================================================================" << endl << endl;

        break;
    }

}


void display_word(const char word[], const bool guessed[]) {
    //using strlen function to measure the length of the word guessed by the 2nd player
    int len = strlen(word);
    for (int i = 0; i < len; ++i) {
        //print the letter if the letter is in the word 
        if (guessed[i]) {
            cout << word[i] << " ";
        }
        else if (word[i] == ' ')
        {
            cout << " ";
        }
        //otherwise print a dash
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}


//the reveal function that uses pointers to access the characters of the array 
void reveal(const char word[], int len) {
    // Assigning a pointer to the start of the array
    const char* ptr = word;
    // Traversing the array using the pointer to print each character
    for (int i = 0; i < len; i++) {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
}


void pcgame(const char word[], string playerName, string userID) {

    const int attempts = 6;
    cout << "\t\t\t\t\t+-------------------------------+" << endl;
    cout << "\t\t\t\t\t|   PLAYER Vs CPU HANGMAN GAME  |" << endl;
    cout << "\t\t\t\t\t+-------------------------------+" << endl << endl;
    //now second player's turn to guess the letters
    cout << "\n***" << playerName << "'s turn***" << endl;
    int wordLength = strlen(word);
    //dynamically allocatig an array for the guessed letters
    bool* guessedLetters = new bool[wordLength] {};
    int attemptsLeft = attempts;
    //if all there are atempts left and all letters have not been guessed then display the letters gussed and the draw hangman accordingly
    while (attemptsLeft > 0 && !all_letters_guessed(guessedLetters, wordLength)) {
        //calling the functions draw hangman and sisplaying the word
        hangmanStatus(attemptsLeft);
        display_word(word, guessedLetters);
        //taking input for the guess
        char guess;
        cout << "\nEnter a letter: ";
        input: cin >> guess;
        try {
            if (isalpha(guess)) {
                cout << endl;
            }
            else
                throw 403;
        }
        catch (...) {
            cout << "Enter an alphabet or a digit:" << endl;
            goto input;
        }
        //converting the letters to lowecase
        guess = tolower(guess);
        //to check if the letter is guessed or not 
        bool letterGuessed = false;
        //checking if the guessed letter is in the the word or not
        for (int i = 0; i < wordLength; ++i) {
            if (word[i] == guess) {
                //printing all the correct letters
                guessedLetters[i] = true;
                letterGuessed = true;
            }
        }
        //if letter is not guessed then decrement the number of attempts left
        if (!letterGuessed) {
            --attemptsLeft;
            cout << "\nOOPS! That is incorrect!" << endl;
        }
    }
    //clear the system 
    system("CLS");
    //if all letters are guessed then print the message that 2P has won and also display the woed
    if (all_letters_guessed(guessedLetters, wordLength)) {
        display_word(word, guessedLetters);
        cout << "YAYY!! THE MAN HAS BEEN SAVED!!\n A WIN HAS BEEN ADDED TO YOUR RECORD\n";
        addWin(userID);
    }
    else {
        //if all letters are not guessed then display the correct word and also draw hangman
        hangmanStatus(attemptsLeft);
        cout << "\nWhoops! Sorry you ran out of attempts. The man has been hanged." << endl;
        addLoss(userID);
        cout << "\nThe correct word/sentence was: ";
        //calling the reveal function
        reveal(word, wordLength);

    }
    //deleting the memory allocated to the guessed letter array
    delete[] guessedLetters;
}


string generateWord() { // Function to choose the word to play the game with

    srand(time(0)); // So the word chosen is not the same each time

    string wordsList[] = { "algorithm", "intelligence", "data", "cloud", "computing", "clustering", "computer", "cybersecurity", "database", "learning", "desktop",
    "digital", "entropy", "error", "ethernet", "firewall", "graphics", "drive", "hyperlink", "java", "kernel", "laptop", "machine", "neural", "network",
    "operating", "packet", "programming", "query", "regression", "robotics", "sensor", "server", "software", "spreadsheet", "supercomputer", "tablet", "training",
    "interface", "virtual", "aggregation", "bias", "calibration", "mining", "engineering", "generalization", "hypothesis", "inference", "language",
    "outlier", "overfitting", "precision", "recall", "regularization", "sampling", "analysis", "visualization", "scraping", "coding", "authentication", "authorization",
    "caching", "storage", "container", "infrastructure", "microservices", "scalability", "version", "development", "governance", "ethics", "fairness", "privacy",
    "reproducibility", "transparency", "detection", "security", "encryption", "anonymization", "pipeline", "tensor", "python", "binary", "insight", "decision",
    "prediction", "optimization", "automation", "business", "transformation", "finance", "marketing", "healthcare", "retail", "transportation", "smart",
    "future", "emerging", "quantum", "blockchain" };
    // List of words

    string word = wordsList[rand() % 100]; // Picking a random word from the list

    return word; // Ending the generateWord() function by returning the random word
}