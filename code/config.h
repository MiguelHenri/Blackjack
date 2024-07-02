#ifndef CONFIG
#define CONFIG

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

using namespace std;

const int PORT = 8080;
const int NUM_PLAYERS = 2; // max of 9 players
const int ACE_VALUE = 1;

string serialize(const vector<vector<pair<int, int>>>& data);
vector<vector<pair<int, int>>> deserialize(const string& serializedData);

#endif