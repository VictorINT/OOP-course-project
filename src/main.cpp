#include "../include/views/Menu.h"
#include "../include/managers/ServiceManager.h"
#include <iostream>

using namespace std;

int main() {
    try {
        Menu menu;
        menu.ruleaza();
        
        // Cleanup
        ServiceManager::deleteInstance();
        
    } catch (const exception& e) {
        cerr << "Eroare: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
