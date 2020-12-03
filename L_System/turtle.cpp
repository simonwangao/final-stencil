# include "L_System/turtle.h"

void Turtle::setUpRules() {

    charToBranch = createBranchTypes();
    successors = createProductionRules();
    initial = "";

    for (int i = 0; i < l_t; i++) {
        if (i % 3) {
            initial.append("b");
        } else {
           initial.append("a");
        }
    }
}

string Turtle::createTreePattern(string predecessor) {

    string newPattern = "";

    // replaced based on probability
    for (int i = 0; i < l_t; i++) {

        char curr = predecessor[i];
        vector<char> options = successors[curr];
        int index = rand() % options.size();
        char next = options[index];

        newPattern.push_back(next);
    }

    // return changed string
    return newPattern;
}

