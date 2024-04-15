#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct Person {
    std::string ssn;
    std::string name;
};

std::vector<Person> data = {};
int insertionCounter = 0;
int deleteCounter = 0;
int retrievalCounter = 0;

void addData(const std::string& ssn, const std::string& name) {
    for (const auto& person : data) {
        if (person.ssn == ssn && person.name == name) {
            return; 
        }
    }

    data.push_back({ssn, name});
    insertionCounter++;
}

void deleteData(const std::string& ssn, const std::string& name) {
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it->ssn == ssn && it->name == name) {
            data.erase(it);
            deleteCounter++;
            return;
        }
    }
}

int getArraySize() {
    return data.size();
}

void processFile(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    
    if (!inputFile) {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }
        
        char command = line[0];
        std::string data = line.substr(1);
        
        switch (command) {
            case 'i':{
                    std::istringstream iss(data);
                    std::string ssn, name;
                    if (iss >> ssn >> name) {
                        addData(ssn, name);
                    }
                }
                break;
                
            case 'd':{
                    std::istringstream iss(data);
                    std::string ssn, name;
                    if (iss >> ssn >> name) {
                        deleteData(ssn, name);
                    }
                }
                break;
                
            case 'r':{
                    std::istringstream iss(data);
                    std::string ssn, name;
                    if (iss >> ssn >> name) {
                        retrievalCounter++;
                    }
                }
                break;
                
            default:
                std::cout << "Invalid command" << std::endl;
                break;
        }
    }
}


int main(int argc, char* argv[]) {
    clock_t start, end;
    double duration;  
    start = clock();

    std::string fileName = argv[1];
    processFile(fileName);
    
    std::cout << "The Number of Valid Insertations: " << insertionCounter << std::endl;
    std::cout << "The Number of Valid Deletions: " << deleteCounter << std::endl;
    std::cout << "The Number of Valid Retrievals: " << retrievalCounter << std::endl;
    std::cout << "Item numbers in the array: " << getArraySize() << std::endl;
    std::cout << "Array Size is: " << getArraySize() << std::endl;

    end = clock();
    duration = (end - start) / (double)CLOCKS_PER_SEC;
    std::cout << "Time elapsed: " << duration << std::endl;

    return 0;
}