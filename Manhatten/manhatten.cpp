// Adrian Melo
// CS 3304 Manhattan Tourist Problem
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

string path(vector<vector<int>>& grid){
    string answer = "";
    int m=grid.size(),n=grid[0].size();
    for (int i = m-1; i > -2; i){
        for (int j = n-1; j > -2; j){
            if (j ==0 && i ==0){
                return answer;
            }
           else if(grid[i][j] == grid[i-1][j] + grid[i-2][j]){
            i = i-2;
            answer += "S";
           }
           else{
            j = j - 2;
            answer += "E";

           }
        }
    }
    return answer;
}

int MaxPathSum(vector<vector<int>>& grid) {
    int i,j;
    int m=grid.size(),n=grid[0].size();

    string str;

    for(j = 2; j < n;j=j+2){
        grid[0][j] += grid[0][j-1] + grid[0][j-2];
    }
    for(i = 2; i < m; i= i+2){
        grid[i][0] += grid[i-1][0]+grid[i-2][0];
    }
    for(i = 2; i < m; i=i+2){
        for(j = 2; j < n; j=j+2){
            grid[i][j] = max(grid[i-2][j] + grid[i-1][j], grid[i][j-2] + grid[i][j-1]);

        }
    }

    cout << endl;
    str = path(grid);
    reverse(str.begin(), str.end()); 
	cout<<"Optimal Path = "<<str;
    return grid[m-1][n-1];
}

int main() {
    cout << "CS 3304 - Manhattan Tourist Problem\n";
    cout << "Adrian Melo\n" << endl;

    vector<vector<int>> graph; 
    ifstream file("Input.csv");
    string line;

    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            int val = stoi(cell);
            row.push_back(val);
        }

        for (int i = 0; i < row.size(); i++) {
            if (row[i] == 0) {
                for (int j = 0; j < row.size(); j++) {
                    row[j] = 0;
                    graph[i][j] = 0; 
                }
                break;
            }
        }
        graph.push_back(row);
    }

    for (int i = graph.size(); i >= 0; i--) {
        int size = graph[i].size();
        for (int j = graph[i].size(); j >=0; j--) {
            if (i % 2 == 0 && j==0){
                graph[i].insert(graph[i].begin(), 0);
                graph[i].insert(graph[i].end(), 0);
            }
            else if(graph[i][j] && j != 0 && j != size){
                graph[i].insert(graph[i].begin() + j , 0);
            }
        }
    }

    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    int score = MaxPathSum(graph);
    cout << "\nOptimal Score = " << score;
    return 0;
}
