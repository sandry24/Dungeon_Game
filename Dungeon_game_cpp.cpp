#include <bits/stdc++.h>
 
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
#define pb push_back
#define mp make_pair

std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
std::uniform_int_distribution<> monst{1, 5};
std::uniform_int_distribution<> chance{1, 2};
std::uniform_int_distribution<> chance2{1, 5};
std::uniform_int_distribution<> chance3{1, 5};
std::uniform_int_distribution<> critical_chance{1, 10};

string return_Potion(int x){
    switch(x){
        case 1 : return "Health";break;
        case 2 : return "Gold";break;
        case 3 : return "Strength"; break;
        case 4 : return "Neutral"; break;
        case 5 : return "Poison"; break;
    }     
}

int return_Gold(int x){
    switch(x){
        case 1 : return 5;break;
        case 2 : return 10;break;
        case 3 : return 15; break;
        case 4 : return 25; break;
        case 5 : return 50; break;
    }   
}

int return_Attack(int x){
    switch(x){
        case 1 : return 1;break;
        case 2 : return 3;break;
        case 3 : return 7; break;
        case 4 : return 10; break;
        case 5 : return 12; break;
    }     
}

int return_Health(int x){
    switch(x){
        case 1 : return 3;break;
        case 2 : return 5;break;
        case 3 : return 10; break;
        case 4 : return 12; break;
        case 5 : return 20; break;
    }    
}

string return_Monster(int x){
    switch(x){
        case 1 : return "Slime";break;
        case 2 : return "Zombie";break;
        case 3 : return "Skeleton"; break;
        case 4 : return "Vampire"; break;
        case 5 : return "Dragon"; break;
    }
}

bool continue_game(){
    char ans;
    cout << "Press 'Y' to start a new game, press 'N' to return.\n";
    cin >> ans;
    if(ans == 'Y')
        return true;
    else
        return false;
}

bool next_Attack(){
    char ans;
    cout << "Press 'A' to attack the monster, press 'R' to run away.\n";
    cin >> ans;
    if(ans == 'A')
        return true;
    else
        return false;
}

void player_Died(int x){
    cout << "You died with " << x << " gold.\n";
}

void solve(){
    bool play = continue_game();
    while(play){
        int health = 100, attack_power = 3, gold = 0, total_killed = 0, attack_power_potions = 0;
        cout << '\n' << "You have " << health << " HP, " << attack_power << " AP and " << gold << " gold.\n";
        while(health > 0){
            cout << '\n';
            int potion_chance = chance2(mersenne);
            if(potion_chance == 2){
                int potion_type = chance3(mersenne);
                cout << "You have found a mysterious potion.\n";
                cout << "Press 'D' to drink it, 'T' to throw it.\n";
                char drink;
                cin >> drink;
                if(drink == 'T'){
                    cout << "You threw away the potion.\n";
                } else {
                    cout << "You drank the potion.\n";
                    cout << "It was a " << return_Potion(potion_type) << " potion.\n";
                    if(potion_type == 1){
                        cout << "Your health was increased by 10 HP.\n";
                        health += 10;
                        cout << "You now have " << health << " HP.\n";
                    } else if(potion_type == 2){
                        cout << "You have received 25 gold.\n";
                        gold += 25;
                        cout << "You now have " << gold << " gold.\n";
                    } else if(potion_type == 3){
                        cout << "Your attack power was increased by 1.\n";
                        attack_power_potions++;
                        attack_power++;
                        cout << "You now have " << attack_power << " AP.\n";
                    } else if(potion_type == 4){
                        cout << "Nothing happened.\n";
                    } else {
                        cout << "You lost 5 HP.\n";
                        health -= 5;
                        cout << "You now have " << max(0, health) << " HP.\n";
                        if(health <= 0){
                            cout << '\n';
                            cout << "You have died with " << gold << " gold.\n";
                            cout << '\n';
                            cout << "GAME OVER\n" << '\n';
                            break;
                        }
                    }
                }
                cout << '\n';
            }
            int root = monst(mersenne);
            string monster = return_Monster(root); int monster_health = return_Health(root); int monster_attack = return_Attack(root); int monster_gold = return_Gold(root);
            cout << "You encountered a " << monster << " with " << monster_health << " HP and " << monster_attack << " AP.\n";
            bool attack = next_Attack();
            while(attack){
                cout << '\n';
                int critical = critical_chance(mersenne);
                if(critical != 5){
                    cout << "You hit the monster for " << attack_power << " damage.\n";
                    monster_health -= attack_power;
                } else {
                    cout << "CRITICAL HIT!\n";
                    cout << "You hit the monster for " << attack_power*2 << " damage.\n";
                    monster_health -= attack_power*2;
                }
                if(monster_health <= 0){
                    cout << "You have defeated the monster and have received " << monster_gold << " gold.\n";
                    total_killed++;
                    gold += monster_gold;
                    break;
                }
                cout << "The monster now has " << monster_health << " HP.\n";
                cout << "The monster has hit you for " << monster_attack << " damage.\n";
                health -= monster_attack;
                if(health <= 0){
                    break;
                }
                cout << "You now have " << health << " HP.\n";
                attack = next_Attack();
            }
            if(!attack){
                int fled = chance(mersenne);
                if(fled == 1){
                    cout << "You successfully ran away.\n";
                } else {
                    cout << "You ran away, but the monster hit you for " << monster_attack << " damage.\n";
                    health -= monster_attack;
                }
            }
            int last_ap = attack_power;
            attack_power = 3 + (total_killed / 3) + attack_power_potions;
            if(attack_power != last_ap){
                cout << '\n';
                cout << "Your attack power was increased by 1.\n";
            }
            if(health > 0)
                cout << "You now have: " << max(0, health) << " HP, " << attack_power << " AP and " << gold << " gold.\n";
            else {
                cout << '\n';
                cout << "You have died with " << gold << " gold.\n";
                cout << '\n';
                cout << "GAME OVER\n" << '\n';
            }
        }
        cout << '\n';
        play = continue_game();
    }
    if(!play){
        cout << "Goodbye\n";
        return;
    }
}

int main()
{   
    //ios::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}