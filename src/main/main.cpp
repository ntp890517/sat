#include <iostream>

#include "../sol/SolverSimulate.h"

using namespace std;

int main(int argc,const char *argv[]) {
    Solver *solver = new SolverSimulate();

    //solver->SetDebug();
    solver->ReadCnf(argv[1]);
    solver->Solve();

    if (solver->IsSat()) {
        cout << "SAT. Assignment = " << solver->GetAssignment() << endl;
    } else if (solver->IsUnsat()) {
        cout << "UNSAT." << endl;
    } else {
        cout << "UNDEF." << endl;
    }

    return 0;
}
