#include "main.h"

void setupPlayerStats(string &name, int &str, int &def, int &armor, int &skill, int &wins, int &Losses);
void savePlayerStats(string name, int str, int def, int armor, int skill, int wins, int Losses);

int main() {
  random_device rd;
  uniform_int_distribution<int>d6(1,6);

  string p1Name;
  int p1Str;
  int p1Def;
  int p1Armor;
  int p1Skill;
  int p1Wins;
  int p1Losses;

  string p2Name;
  int p2Str;
  int p2Def;
  int p2Armor;
  int p2Skill;
  int p2Wins;
  int p2Losses;  

  cout << "SETTING UP PLAYER1..." << endl << "✦" << endl;
  setupPlayerStats(p1Name, p1Str, p1Def, p1Armor, p1Skill, p1Wins, p1Losses);

  cout << "SETTING UP PLAYER2..." << endl << "✧" << endl;
  setupPlayerStats(p2Name, p2Str, p2Def, p2Armor, p2Skill, p2Wins, p2Losses);

  int p1Health = rd() % 20 + 1;
  int p2Health = rd() % 20 + 1;
  int turns = 0;

  cout << endl << "TIME FOR THE FIGHT!" << endl;
  cout << "Introducing the challengers...\n✦ " << p1Name << ": " << p1Wins << " Wins, " << p1Losses << " Losses\n✧ " << p2Name << ": " << p2Wins << " Wins, " << p2Losses << " Losses" << endl;

  while (p1Health > 0 && p2Health > 0 && turns < 100){
    int attackRoll;
    int damageRoll;

    cout << "BEGIN ROUND" << turns+1 << endl;

    attackRoll = p1Skill + d6(rd);
    if (attackRoll > 3 + p2Def){
      cout << p1Name << " hits " << p2Name << "..." << endl;
      damageRoll = p1Str + d6(rd) - p2Armor;
      if (damageRoll > 0){
        p2Health -=  damageRoll;
        cout << "..." << p2Name << " takes " << damageRoll << " damage!" << endl;
      }
      else {
        cout << "..." << p2Name << "'s armor blocks all the damage!" << endl;
      }
    }
    else{
      cout << p1Name << " swings at " << p2Name << "..." << endl;
      cout << "..." << p2Name << "'s defense blocks all hits!" << endl;
    }
    cout << "Round Results..." << endl;
    cout << "✦ " << p1Name << "'s Health: " << p1Health << endl;
    cout << "✧ " << p2Name << "'s Health: " << p2Health << endl;
    turns ++;

    attackRoll = p2Skill + d6(rd);
    if (attackRoll > 3 + p1Def){
      cout << p2Name << " hits " << p1Name << "..." << endl;
      damageRoll = p2Str + d6(rd) - p1Armor;
      if (damageRoll > 0){
        p1Health -=  damageRoll;
        cout << "..." << p1Name << " takes " << damageRoll << " damage!" << endl;
      }
      else {
        cout << "..." << p1Name << "'s armor blocks all the damage!" << endl;
      }
    }
    else{
      cout << p2Name << " swings at " << p1Name << "..." << endl;
      cout << "..." << p1Name << "'s defense blocks all hits!" << endl;
    }
    cout << "Round Results..." << endl;
    cout << "✦ " << p1Name << "'s Health: " << p1Health << endl;
    cout << "✧ " << p2Name << "'s Health: " << p2Health << endl;
    turns ++;
  }
  if (p1Health == p2Health){
    cout << " The Results are in..." << endl;
    cout << "... the fight ended on a draw! Both opponents had " << p1Health << " health!" << endl;
  }
  else if (p1Health > p2Health){
    cout << " The Results are in..." << endl;
    cout << "...Congrats " << p1Name << " you won! Better luck next time " << p2Name << " !" << endl;
    p1Wins ++;
    p2Losses ++;
  }
  else{
    cout << " The Results are in..." << endl;
    cout << "...Congrats " << p2Name << " you won! Better luck next time " << p1Name << " !" << endl;
    p2Wins ++;
    p1Losses ++;
  }
  savePlayerStats(p1Name, p1Str, p1Def, p1Armor, p1Skill, p1Wins, p1Losses);
  savePlayerStats(p2Name, p2Str, p2Def, p2Armor, p2Skill, p2Wins, p2Losses);
}

void setupPlayerStats(string &name, int &str, int &def, int &armor, int &skill, int &wins, int &losses) {
  fstream file;

  cout << "Name: ";
  getline(cin, name);
  if (name == ""){
    name = "No Name";
  }

  string filename = name + ".txt";
  file.open(filename, ios::in);
  if (file.is_open()){
    file >> str;
    file >> def;
    file >> armor;
    file >> skill;
    file >> wins;
    file >> losses;

    file.close();
  }
  else{
    bool accepted = false;
    while (accepted == false){
      int points = 20;
      cout << "You have " << points << " points to assign to your character stats." << endl;
      cout << "Stats include strength, defense, armor & skill." << endl;

      cout << "• Strength: ";
      cin >> str;
      points -= str;
      cout << "You have " << points << " remaining." << endl;

      cout << "• Defence: ";
      cin >> def;
      points -= def;
      cout << "You have " << points << " remaining." << endl;

      cout << "• Armor: ";
      cin >> armor;
      points -= armor;
      cout << "You have " << points << " remaining." << endl;

      cout << "• Skill: ";
      cin >> skill;
      points -= skill;
      cout << " You have " << points << " remaining." << endl;
      cin.ignore();

      wins = 0;

      if (points >= 0){
        cout << "The entered stats have been accpeted. " << name << " is being created!" << endl;
        accepted = true;
      }
      else{
        cout << "Sorry, you've exceeded the points limit." << endl;
        cout << "Try again..." << endl;
      }
    }
  }
}

void savePlayerStats(string name, int str, int def, int armor, int skill, int wins, int losses) {
  fstream file;

  string filename = name + ".txt";
  file.open(filename, ios::out);

  file << str << endl;
  file << def << endl;
  file << armor << endl;
  file << skill << endl;
  file << wins << endl;
  file << losses << endl;

  file.close();
}
