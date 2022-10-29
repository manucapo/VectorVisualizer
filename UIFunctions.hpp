#pragma once
void CreateCustomParticle(string* inputString, float* userInputFloat, Particle* tempParticle, shared_ptr<World> world);
void CreateCustomLine(string* inputString, float* userInputFloat, Line* tempLine, shared_ptr<World> world);
void CreateCustomTrace(string* inputString, float* userInputFloat, Trace* tracePtr, shared_ptr<World> world);

void CreateCustomParticle(string* inputString, float* userInputFloat, Particle* tempParticle, shared_ptr<World> world) { //Create particle asking user for input
    cout << "Enter particle X postion : \n" << endl;
    getline(cin, *inputString);
    stringstream(*inputString) >> *userInputFloat;
    tempParticle->setX(*userInputFloat);
    cout << "Enter particle Y postion : \n" << endl;
    getline(cin, *inputString);
    stringstream(*inputString) >> *userInputFloat;
    tempParticle->setY(*userInputFloat);
    cout << "Enter particle force constant : \n" << endl;
    getline(cin, *inputString);
    stringstream(*inputString) >> *userInputFloat;
    tempParticle->setForceConstant(*userInputFloat);
    cout << "Enter particle charge : \n" << endl;
    getline(cin, *inputString);
    stringstream(*inputString) >> *userInputFloat;
    tempParticle->setCharge(*userInputFloat);
    cout << "Enter particle decay exponent : \n" << endl;
    getline(cin, *inputString);
    stringstream(*inputString) >> *userInputFloat;
    tempParticle->setDecayExponent(*userInputFloat);
    world->particleVector.push_back(*tempParticle); // push particle to world
}

void CreateCustomLine(string* inputString, float* userInputFloat, Line* tempLine, shared_ptr<World> world) {  //Create line asking user for input
    cout << "Enter Desired amount of line segments: " << endl;
    getline(cin, *inputString);
    stringstream(*inputString) >> *userInputFloat;
    int lineSegmentAmount = *userInputFloat;
    if (lineSegmentAmount > 0)
    {
        Line line;
        for (int i = 0; i < lineSegmentAmount; i++)
        {

            Point start;
            if (i == 0)
            {
                cout << "LINE SEGMENT " << i << " START :" << endl;
                cout << "Enter Desired start point X coordinate : " << endl;
                getline(cin, *inputString);
                stringstream(*inputString) >> *userInputFloat;
                start.setX(*userInputFloat);
                cout << "Enter Desired start point Y coordinate : " << endl;
                getline(cin, *inputString);
                stringstream(*inputString) >> *userInputFloat;
                start.setY(*userInputFloat);
            }
            else
            {
                start.setX(line.getTail().getX());
                start.setY(line.getTail().getY());
            }
            cout << "LINE SEGMENT " << i << " END :" << endl;
            Point end;
            cout << "Enter Desired end point X coordinate : " << endl;
            getline(cin, *inputString);
            stringstream(*inputString) >> *userInputFloat;
            end.setX(*userInputFloat);
            cout << "Enter Desired end point Y coordinate : " << endl;
            getline(cin, *inputString);
            stringstream(*inputString) >> *userInputFloat;
            end.setY(*userInputFloat);

            line.addSegment(start, end);
        }
        world->lineVector.push_back(line);
    }
}

void CreateCustomTrace(string* inputString, float* userInputFloat, Trace* tracePtr, shared_ptr<World> world) {  //Create trace asking user for input

    Trace trace;
    double xCoord;
    double yCoord;
    cout << "CREATING TRACE : " << endl;
    cout << "Enter Desired start point X coordinate : " << endl;
    getline(cin, *inputString);
    stringstream(*inputString) >> *userInputFloat;
    xCoord = *userInputFloat;
    cout << "Enter Desired start point Y coordinate : " << endl;
    getline(cin, *inputString);
    stringstream(*inputString) >> *userInputFloat;
    yCoord = *userInputFloat;

    trace.SetStart(xCoord, yCoord);
    trace.CreateTrace(world->particleVector);

    world->traceVector.push_back(trace);

}
