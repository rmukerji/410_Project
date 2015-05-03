#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Node {
    public:
        Node() 
        {  
            node_char = '\0'; 
            end_word = false; 
            for(int i = 0; i < 26; i++)
                children.push_back(NULL);
        }

        ~Node(){ }

        char content() 
        { 
            return node_char; 
        }

        void setContent(char c) 
        { 
            node_char = c; 
        }

        bool wordMarker() 
        { 
            return end_word; 
        }
        void setWordMarker() 
        { 
            end_word = true; 
        }

        Node* findChild(char c)
        {
            return children[c - 97];
        }

        vector<Node*> get_children()
        {
            return children;
        }

        void insertChild(int index, Node * child) 
        { 
            children[index] = child; 
        }

        private:
            char node_char;
            bool end_word;
            vector<Node*> children;
};

class Trie {
    public:
        Trie()
        {
            root = new Node();
        }

        ~Trie();

        void addWord(string s)
        {
            Node* current = root;
            for(int i = 0; i < s.length(); i++)
            {       
                Node* child = current->findChild(s[i]);
                if (child != NULL)
                    current = child;
                else
                {
                    Node* tmp = new Node();
                    tmp->setContent(s[i]);
                    current->insertChild(s[i] - 97, tmp);
                    current = tmp;
                }
                if (i == s.length() - 1)
                    current->setWordMarker();
            }            
        }

        bool searchWord(string s)
        {
            Node* current = root;
            while(current != NULL)
            {
                for(int i = 0; i < s.length(); i++)
                {
                    Node* tmp = current->findChild(s[i]);
                    if (tmp == NULL)
                        return false;
                    current = tmp;
                }
                if (current->wordMarker())
                    return true;
                else
                    return false;
            }
            return false;
        }

        vector<string> all_words_that_start_with(char c)
        {
            Node * subroot = (root->get_children())[c - 97];
            vector<string> words;
            traverse_sub_tree(subroot, "", words);
            return words;
        }

    private:
        Node* root;

        void traverse_sub_tree(Node * curr, string word, vector<string> & words)
        {
            if(curr == NULL)
                return;

            word += curr->content();
            if(curr->wordMarker())
                words.push_back(word);
            for(int i = 0; i < 26; i++)
            {
                Node * ch = (curr->get_children())[i];
                traverse_sub_tree(ch, word, words);
            }
        }
};


inline int min(int x, int y, int z)
{
    if (x < y)
        return x < z ? x : z;
    else
        return y < z ? y : z;
}

int edit_distance(const string& A, const string& B, int (&weights)[26][26])
{
    int NA = A.size();
    int NB = B.size();

    vector<vector<int> > M(NA + 1, vector<int>(NB + 1));

    for (int a = 0; a <= NA; ++a)
        M[a][0] = a;

    for (int b = 0; b <= NB; ++b)
        M[0][b] = b;

    for (int a = 1; a <= NA; ++a)
        for (int b = 1; b <= NB; ++b)
        {
            int x = M[a-1][b] + 2;
            int y = M[a][b-1] + 2;
            int z_1 = M[a-1][b-1] + (A[a-1] == B[b-1] ? 0 : weights[A[a - 1] - 97][B[b - 1] - 97]);
            int z_2 = M[a-1][b-1] + (A[a-1] == B[b-1] ? 0 : 2);
            int z = (z_1 + z_2)/2;
            M[a][b] = min(x,y,z);
        }

    return M[A.size()][B.size()];
}


int main()
{

    int space = 3;

    int weights[26][26];

    weights[0][0] = 0;  // a to a 
    weights[0][1] = 4; // a to b 
    weights[0][2] = 3;  // a to c 
    weights[0][3] =  2; // a to d 
    weights[0][4] =  2; // a to e 
    weights[0][5] =  3; // a to f 
    weights[0][6] =  4; // a to g 
    weights[0][7] =  5; // a to h 
    weights[0][8] =  5; // a to i 
    weights[0][9] =  5; // a to j 
    weights[0][10] =  5; // a to k 
    weights[0][11] =  5; // a to l 
    weights[0][12] =  5; // a to m 
    weights[0][13] =  5; // a to n 
    weights[0][14] =  5; // a to o 
    weights[0][15] =  5; // a to p 
    weights[0][16] =  1; // a to q 
    weights[0][17] =  3; // a to r 
    weights[0][18] =  1; // a to s 
    weights[0][19] =  4; // a to t 
    weights[0][20] =  4; // a to u 
    weights[0][21] =  4; // a to v 
    weights[0][22] =  2; // a to w 
    weights[0][23] =  2; // a to x 
    weights[0][24] =  4; // a to y 
    weights[0][25] =  1; // a to z 

    weights[1][0] =  4; // b to a 
    weights[1][1] =  0; // b to b 
    weights[1][2] =  2; // b to c 
    weights[1][3] =  3; // b to d 
    weights[1][4] =  3; // b to e 
    weights[1][5] =  3; // b to f 
    weights[1][6] =   1; // b to g 
    weights[1][7] =   1; // b to h 
    weights[1][8] =   2;// b to i 
    weights[1][9] =   3;// b to j 
    weights[1][10] =   3;// b to k 
    weights[1][11] =   4;// b to l 
    weights[1][12] =   3;// b to m 
    weights[1][13] =   1;// b to n 
    weights[1][14] =   3;// b to o 
    weights[1][15] =   3;// b to p 
    weights[1][16] =   5; // b to q 
    weights[1][17] =   2;// b to r 
    weights[1][18] =   4;// b to s 
    weights[1][19] =   2;// b to t 
    weights[1][20] =   2;// b to u 
    weights[1][21] =   1;// b to v 
    weights[1][22] =   4;// b to w 
    weights[1][23] =   3;// b to x 
    weights[1][24] =   2;// b to y 
    weights[1][25] =   4;// b to z 

    weights[2][0] =   2;// c to a 
    weights[2][1] =   2;// c to b 
    weights[2][2] =   0;// c to c 
    weights[2][3] =   1;// c to d 
    weights[2][4] =   2;// c to e 
    weights[2][5] =   1;// c to f 
    weights[2][6] =   2;// c to g 
    weights[2][7] =   2;// c to h 
    weights[2][8] =   4;// c to i 
    weights[2][9] =   3;// c to j 
    weights[2][10] =   4;// c to k 
    weights[2][11] =   4;// c to l 
    weights[2][12] =   4;// c to m 
    weights[2][13] =   3;// c to n 
    weights[2][14] =   4;// c to o 
    weights[2][15] =   5;// c to p 
    weights[2][16] =   3;// c to q 
    weights[2][17] =   2;// c to r 
    weights[2][18] =   2;// c to s 
    weights[2][19] =   2;// c to t 
    weights[2][20] =   4;// c to u 
    weights[2][21] =   1;// c to v 
    weights[2][22] =   2;// c to w 
    weights[2][23] =   1;// c to x 
    weights[2][24] =   3;// c to y 
    weights[2][25] =   2;// c to z 

    weights[3][0] =   2;// d to a 
    weights[3][1] =   3;// d to b 
    weights[3][2] =   1;// d to c 
    weights[3][3] =   0;// d to d 
    weights[3][4] =   1;// d to e 
    weights[3][5] =   1;// d to f 
    weights[3][6] =   2;// d to g 
    weights[3][7] =   3;// d to h 
    weights[3][8] =   4;// d to i 
    weights[3][9] =   3;// d to j 
    weights[3][10] =   4;// d to k 
    weights[3][11] =   5;// d to l 
    weights[3][12] =   4;// d to m 
    weights[3][13] =   3;// d to n 
    weights[3][14] =   4;// d to o 
    weights[3][15] =   4;// d to p 
    weights[3][16] =   3;// d to q 
    weights[3][17] =   1;// d to r 
    weights[3][18] =   1;// d to s 
    weights[3][19] =   2;// d to t 
    weights[3][20] =   3;// d to u 
    weights[3][21] =   2;// d to v 
    weights[3][22] =   1;// d to w 
    weights[3][23] =   1;// d to x 
    weights[3][24] =   3;// d to y 
    weights[3][25] =   2;// d to z 

    weights[4][0] =   2;// e to a 
    weights[4][1] =   3;// e to b 
    weights[4][2] =   2;// e to c 
    weights[4][3] =   1;// e to d 
    weights[4][4] =   0;// e to e 
    weights[4][5] =   1;// e to f 
    weights[4][6] =   2;// e to g 
    weights[4][7] =   3;// e to h 
    weights[4][8] =   1;// e to i 
    weights[4][9] =   4;// e to j 
    weights[4][10] =   4;// e to k 
    weights[4][11] =   5;// e to l 
    weights[4][12] =   4;// e to m 
    weights[4][13] =   4;// e to n 
    weights[4][14] =   3;// e to o 
    weights[4][15] =   4;// e to p 
    weights[4][16] =   2;// e to q 
    weights[4][17] =   1;// e to r 
    weights[4][18] =   1;// e to s 
    weights[4][19] =   2;// e to t 
    weights[4][20] =   3;// e to u 
    weights[4][21] =   2;// e to v 
    weights[4][22] =   1;// e to w 
    weights[4][23] =   2;// e to x 
    weights[4][24] =   2;// e to y 
    weights[4][25] =   2;// e to z 

    weights[5][0] =   3;// f to a 
    weights[5][1] =   2;// f to b 
    weights[5][2] =   1;// f to c 
    weights[5][3] =   1;// f to d 
    weights[5][4] =   1;// f to e 
    weights[5][5] =   0;// f to f 
    weights[5][6] =   1;// f to g 
    weights[5][7] =   2;// f to h 
    weights[5][8] =   3;// f to i 
    weights[5][9] =   3;// f to j 
    weights[5][10] =   4;// f to k 
    weights[5][11] =   4;// f to l 
    weights[5][12] =   4;// f to m 
    weights[5][13] =   3;// f to n 
    weights[5][14] =   4;// f to o 
    weights[5][15] =   3;// f to p 
    weights[5][16] =   3;// f to q 
    weights[5][17] =   1;// f to r 
    weights[5][18] =   2;// f to s 
    weights[5][19] =   1;// f to t 
    weights[5][20] =   3;// f to u 
    weights[5][21] =   1;// f to v 
    weights[5][22] =   2;// f to w 
    weights[5][23] =   2;// f to x 
    weights[5][24] =   2;// f to y 
    weights[5][25] =   2;// f to z 

    weights[6][0] =   4;// g to a 
    weights[6][1] =   1;// g to b 
    weights[6][2] =   2;// g to c 
    weights[6][3] =   2;// g to d 
    weights[6][4] =   2;// g to e 
    weights[6][5] =   1;// g to f 
    weights[6][6] =   0;// g to g 
    weights[6][7] =   1;// g to h 
    weights[6][8] =   3;// g to i 
    weights[6][9] =   2;// g to j 
    weights[6][10] =   4;// g to k 
    weights[6][11] =   4;// g to l 
    weights[6][12] =   4;// g to m 
    weights[6][13] =   2;// g to n 
    weights[6][14] =   4;// g to o 
    weights[6][15] =   4;// g to p 
    weights[6][16] =   4;// g to q 
    weights[6][17] =   2;// g to r 
    weights[6][18] =   3;// g to s 
    weights[6][19] =   1;// g to t 
    weights[6][20] =   2;// g to u 
    weights[6][21] =   1;// g to v 
    weights[6][22] =   3;// g to w 
    weights[6][23] =   3;// g to x 
    weights[6][24] =   1;// g to y 
    weights[6][25] =   3;// g to z 

    weights[7][0] =   4;// h to a 
    weights[7][1] =   1;// h to b 
    weights[7][2] =   2;// h to c 
    weights[7][3] =   3;// h to d 
    weights[7][4] =   4;// h to e 
    weights[7][5] =   2;// h to f 
    weights[7][6] =   1;// h to g 
    weights[7][7] =   0;// h to h 
    weights[7][8] =   2;// h to i 
    weights[7][9] =   1;// h to j 
    weights[7][10] =   2;// h to k 
    weights[7][11] =   3;// h to l 
    weights[7][12] =   2;// h to m 
    weights[7][13] =   1;// h to n 
    weights[7][14] =   2;// h to o 
    weights[7][15] =   3;// h to p 
    weights[7][16] =   4;// h to q 
    weights[7][17] =   3;// h to r 
    weights[7][18] =   4;// h to s 
    weights[7][19] =   1;// h to t 
    weights[7][20] =   1;// h to u 
    weights[7][21] =   2;// h to v 
    weights[7][22] =   4;// h to w 
    weights[7][23] =   4;// h to x 
    weights[7][24] =   1;// h to y 
    weights[7][25] =   4;// h to z 

    weights[8][0] =   4;// i to a 
    weights[8][1] =   3;// i to b 
    weights[8][2] =   4;// i to c 
    weights[8][3] =   4;// i to d 
    weights[8][4] =   2;// i to e 
    weights[8][5] =   3;// i to f 
    weights[8][6] =   3;// i to g 
    weights[8][7] =   2;// i to h 
    weights[8][8] =   0;// i to i 
    weights[8][9] =   1;// i to j 
    weights[8][10] =  1; // i to k 
    weights[8][11] =   1;// i to l 
    weights[8][12] =   2;// i to m 
    weights[8][13] =   2;// i to n 
    weights[8][14] =   1;// i to o 
    weights[8][15] =   2;// i to p 
    weights[8][16] =   4;// i to q 
    weights[8][17] =   3;// i to r 
    weights[8][18] =   4;// i to s 
    weights[8][19] =   3;// i to t 
    weights[8][20] =   1;// i to u 
    weights[8][21] =   3;// i to v 
    weights[8][22] =   4;// i to w 
    weights[8][23] =   4;// i to x 
    weights[8][24] =   2;// i to y 
    weights[8][25] =   4;// i to z 

    weights[9][0] =   4;// j to a 
    weights[9][1] =   2;// j to b 
    weights[9][2] =   4;// j to c 
    weights[9][3] =   4;// j to d 
    weights[9][4] =   4;// j to e 
    weights[9][5] =   3;// j to f 
    weights[9][6] =   2;// j to g 
    weights[9][7] =   1;// j to h 
    weights[9][8] =   1;// j to i 
    weights[9][9] =   0;// j to j 
    weights[9][10] =   1;// j to k 
    weights[9][11] =   2;// j to l 
    weights[9][12] =   1;// j to m 
    weights[9][13] =   1;// j to n 
    weights[9][14] =   2;// j to o 
    weights[9][15] =   2;// j to p 
    weights[9][16] =   5;// j to q 
    weights[9][17] =   3;// j to r 
    weights[9][18] =   4;// j to s 
    weights[9][19] =   3;// j to t 
    weights[9][20] =   1;// j to u 
    weights[9][21] =   2;// j to v 
    weights[9][22] =   4;// j to w 
    weights[9][23] =   4;// j to x 
    weights[9][24] =   1;// j to y 
    weights[9][25] =   5;// j to z 

    weights[10][0] =   4;// k to a 
    weights[10][1] =   2;// k to b 
    weights[10][2] =   2;// k to c 
    weights[10][3] =   4;// k to d 
    weights[10][4] =   4;// k to e 
    weights[10][5] =   4;// k to f 
    weights[10][6] =   3;// k to g 
    weights[10][7] =   2;// k to h 
    weights[10][8] =   1;// k to i 
    weights[10][9] =   1;// k to j 
    weights[10][10] =   0;// k to k 
    weights[10][11] =   1;// k to l 
    weights[10][12] =   1;// k to m 
    weights[10][13] =   2;// k to n 
    weights[10][14] =   1;// k to o 
    weights[10][15] =   2;// k to p 
    weights[10][16] =   4;// k to q 
    weights[10][17] =   4;// k to r 
    weights[10][18] =   4;// k to s 
    weights[10][19] =   4;// k to t 
    weights[10][20] =   2;// k to u 
    weights[10][21] =   3;// k to v 
    weights[10][22] =   4;// k to w 
    weights[10][23] =   4;// k to x 
    weights[10][24] =   4;// k to y 
    weights[10][25] =   5;// k to z 

    weights[11][0] =   5;// l to a 
    weights[11][1] =   3;// l to b 
    weights[11][2] =   4;// l to c 
    weights[11][3] =   4;// l to d 
    weights[11][4] =   4;// l to e 
    weights[11][5] =   4;// l to f 
    weights[11][6] =   3;// l to g 
    weights[11][7] =   3;// l to h 
    weights[11][8] =   1;// l to i 
    weights[11][9] =   2;// l to j 
    weights[11][10] =   1;// l to k 
    weights[11][11] =   0;// l to l 
    weights[11][12] =   1;// l to m 
    weights[11][13] =   3;// l to n 
    weights[11][14] =   1;// l to o 
    weights[11][15] =   1;// l to p 
    weights[11][16] =   5;// l to q 
    weights[11][17] =   4;// l to r 
    weights[11][18] =   4;// l to s 
    weights[11][19] =   3;// l to t 
    weights[11][20] =   3;// l to u 
    weights[11][21] =   3;// l to v 
    weights[11][22] =   4;// l to w 
    weights[11][23] =   4;// l to x 
    weights[11][24] =   3;// l to y 
    weights[11][25] =   5;// l to z 

    weights[12][0] =   5;// m to a 
    weights[12][1] =   2;// m to b 
    weights[12][2] =   4;// m to c 
    weights[12][3] =   4;// m to d 
    weights[12][4] =   3;// m to e 
    weights[12][5] =   3;// m to f 
    weights[12][6] =   2;// m to g 
    weights[12][7] =   1;// m to h 
    weights[12][8] =   2;// m to i 
    weights[12][9] =   1;// m to j 
    weights[12][10] =  1; // m to k 
    weights[12][11] =   2;// m to l 
    weights[12][12] =   0;// m to m 
    weights[12][13] =   1;// m to n 
    weights[12][14] =   2;// m to o 
    weights[12][15] =   2;// m to p 
    weights[12][16] =   5;// m to q 
    weights[12][17] =   4;// m to r 
    weights[12][18] =   4;// m to s 
    weights[12][19] =   4;// m to t 
    weights[12][20] =   3;// m to u 
    weights[12][21] =   3;// m to v 
    weights[12][22] =   5;// m to w 
    weights[12][23] =   5;// m to x 
    weights[12][24] =   3;// m to y 
    weights[12][25] =   5;// m to z 

    weights[13][0] =   4;// n to a 
    weights[13][1] =   1;// n to b 
    weights[13][2] =   3;// n to c 
    weights[13][3] =   4;// n to d 
    weights[13][4] =   4;// n to e 
    weights[13][5] =   3;// n to f 
    weights[13][6] =   2;// n to g 
    weights[13][7] =   1;// n to h 
    weights[13][8] =   2;// n to i 
    weights[13][9] =   1;// n to j 
    weights[13][10] =   1;// n to k 
    weights[13][11] =   2;// n to l 
    weights[13][12] =   1;// n to m 
    weights[13][13] =   0;// n to n 
    weights[13][14] =   3;// n to o 
    weights[13][15] =   3;// n to p 
    weights[13][16] =   4;// n to q 
    weights[13][17] =   4;// n to r 
    weights[13][18] =  4; // n to s 
    weights[13][19] =  3; // n to t 
    weights[13][20] =  2; // n to u 
    weights[13][21] =  2; // n to v 
    weights[13][22] =  4; // n to w 
    weights[13][23] =  4; // n to x 
    weights[13][24] =  2; // n to y 
    weights[13][25] =   5;// n to z 

    weights[14][0] =   5;// o to a 
    weights[14][1] =   3;// o to b 
    weights[14][2] =   4;// o to c 
    weights[14][3] =   4;// o to d 
    weights[14][4] =   2;// o to e 
    weights[14][5] =   4;// o to f 
    weights[14][6] =   3;// o to g 
    weights[14][7] =   3;// o to h 
    weights[14][8] =   1;// o to i 
    weights[14][9] =   1;// o to j 
    weights[14][10] =   1;// o to k 
    weights[14][11] =   1;// o to l 
    weights[14][12] =   2;// o to m 
    weights[14][13] =   2;// o to n 
    weights[14][14] =   0;// o to o 
    weights[14][15] =   1;// o to p 
    weights[14][16] =   4;// o to q 
    weights[14][17] =   4;// o to r 
    weights[14][18] =   5;// o to s 
    weights[14][19] =   4;// o to t 
    weights[14][20] =   1;// o to u 
    weights[14][21] =   4;// o to v 
    weights[14][22] =   4;// o to w 
    weights[14][23] =   4;// o to x 
    weights[14][24] =   3;// o to y 
    weights[14][25] =   5;// o to z 

    weights[15][0] =  5; // p to a 
    weights[15][1] =  3; // p to b 
    weights[15][2] =  4; // p to c 
    weights[15][3] =  5; // p to d 
    weights[15][4] =  4; // p to e 
    weights[15][5] =  4; // p to f 
    weights[15][6] =  4; // p to g 
    weights[15][7] =  3; // p to h 
    weights[15][8] =  2; // p to i 
    weights[15][9] =  3; // p to j 
    weights[15][10] =  2; // p to k 
    weights[15][11] =  1; // p to l 
    weights[15][12] =  2; // p to m 
    weights[15][13] =  3; // p to n 
    weights[15][14] =  1; // p to o 
    weights[15][15] =  0; // p to p 
    weights[15][16] =  4; // p to q 
    weights[15][17] =  4; // p to r 
    weights[15][18] =  4; // p to s 
    weights[15][19] =  4; // p to t 
    weights[15][20] =   3;// p to u 
    weights[15][21] =  4; // p to v 
    weights[15][22] =  4; // p to w 
    weights[15][23] =   4;// p to x 
    weights[15][24] =   3;// p to y 
    weights[15][25] =   5;// p to z 

    weights[16][0] =  1; // q to a 
    weights[16][1] =   4;// q to b 
    weights[16][2] =  3; // q to c 
    weights[16][3] =   3;// q to d 
    weights[16][4] =   2;// q to e 
    weights[16][5] =   3;// q to f 
    weights[16][6] =  4; // q to g 
    weights[16][7] =   4;// q to h 
    weights[16][8] =   5;// q to i 
    weights[16][9] =   5;// q to j 
    weights[16][10] =  5; // q to k 
    weights[16][11] =   5;// q to l 
    weights[16][12] =   5;// q to m 
    weights[16][13] =   5;// q to n 
    weights[16][14] =   5;// q to o 
    weights[16][15] =   5;// q to p 
    weights[16][16] =   0;// q to q 
    weights[16][17] =   3;// q to r 
    weights[16][18] =   2;// q to s 
    weights[16][19] =   3;// q to t 
    weights[16][20] =   4;// q to u 
    weights[16][21] =   4;// q to v 
    weights[16][22] =   1;// q to w 
    weights[16][23] =   3;// q to x 
    weights[16][24] =   4;// q to y 
    weights[16][25] =   2;// q to z 

    weights[17][0] =   4;// r to a 
    weights[17][1] =   3;// r to b 
    weights[17][2] =   3;// r to c 
    weights[17][3] =   1;// r to d 
    weights[17][4] =   1;// r to e 
    weights[17][5] =   1;// r to f 
    weights[17][6] =   1;// r to g 
    weights[17][7] =   2;// r to h 
    weights[17][8] =   4;// r to i 
    weights[17][9] =   4;// r to j 
    weights[17][10] =  4; // r to k 
    weights[17][11] =  4; // r to l 
    weights[17][12] =  4; // r to m 
    weights[17][13] =  4; // r to n 
    weights[17][14] =  4; // r to o 
    weights[17][15] =  4; // r to p 
    weights[17][16] =  3; // r to q 
    weights[17][17] =  0; // r to r 
    weights[17][18] =  3; // r to s 
    weights[17][19] =  1; // r to t 
    weights[17][20] =  3; // r to u 
    weights[17][21] =  3; // r to v 
    weights[17][22] =  2; // r to w 
    weights[17][23] =   3;// r to x 
    weights[17][24] =   2;// r to y 
    weights[17][25] =   3;// r to z 

    weights[18][0] =   1;// s to a 
    weights[18][1] =   4;// s to b 
    weights[18][2] =   2;// s to c 
    weights[18][3] =   1;// s to d 
    weights[18][4] =   1;// s to e 
    weights[18][5] =   2;// s to f 
    weights[18][6] =   3;// s to g 
    weights[18][7] =   4;// s to h 
    weights[18][8] =   4;// s to i 
    weights[18][9] =   4;// s to j 
    weights[18][10] =  4; // s to k 
    weights[18][11] =  4; // s to l 
    weights[18][12] =   4;// s to m 
    weights[18][13] =   4;// s to n 
    weights[18][14] =   4;// s to o 
    weights[18][15] =   5;// s to p 
    weights[18][16] =   2;// s to q 
    weights[18][17] =   2;// s to r 
    weights[18][18] =   0;// s to s 
    weights[18][19] =   3;// s to t 
    weights[18][20] =   4;// s to u 
    weights[18][21] =   3;// s to v 
    weights[18][22] =   1;// s to w 
    weights[18][23] =   1;// s to x 
    weights[18][24] =   3;// s to y 
    weights[18][25] =   1;// s to z 

    weights[19][0] =  4; // t to a 
    weights[19][1] =  2; // t to b 
    weights[19][2] =  2; // t to c 
    weights[19][3] =  2; // t to d 
    weights[19][4] =   2;// t to e 
    weights[19][5] =   1;// t to f 
    weights[19][6] =   1;// t to g 
    weights[19][7] =   2;// t to h 
    weights[19][8] =   3;// t to i 
    weights[19][9] =   3;// t to j 
    weights[19][10] =  4; // t to k 
    weights[19][11] =  4; // t to l 
    weights[19][12] =  4; // t to m 
    weights[19][13] =  3; // t to n 
    weights[19][14] =  3; // t to o 
    weights[19][15] =  4; // t to p 
    weights[19][16] =  4; // t to q 
    weights[19][17] =  1; // t to r 
    weights[19][18] =  3; // t to s 
    weights[19][19] =   0;// t to t 
    weights[19][20] =  2; // t to u 
    weights[19][21] =  2; // t to v 
    weights[19][22] =  3; // t to w 
    weights[19][23] =   4;// t to x 
    weights[19][24] =   1;// t to y 
    weights[19][25] =   4;// t to z 

    weights[20][0] =   4;// u to a 
    weights[20][1] =   3;// u to b 
    weights[20][2] =   4;// u to c 
    weights[20][3] =   4;// u to d 
    weights[20][4] =   2;// u to e 
    weights[20][5] =   3;// u to f 
    weights[20][6] =   2;// u to g 
    weights[20][7] =   1;// u to h 
    weights[20][8] =   1;// u to i 
    weights[20][9] =   1;// u to j 
    weights[20][10] =   1;// u to k 
    weights[20][11] =   2;// u to l 
    weights[20][12] =   2;// u to m 
    weights[20][13] =   2;// u to n 
    weights[20][14] =   2;// u to o 
    weights[20][15] =   3;// u to p 
    weights[20][16] =   4;// u to q 
    weights[20][17] =   3;// u to r 
    weights[20][18] =   4;// u to s 
    weights[20][19] =   2;// u to t 
    weights[20][20] =   0;// u to u 
    weights[20][21] =   3;// u to v 
    weights[20][22] =   4;// u to w 
    weights[20][23] =   4;// u to x 
    weights[20][24] =   1;// u to y 
    weights[20][25] =   5;// u to z 

    weights[21][0] =   4;// v to a 
    weights[21][1] =   1;// v to b 
    weights[21][2] =   1;// v to c 
    weights[21][3] =   2;// v to d 
    weights[21][4] =   3;// v to e 
    weights[21][5] =   1;// v to f 
    weights[21][6] =   1;// v to g 
    weights[21][7] =   2;// v to h 
    weights[21][8] =   4;// v to i 
    weights[21][9] =   3;// v to j 
    weights[21][10] =  4; // v to k 
    weights[21][11] =   4;// v to l 
    weights[21][12] =   3;// v to m 
    weights[21][13] =   2;// v to n 
    weights[21][14] =   4;// v to o 
    weights[21][15] =   5;// v to p 
    weights[21][16] =   4;// v to q 
    weights[21][17] =   3;// v to r 
    weights[21][18] =   4;// v to s 
    weights[21][19] =   3;// v to t 
    weights[21][20] =   4;// v to u 
    weights[21][21] =   0;// v to v 
    weights[21][22] =   4;// v to w 
    weights[21][23] =   2;// v to x 
    weights[21][24] =   3;// v to y 
    weights[21][25] =   4;// v to z 

    weights[22][0] =  1; // w to a 
    weights[22][1] =   4;// w to b 
    weights[22][2] =   3;// w to c 
    weights[22][3] =   2;// w to d 
    weights[22][4] =   1;// w to e 
    weights[22][5] =   2;// w to f 
    weights[22][6] =   3;// w to g 
    weights[22][7] =   3;// w to h 
    weights[22][8] =   4;// w to i 
    weights[22][9] =   4;// w to j 
    weights[22][10] =  5; // w to k 
    weights[22][11] =  5; // w to l 
    weights[22][12] =   4;// w to m 
    weights[22][13] =   4;// w to n 
    weights[22][14] =   4;// w to o 
    weights[22][15] =   5;// w to p 
    weights[22][16] =   1;// w to q 
    weights[22][17] =   2;// w to r 
    weights[22][18] =   1;// w to s 
    weights[22][19] =   3;// w to t 
    weights[22][20] =   4;// w to u 
    weights[22][21] =   3;// w to v 
    weights[22][22] =   0;// w to w 
    weights[22][23] =   2;// w to x 
    weights[22][24] =   4;// w to y 
    weights[22][25] =   3;// w to z 

    weights[23][0] =   1;// x to a 
    weights[23][1] =   3;// x to b 
    weights[23][2] =   1;// x to c 
    weights[23][3] =   1;// x to d 
    weights[23][4] =   2;// x to e 
    weights[23][5] =   2;// x to f 
    weights[23][6] =   3;// x to g 
    weights[23][7] =   4;// x to h 
    weights[23][8] =   5;// x to i 
    weights[23][9] =   5;// x to j 
    weights[23][10] =   5;// x to k 
    weights[23][11] =   5;// x to l 
    weights[23][12] =   4;// x to m 
    weights[23][13] =   4;// x to n 
    weights[23][14] =   5;// x to o 
    weights[23][15] =   5;// x to p 
    weights[23][16] =   3;// x to q 
    weights[23][17] =   3;// x to r 
    weights[23][18] =   1;// x to s 
    weights[23][19] =   3;// x to t 
    weights[23][20] =   4;// x to u 
    weights[23][21] =   2;// x to v 
    weights[23][22] =   2;// x to w 
    weights[23][23] =   0;// x to x 
    weights[23][24] =   4;// x to y 
    weights[23][25] =   1;// x to z 

    weights[24][0] =  4; // y to a 
    weights[24][1] =   2;// y to b 
    weights[24][2] =   3;// y to c 
    weights[24][3] =   3;// y to d 
    weights[24][4] =   3;// y to e 
    weights[24][5] =   2;// y to f 
    weights[24][6] =   2;// y to g 
    weights[24][7] =   1;// y to h 
    weights[24][8] =   2;// y to i 
    weights[24][9] =   2;// y to j 
    weights[24][10] =   2;// y to k 
    weights[24][11] =   3;// y to l 
    weights[24][12] =   2;// y to m 
    weights[24][13] =   2;// y to n 
    weights[24][14] =   3;// y to o 
    weights[24][15] =   3;// y to p 
    weights[24][16] =   4;// y to q 
    weights[24][17] =   2;// y to r 
    weights[24][18] =   4;// y to s 
    weights[24][19] =   1;// y to t 
    weights[24][20] =   1;// y to u 
    weights[24][21] =   2;// y to v 
    weights[24][22] =   4;// y to w 
    weights[24][23] =   4;// y to x 
    weights[24][24] =   0;// y to y 
    weights[24][25] =   4;// y to z 

    weights[25][0] =   1;// z to a 
    weights[25][1] =   4;// z to b 
    weights[25][2] =   3;// z to c 
    weights[25][3] =   2;// z to d 
    weights[25][4] =   3;// z to e 
    weights[25][5] =   3;// z to f 
    weights[25][6] =   4;// z to g 
    weights[25][7] =   4;// z to h 
    weights[25][8] =   5;// z to i 
    weights[25][9] =   5;// z to j 
    weights[25][10] =  5; // z to k 
    weights[25][11] =   5;// z to l 
    weights[25][12] =   5;// z to m 
    weights[25][13] =   4;// z to n 
    weights[25][14] =   5;// z to o 
    weights[25][15] =   5;// z to p 
    weights[25][16] =   3;// z to q 
    weights[25][17] =   4;// z to r 
    weights[25][18] =   1;// z to s 
    weights[25][19] =   3;// z to t 
    weights[25][20] =   4;// z to u 
    weights[25][21] =   3;// z to v 
    weights[25][22] =   2;// z to w 
    weights[25][23] =   1;// z to x 
    weights[25][24] =   4;// z to y 
    weights[25][25] =   0;// z to z 




    Trie* trie = new Trie();
    
    ifstream f("words.txt");
    string s;
    int num_words = 0;
    while(getline(f, s))
    {
        trie->addWord(s);
        num_words++;
    }

    vector<vector<string> > sorted;
    for(int i = 0; i < 26; i++)
    {
        vector<string> words = trie->all_words_that_start_with(char(i + 97));
        sorted.push_back(words);
    }
    int best = 100000;
    string best_string = "";
    while(1)
    {
        cout<<"Enter a word: ";
        cin >> s;
        vector<string> words = sorted[s[0] - 97];
        if(trie->searchWord(s))
            cout<<s<<endl;
        else
        {
            for(int i = 0; i < words.size(); i++)
            { 
                int dist = edit_distance(words[i], s, weights);
                if(dist < best)
                {
                    best = dist;
                    best_string = words[i];
                }
            }
            
            for(int i = 0; i < words.size(); i++)
            { 
                int dist = edit_distance(words[i], s, weights);
                if(best == dist || dist == best + 1)
                    cout<<words[i]<<endl;
            }
        }
        best = 100000;
        best_string = ""; 
    } 
}