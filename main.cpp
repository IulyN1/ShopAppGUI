/*
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
*/
#include "Produs.h"
#include "ProdusRepo.h"
#include "UI.h"
#include "Validator.h"
#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Tests.h"

void run_tests() {
    Tests teste;
    teste.ruleaza_teste();
}

int main(int argc, char* argv[]) {
    //run_tests();
    QApplication app(argc, argv);
    ProdusRepoFile repo("produse.txt");
    Validator valid;
    Cos cos{ repo };
    ProdusServ srv{ repo, valid, cos }; 
    
    
    GUI* gui = new GUI(srv,cos);
    gui->show();
    return app.exec();
    
    //_CrtDumpMemoryLeaks();
}
