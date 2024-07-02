#include "config.h"

/**
 * @brief Function used to serialize the players (clients) hands.
 * 
 * @param data The data to be serialized.
 * @return The data serialized.
 */
string serialize(const vector<vector<pair<int, int>>>& data) {
    string serializedData;
    // Looping big vector
    for (const auto& innerVec : data) {
        // Adds inner vector size to string begin as a prefix
        size_t innerSize = innerVec.size();
        serializedData.append(reinterpret_cast<const char*>(&innerSize), sizeof(size_t));
        
        // Looping the inner vector and serializing pairs
        for (const auto& card : innerVec) {
            // Append each card's rank and suit
            serializedData.append(reinterpret_cast<const char*>(&card.first), sizeof(int));
            serializedData.append(reinterpret_cast<const char*>(&card.second), sizeof(int));
        }
    }

    return serializedData;
}

/**
 * @brief Function used to deserialize the players (clients) hands.
 * 
 * @param serializedData The data to be deserialized.
 * @return The data deserialized.
 */
vector<vector<pair<int, int>>> deserialize(const string& serializedData) {
    vector<vector<pair<int, int>>> data;
    size_t offset = 0;

    // While there is data to read
    while (offset < serializedData.size()) {
        size_t innerSize;
        memcpy(&innerSize, serializedData.data() + offset, sizeof(size_t));
        offset += sizeof(size_t);

        // Reading inner vector
        vector<pair<int, int>> innerVec;
        for (size_t i = 0; i < innerSize; ++i) {
            // Reading each pair
            int first, second;
            memcpy(&first, serializedData.data() + offset, sizeof(int));
            offset += sizeof(int);
            memcpy(&second, serializedData.data() + offset, sizeof(int));
            offset += sizeof(int);
            innerVec.push_back(make_pair(first, second));
        }
        data.push_back(innerVec);
    }

    return data;
}