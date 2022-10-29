#include "HelperFunctions.hpp"
#include "UIFunctions.hpp"

using namespace std;

int main(int argc, char const** argv)
{
  bool runMainProgramLoop = true;                        // Decides if the main program loop should run.
  bool showDisplayOptionsMenu = false;                   // Decides if the display menu should show.
  bool showFieldOptionsMenu = false;                     // Decides if the field menu should show.
  bool showWorldOptionsMenu = false;                     // Decides if the world menu should show.
  bool normalizeVectorsBeforeDisplay = true;             // Decides whether to display all vectors with a lenght of 1 unit.
  int pixelsPerUnit = SCALE;                             // Amount of pixels per unit.
  int i, j;
  float vectorRelativeScale = VECTORMULTIPLIER;                                // Vector display magnitude relative scaling.
  float vectorAbsolutePixelScale = pixelsPerUnit * vectorRelativeScale;        // Vector display magnitude absolute scaling in pixels.
  shared_ptr<World> world(new World(WORLDSIZE));                               // Collects Point/Particle/Vector objects.
    
  while (runMainProgramLoop) {                           // Start main program Loop.
    string userInputString = "";
    int userInputInteger = 0;
    float userInputFloat = 0;
    Particle localParticle;                              // Local instance to copy into and populate world Particle collection.
    Line localLine;                                             
    Trace localTrace;
        
    cout << "WELCOME !!! \n" << endl;
    cout << "1. EXIT PROGRAM \n" << endl;
    cout << "2. DISPLAY OPTIONS \n" << endl;
    cout << "3. FIELD OPTIONS \n" << endl;
    cout << "4. WORLD OPTIONS \n" << endl;
    cout << "5. RUN VECTOR VISUALIZER \n" << endl;
    getline(cin,userInputString);                             // Gets a line from cin buffer and copies it into to the string object,
    stringstream(userInputString) >> userInputInteger;        // Convert the string object into a stream to extract data from it.
        
    switch (userInputInteger) {                               // Main menu switch statement.
      case 1:
        cout <<"Are you sure you want to exit ? (y/n) \n" << endl;
        getline(cin,userInputString);
        if (userInputString.compare("y") == 0 || userInputString.compare("Y") == 0){
          runMainProgramLoop = false;
        }
        userInputString = "";
        break;
      case 2:
        showDisplayOptionsMenu = true;
        while (showDisplayOptionsMenu){                        // Start display options menu nested loop.
          cout << "DISPLAY SET UP MENU \n" << endl;
          cout << "1. EXIT DISPLAY MENU \n" << endl;
          if (normalizeVectorsBeforeDisplay) {
            cout << "2. NORMALIZED FIELD DISPLAY:  ON\n" << endl;
          } else {
            cout << "2. NORMALIZED FIELD DISPLAY:  OFF\n" << endl;
          }
          cout << "3. WORLD SCALE = " << pixelsPerUnit << " \n"<< endl;
          cout << "4. VECTOR SCALE = " << vectorRelativeScale << " \n" << endl;
          getline(cin,userInputString);
          stringstream(userInputString) >> userInputInteger;
                    
          switch (userInputInteger) {                         // Display options sub menu switch statement.
           case 1:
              showDisplayOptionsMenu = false;
              break;
            case 2:
              if (!normalizeVectorsBeforeDisplay){
                normalizeVectorsBeforeDisplay = true;
              } else {
                normalizeVectorsBeforeDisplay = false;
              }
              break;
            case 3:
              cout << "Enter in Desired World Scaling (In UNITS) : " << endl;
              getline(cin,userInputString);
              stringstream(userInputString) >> userInputInteger;
              if (userInputInteger == 0){
                userInputInteger = 1;
              }
              pixelsPerUnit = userInputInteger;
              vectorAbsolutePixelScale = pixelsPerUnit * vectorRelativeScale;
              break;
            case 4:
              cout << "Enter in Desired Vector Scaling (ABSOLUTE) : " << endl;
              getline(cin,userInputString);
              stringstream(userInputString) >> userInputFloat;
              if (userInputFloat == 0){
                userInputFloat = 1;
              }
              vectorRelativeScale  = userInputFloat;
              vectorAbsolutePixelScale = pixelsPerUnit * vectorRelativeScale;
              break;
            default:
              break;
          }
        }
        break;
      case 3:
        showFieldOptionsMenu = true;
        while (showFieldOptionsMenu){                                           // Start field options menu nested loop.
          cout << "FIELD SET UP MENU \n" << endl;
          cout << "1. EXIT FIELD MENU \n" << endl;
          cout << "2. X COMPONENT = " << Evaluator::instance()->getXExpressionString() << " \n"<< endl;
          cout << "3. Y COMPONENT = " << Evaluator::instance()->getYExpressionString() << " \n" << endl;
          cout << "4. FIELD TEMPLATES \n" << endl;
          cout << "5. SAMPLE FIELD \n" << endl;
          getline(cin,userInputString);
          stringstream(userInputString) >> userInputInteger;
            
          switch (userInputInteger) {                                           // Field options sub menu switch statement
            case 1:
              showFieldOptionsMenu = false;
              break;
            case 2:
              cout << "Enter Desired X component : " << endl;
              getline(cin,userInputString);
              Evaluator::instance()->setXExpressionString(userInputString);
              Evaluator::instance()->compileParser();
              break;
            case 3:
              cout << "Enter Desired Y component : " << endl;
              getline(cin,userInputString);
              Evaluator::instance()->setYExpressionString(userInputString);
              Evaluator::instance()->compileParser();
              break;
            case 4:
              cout << "1. Anti clockwise circular field. \n" << endl;
              cout << "2. Cyclone belt field. \n" << endl;
              cout << "3. Empty field. \n" << endl;
              getline(cin,userInputString);
              stringstream(userInputString) >> userInputInteger;
              switch (userInputInteger) {                                       // Field template sub sub menu switch statement
                case 1:
                  Evaluator::instance()->setXExpressionString("-y");
                  Evaluator::instance()->setYExpressionString("x");
                  break;
                case 2:
                  Evaluator::instance()->setXExpressionString("y");
                  Evaluator::instance()->setYExpressionString("sin(x)");
                  break;
                case 3:
                  Evaluator::instance()->setXExpressionString("0");
                  Evaluator::instance()->setYExpressionString("0");
                  break;
                default:
                  break;
              }
              Evaluator::instance()->compileParser();
              break;
            case 5:
              cout << "Enter Desired sampling point X coordinate : " << endl;
              getline(cin,userInputString);
              stringstream(userInputString) >> userInputFloat;
              Evaluator::instance()->setXValue(userInputFloat);
              cout << "Enter Desired sampling point Y coordinate : " << endl;
              getline(cin,userInputString);
              stringstream(userInputString) >> userInputFloat;
              Evaluator::instance()->setYValue(userInputFloat);
#ifdef EXPRESSIONMODE1
              if (Evaluator::instance()->getParserState())
              {
                  Evaluator::instance()->setXResult(Evaluator::instance()->getExpressionX().value());
                  Evaluator::instance()->setYResult(Evaluator::instance()->getExpressionY().value());
              }
              else
              {
                  cout << "PARSER FAILED TO COMPILE ! \n" << endl;
              }
#endif
#ifndef EXPRESSIONMODE1
              cout << "EXPRESSION TEST MODE ON \n" << endl;
#endif
              cout << "The field at the chosen location has the following components : \n  X = " << Evaluator::instance()->getXResult() << "\n" << "  Y = " << Evaluator::instance()->getYResult() << "\n" <<   endl;
              break;
            default:
              break;
          }
        }
        break;
      case 4:
        showWorldOptionsMenu = true;
          while (showWorldOptionsMenu){                                           // Start world options menu nested loop.
            cout << "WORLD SET UP MENU \n" << endl;
            cout << "1. EXIT WORLD MENU \n" << endl;
            cout << "2. ADD PARTICLE \n" << endl;
            cout << "3. CLEAR ALL PARTICLES \n" << endl;
            cout << "4. PARTICLE CONFIGURATION TEMPLATES \n" << endl;
            cout << "5. ADD LINE \n" << endl;
            cout << "6. CLEAR ALL LINES \n" << endl;
            cout << "7. ADD TRACE \n" << endl;
            cout << "8. CLEAR ALL TRACES \n" << endl;
            getline(cin,userInputString);
            stringstream(userInputString) >> userInputInteger;
            switch (userInputInteger) {                                           // World options sub menu switch statement
              case 1:
                showWorldOptionsMenu = false;
                break;
              case 2:
                CreateCustomParticle(&userInputString, &userInputFloat, &localParticle, world);  // Create a particle with user input.
                break;
              case 3:
                world->particleVector.clear();
                cout << "\n PARTICLES CLEARED ! \n" << endl;
                break;
              case 4:
                world->particleVector.clear();
                cout << "1. Dipole. \n" << endl;
                cout << "2. Quadropole. \n" << endl;
                cout << "3. Long line charge. \n" << endl;
                cout << "4. Short line charge. \n" << endl;
                getline(cin,userInputString);
                stringstream(userInputString) >> userInputInteger;
                switch (userInputInteger) {                                      // Particle template sub sub menu switch statement
                  case 1:
                    CreateParticle(&localParticle, world, 1, 1, 2, 0, 1);        // Create a particle withouth user input.
                    CreateParticle(&localParticle, world, -1, 1, 2, 0, -1);
                    cout << " \n Dipole created \n" << endl;
                    break;
                  case 2:
                    CreateParticle(&localParticle, world, 1, 1, 2, 1, 1);
                    CreateParticle(&localParticle, world, 1, 1, 2, -1, -1);
                    CreateParticle(&localParticle, world, -1, 1, 2, -1, 1);
                    CreateParticle(&localParticle, world, -1, 1, 2, 1, -1);
                    cout << " \n Quadropole created \n" << endl;
                    break;
                  case 3:
                    for (i = 0; i < (WORLDSIZE/pixelsPerUnit)*2;i++){            // Creates a vertical line of particles on Y axis.
                      CreateParticle(&localParticle, world, 2, 1, 2, 0, i);
                      if (i > 0){                                                // Avoids placing a double charge at the origin.
                        CreateParticle(&localParticle, world, 2, 1, 2, 0, -i);
                      }
                    }
                    cout << " \n Long line charge created \n" << endl;
                    break;
                  case 4:
                    for (i = 0; i < (WORLDSIZE/pixelsPerUnit)/4;i++){            //  Shorter vertical line of particles on Y axis.
                      CreateParticle(&localParticle, world, 2, 1, 2, 0, i);
                      if (i > 0){
                        CreateParticle(&localParticle, world, 2, 1, 2, 0, -i);
                      }
                    }
                    cout << " \n Short line charge created \n" << endl;
                    break;
                  default:
                    break;
                }
                break;
              case 5:
              {
                  CreateCustomLine(&userInputString, &userInputFloat, &localLine, world);
              }
                break;
              case 6:
                  world->lineVector.clear();
                  cout << "\n LINES CLEARED ! \n" << endl;
                break;
              case 7:
                  CreateCustomTrace(&userInputString, &userInputFloat, &localTrace, world);
                break;
              case 8:
                  world->traceVector.clear();
                  cout << "\n TRACES CLEARED ! \n" << endl;
                 break;
              default:
                break;
            }
          }
          break;
        case 5:
          cout << "Setting up Visualizer Window. \n " << endl;
          for (i = 0; i < WORLDSIZE; i++){
            for (j = 0; j < WORLDSIZE; j++){
              Point temporaryPointArray((i - WORLDSIZE/2)/pixelsPerUnit,(j-WORLDSIZE/2)/pixelsPerUnit);    // Create Point with properly scaled and shifted X and Y coordinates.
              Vector2 temporaryVector2;                                                                    // Copy into world Vector2 colleciton after processing.
              world->worldArray[i * WORLDSIZE + j] = temporaryPointArray;
              Evaluator::instance()->setXValue(world->worldArray[i * WORLDSIZE + j].getX());               // Pass point coordinates to Equation Evaluator.
              Evaluator::instance()->setYValue(world->worldArray[i * WORLDSIZE + j].getY());
              Evaluator::instance()->setXResult(0);                                                        // Set Dummy evaluator results in case evaluator is in test mode.
              Evaluator::instance()->setYResult (0);
#ifdef EXPRESSIONMODE1
              if (Evaluator::instance()->getParserState())
              {
                  Evaluator::instance()->setXResult(Evaluator::instance()->getExpressionX().value());          // Set Actual evaluator results in full mode.
                  Evaluator::instance()->setYResult(Evaluator::instance()->getExpressionY().value());
              }
#endif
              temporaryVector2.setX(Evaluator::instance()->getXResult());
              temporaryVector2.setY(Evaluator::instance()->getYResult());
              world->fieldAray[i * WORLDSIZE + j] = temporaryVector2;
            }
          }
          SFMLSetUp(world->worldArray,world->fieldAray,world->particleVector,world->lineVector,world->traceVector,normalizeVectorsBeforeDisplay,pixelsPerUnit,vectorAbsolutePixelScale);
          break;
        default:
          cout << "You have selected an invalid option \n" << endl;
          break;
    }
 
  }
  return EXIT_SUCCESS;
}
