#include <bits/stdc++.h>
using namespace std;

// *********************************************************************************************************************
// Problem 3 A *********************************************************************************************************
// *********************************************************************************************************************

template <typename t>
struct slNode {
    t key;
    vector<slNode<t>*> next;

    slNode(t key = t()) : key(key) {}
//    slNode() {}
};

template <typename t>
class skipList {
protected:
    slNode<t>* head;
    slNode<t>* tail;
    int level;

    bool ascend() {
        return rand() % 2 == 0;
    }

    void createLevel() {
        head->next.push_back(tail);
        tail->next.push_back(nullptr);
        level++;
    }
public:
    skipList() {
        head = new slNode<t>();
        tail = new slNode<t>();
        head->next.push_back(tail);
        tail->next.push_back(nullptr);
        level = 0;
        srand(time(nullptr));
    }

    void insert(t key) {
        slNode<t>* node = head;
        slNode<t>* dataArr[level + 1];
        int i = level;
        while ( i >=0 ) {
            if (node->next[i]!=tail && node->next[i]->key < key) {
                node = node->next[i];
            } else {
                dataArr[i] = node;
                i--;
            }
        }

        i = 0;
        slNode<t>* keynode = new slNode<t>(key);
        keynode->next.push_back(dataArr[0]->next[0]);
        dataArr[0]->next[0] = keynode;

        while (ascend()) {
            i++;
            if (i>level) {
                createLevel();
                keynode->next.push_back(head->next[i]);
                head->next[i] = keynode;
            } else {
                keynode->next.push_back(dataArr[i]->next[i]);
                dataArr[i]->next[i] = keynode;
            }
        }
    }

    slNode<t>* search(t key) {
        slNode<t>* node = head;
        int i = level;

        while (i >= 0) {
            while (node->next[i]!=tail && node->next[i]->key < key) {
                node = node->next[i];
            }
            if (node->next[i] != nullptr && node->next[i]->key == key) {
                return node->next[i];
            }
            i--;
        }
        return nullptr;
    }

    void remove(t key) {
        slNode<t>* node = head;
        slNode<t>* dataArr[level + 1];
        int i = level;
        bool found = false;

        while ( i >=0 ) {
            while (node->next[i]!=tail && node->next[i]->key < key) {
                node = node->next[i];
            }
            if (node->next[i]!=tail && node->next[i]->key == key) {
                dataArr[i] = node;
                found = true;
            } else {
                dataArr[i] = nullptr;
            }
            i--;
        }

        if (!found) { cout<<"Key not found"; return;}

        i = 0;
        slNode<t>* target = nullptr;
        while (i <= level) {
            if (dataArr[i] != nullptr) {
                target = dataArr[i]->next[i];
                dataArr[i]->next[i] = target->next[i];
            }
            i++;
        }

        while (level>=1 && head->next[level] == tail) {
            tail->next.pop_back();
            head->next.pop_back();
            level--;
        }

        delete target;
    }

    // Print Values In Every Level To Observe The Structure
    void printSkipList() {
        for (int i = level; i >= 0; i--) {
            slNode<t>* node = head->next[i];
            cout << "Level " << i << ": -inf -> ";
            while (node != tail) {
                cout << node->key << " -> ";
                node = node->next[i];
            }
            cout << "+inf\n";
        }
    }

    // Print Values In Data Structure
    void print() {
        slNode<t>* node = head->next[0];
        cout << "Values: -inf -> ";
        while (node != tail) {
            cout << node->key << " -> ";
            node = node->next[0];
        }
        cout << "+inf\n";
    }
};

// *********************************************************************************************************************
// Problem 3 B *********************************************************************************************************
// *********************************************************************************************************************

template <typename t>
class gameSkipList : public skipList<t> {
public:
    vector<t> getPlayers() {
        vector<t> scores;
        slNode<t>* node = this->head->next[0];
        while (node != this->tail) {
            scores.push_back(node->key);
            node = node->next[0];
        }
        return scores;
    }
};

struct player {
    string name;
    int score;

    player() {}
    player(string name, int score) : name(name), score(score) {}

    bool operator<(const player& other) const {
        return score < other.score;
    }

    bool operator>(const player& other) const {
        return score > other.score;
    }

    bool operator==(const player& other) const {
        return name == other.name;
    }

    friend ostream& operator<<(ostream& os, const player& p) {
        os << "Name: " << p.name << ", Score: " << p.score;
        return os;
    }
};

class leaderBoard {
    gameSkipList<player> gsl;
public:

    leaderBoard() : gsl() {}

    void addPlayer(player& p) {
        if (gsl.search(p)) {
            cout<<"Player Name Already Exists!\n";
            return;
        }
        gsl.insert(p);
    }

    void removePlayer(player& p) {
        gsl.remove(p);
    }

    void updatePlayer(player& p, int score) {
        gsl.remove(p);
        p.score=score;
        gsl.insert(p);
    }

    void getTopN(int n) {
        vector<player> players = gsl.getPlayers();

        if (0 > players.size() - n) { n= players.size(); }
        else { n = players.size() - n; }

        for (int i = players.size()-1 ; i>= n ; i--){
            cout<<players[i]<<endl;
        }
    }

    void printDS() {gsl.printSkipList();}

    void print() {
        vector<player> players = gsl.getPlayers();
        for (int i = players.size()-1 ; i>= 0 ; i--){
            cout<<players[i]<<endl;
        }
    }
};

// *********************************************************************************************************************
// Main ****************************************************************************************************************
// *********************************************************************************************************************

/* Main For 3A */
//int main() {
//    skipList<int> sl;
//
//    sl.insert(5);
//    sl.insert(10);
//    sl.insert(15);
//    sl.insert(20);
//    sl.insert(25);
//
//    if (sl.search(15)) {
//        std::cout << "15 found in the skiplist.\n";
//    } else {
//        std::cout << "15 not found in the skiplist.\n";
//    }
//
//    if (sl.search(30)) {
//        std::cout << "30 found in the skiplist.\n";
//    } else {
//        std::cout << "30 not found in the skiplist.\n";
//    }
//
//    cout<<"\n";
//    sl.print();
//    cout<<"\n";
//    sl.printSkipList();
//    cout<<"\n";
//
//
//    sl.remove(15);
//
//    if (sl.search(15)) {
//        std::cout << "15 still in the skiplist after removal (error).\n";
//    } else {
//        std::cout << "15 successfully removed from the skiplist.\n";
//    }
//
//    sl.remove(30);
//
//    cout<<"\n";
//    sl.print();
//    cout<<"\n";
//    sl.printSkipList();
//    cout<<"\n";
//
//    return 0;
//}

/* Main For 3B */
int main() {
    leaderBoard lb;

    player alice = player("Alice", 100);
    player bob = player("Bob", 200);
    player charlie = player("Charlie", 150);
    player dave = player("Dave", 120);

    lb.addPlayer(alice);
    lb.addPlayer(bob);
    lb.addPlayer(charlie);
    lb.addPlayer(dave);

    lb.printDS();
    lb.print();

    cout << "\nUpdating Bob's score to 130...\n";
    lb.updatePlayer(bob,130);

    cout << "Updated leaderboard:\n";
    lb.printDS();
    lb.print();

    cout << "\nRemoving Charlie from the leaderboard...\n";
    lb.removePlayer(charlie);

    cout << "Leaderboard after removal:\n";
    lb.printDS();
    lb.print();

    cout << "\nTop 2 players:\n";
    lb.getTopN(2);

    return 0;
}
