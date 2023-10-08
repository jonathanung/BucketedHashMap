#include <iostream>
#include <string>
#include "BucketedHashMap.hpp"

int main() {
    BucketedHashMap<std::string, int> bHM = BucketedHashMap<std::string, int>(0.5);
    bHM.insert("ABC", 5);
    bHM.showStructure();
    bHM.show();
    std::cout << bHM["ABC"] << std::endl;
    std::cout << bHM.getSize() << std::endl;
    bHM["ABC"] = 3000;
    // bHM.insert("ABC", 3000);
    bHM.insert("ABCDE", 30);
    bHM.insert("neighbour", 10);
    bHM.insert("ABCEE", 11);
    bHM.showStructure();
    bHM.insert("ZZZZZ", 20);
    bHM.insert("YOOO", 40);
    bHM.insert("agagaga", 511);
    bHM.insert("rishits mom", 27);
    bHM.showStructure();
    bHM.show();
    std::cout << bHM["ABC"] << std::endl;
    std::cout << bHM.getSize() << std::endl;
    bHM.remove("ABC");
    bHM.showStructure();
    std::cout << bHM << std::endl;
    std::cout << bHM.getSize() << std::endl;
    std::cout << bHM["ABC"] << std::endl;
    return 0;
}