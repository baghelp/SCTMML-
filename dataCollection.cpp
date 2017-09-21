/*
 * Copyright © 2012, United States Government, as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All rights reserved.
 * 
 * The NASA Tensegrity Robotics Toolkit (NTRT) v1 platform is licensed
 * under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0.
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 */

/**
 * @file dataCollection.cpp
 * @brief Implementation of dataCollection.
 * @author Drew Sabelhaus
 * $Id$
 */

// This module
#include "dataCollection.h"
// // This application
// #include "yamlbuilder/TensegrityModel.h"
// // This library
// #include "core/tgBasicActuator.h"
// #include "core/tgSpringCableActuator.h"
// #include "core/tgTags.h"
// #include "LinearMath/btVector3.h"
// #include "LinearMath/btScalar.h"
// #include "LinearMath/btMatrix3x3.h"
// #include "LinearMath/btQuaternion.h"
//
// //#include "sensors/tgDataObserver.h"
// // The C++ Standard Library
// #include <cassert>
// #include <stdexcept>
// #include <vector>
// #include <iostream>
// #include <ssteam>
// #include "helpers/FileHelpers.h"
// #include <stdexcept>
// #include <string.h>
// #include <math.h>




// Constructor assigns variables, does some simple sanity checks.
// Also, initializes the accumulator variable timePassed so that it can
// be incremented in onStep.
dataCollection::dataCollection( string outFile ) {
    
  //vector<string> rods,
  //vector<string> strings) :
  // CENTER_TIME(CENTER_TIME),
  // minTension(minTension),
  // rate(rate),
  // angleOfTravel(angleOfTravel),
  // timePassed(0.0)
  //{
  // this->minTension = minTension;
  // this->rate = rate;
  // this->angleOfTravel = angleOfTravel;
  this->outFile = outFile;
  this->timePassed =  0.0;
  // start time must be greater than or equal to zero
  if( CENTER_TIME < 0.0 ) {
    throw invalid_argument("Start time must be greater than or equal to zero.");
  }
  // minTension must be greater than some lower bound
  // else if( minTension <= 0 ) {
  //   throw invalid_argument(
  //       "Tension is not high enough. min is currently set to 1." );
  // }
  // rate must be greater than zero
  // else if( rate < 0.0 ) {
  //   throw invalid_argument("Rate cannot be negative.");
  // }
  // @TODO: what checks to make on tags?
}

/**
 * The initializeActuators method is called in onSetup to fill the cables and
 * rods arrays, as well as store the initial rest lengths in the initialRL map.
 */
void dataCollection::initializeStructure( TensegrityModel& subject ) {
  //DEBUGGING
  // Pick out the actuators and rods by tag
  cube.erase(cube.begin(), cube.end());
  rods.erase(rods.begin(), rods.end());
  cables.erase(cables.begin(), cables.end());

  // for each name in CABLES, add the corresponding cable to the cables array
  for( int i = 0; i < NUM_CABLES; i++ ) {
    string tag = CABLES[i];
    tgBasicActuator* grabbedCable = subject.find<tgBasicActuator>(tag).front();
    cables.push_back(grabbedCable);
  }
  // for each name in RODS, add the corresponding rod to the rods array
  for( int i = 0; i < NUM_RODS; i++ ) {
    string tag = RODS[i];
    tgRod* grabbedRod = subject.find<tgRod>(tag).front();
    rods.push_back(grabbedRod);
  }
  // grab the box
  string tag = CUBE;
  tgBox* box = subject.find<tgBox>(tag).front();
  cube.push_back(box);

  //for each rod in the RODS, add its end points to the nodes vector
  for( size_t i = 0; i < rods.size(); i++ ) {
    //cout<< rods[i]->toString() <<endl;
    pair< btVector3*, btVector3* > endPoints = rods[i]->ends();
    //do you have a segfault? look at this thing. maybe trying to access stuff
    //on the stack that has been overwritten
    nodes.insert( nodes.begin(), endPoints.first );
    nodes.insert( nodes.begin(), endPoints.second );
  }

  //add the middle of the cube to the nodes vector
  btVector3 bottom = btVector3();
  btVector3 top = btVector3();
  btVector3* middle = new btVector3();
  top = *(box->ends().first);
  bottom = *(box->ends().second);
  *middle = (top + bottom)/2;
  nodes.insert( nodes.begin(), middle );



}

/**
 * For this controller, the onSetup method initializes the actuators,
 * which means just store pointers to them and record their rest lengths.
 * This method calls the helper initializeActuators.
 */
void dataCollection::onSetup( TensegrityModel& subject )
{
  cout << "Setting up the dataCollection controller." << endl;
  //	    << "Finding cables with tags: " << lengthen
  //	    << endl;
  //lengthen_vector = {};
  //shorten_vector = {};
  initializeStructure( subject );
  randomizeRLengths();
  // For all the strings in the list, call initializeActuators.
  cout << "Finished setting up the controller." << endl;    
}


void dataCollection::randomizeRLengths() {
  int index = rand()%12;
  srand(time(NULL));
  // // MIN_RL + (something from 0 to 10)
  // lengths[0] = MIN_RL + ( (double) ( rand() % 10000) )/1000;
  // lengths[1] = MIN_RL + ( (double) ( rand() % 10000) )/1000;
  // lengths[2] = MIN_RL + ( (double) ( rand() % 10000) )/1000;
  // lengths[3] = MIN_RL + ( (double) ( rand() % 10000) )/1000;
  // lengths[4] = MIN_RL + ( (double) ( rand() % 10000) )/1000;
  // lengths[5] = MIN_RL + ( (double) ( rand() % 10000) )/1000;
  // lengths[6] = MIN_RL + ( (double) ( rand() % 10000) )/1000;
  // lengths[7] = MIN_RL + ( (double) ( rand() % 10000) )/1000;
  // lengths[8] = MIN_RL + ( (double) ( rand() % 10000) )/1000;
  // lengths[9] = MIN_RL + ( (double) ( rand() % 10000) )/1000;
  // lengths[10] = MIN_RL + ( (double) ( rand() % 10000) )/1000;
  // lengths[11] = MIN_RL + ( (double) ( rand() % 10000) )/1000;
 
  // Make most of them super loose, and then make one of them really tight.
  // Later, we will tighten the loose ones until they are above min_tension
  for( int i = 0; i < NUM_CABLES; i++ ) {
    lengths[i] = MAX_RL;
  }
  lengths[index] = MIN_RL + ( (double) ( rand() % 1000) )/1000;

}


btVector3 dataCollection::getDeltaModelCOM() {
  btVector3 newCOM = getModelCOM();
  // cout<< "New COM: " << newCOM <<". Old COM: "<< COM << "." <<endl;
  btVector3 diff = newCOM - COM;
  return diff;
}

btVector3 dataCollection::getModelCOM() {
  btVector3 COM_new = btVector3(0, 0, 0);
  double totalMass = 0.0;
  for( int i = 0; i < sizeof(RODS)/sizeof(RODS[0]); i++ ) {
    COM_new += rods[i]->centerOfMass()*ROD_MASS;
    totalMass += ROD_MASS;
  }
  COM_new += cube[0]->centerOfMass()*PAYLOAD_MASS;
  totalMass += PAYLOAD_MASS;
  COM_new /= totalMass;
  return COM_new;
}


/* Return true if all the cables are above the minimum tension
 */
bool dataCollection::cablesAboveTension( double minTension ) {
  bool tensionOK = true;
  for( int i = 0; i < sizeof(CABLES)/sizeof(CABLES[0]); i++ ) {
    if( cables[i]->getTension() < minTension ) {
      tensionOK = false;
    }
  }
  return tensionOK;
}


/* Write the current rest lengths and final COM data to a file. This data can then be
 * used to train Linear Regression to learn inputs in order to move the COM
 */
void dataCollection::writeData( string outFile ) {
  /* Format:
   * [1x43]: 1x3 deltaCOM, 1x3 cubeOrientation, 1x39 relative node xyz
   * locations, 1x12 rlengths
   */
  cout<< "Writing data to file "<< outFile <<"...";
  // calculate change in COM
  btVector3 diff = getModelCOM() - initialCOM;
  btVector3 nodeDiff;
  ofstream file(outFile.c_str(), ios::out | ios::app);
  if(file.is_open() ) {
    // write down change in COM
    file<< diff.getX()<<", "<<diff.getY() << ", " <<diff.getZ() <<", ";
    // write down starting orientation of cube
    file<< initialOrientation.getX()<< ", ";
    file<< initialOrientation.getY()<< ", ";
    file<< initialOrientation.getZ()<< ", ";
    for( int i = 0; i < NUM_CABLES; i++ ) {
      nodeDiff = *(nodes[i]) - initialCOM;
      file<< nodeDiff.getX()<<", "<<nodeDiff.getY() << ", " <<nodeDiff.getZ() <<", ";
    }
    // write down restLengths
    file<<
      cables[0]->getRestLength() <<", "<<
      cables[1]->getRestLength() <<", "<<
      cables[2]->getRestLength() <<", "<<
      cables[3]->getRestLength() <<", "<<
      cables[4]->getRestLength() <<", "<<
      cables[5]->getRestLength() <<", "<<
      cables[6]->getRestLength() <<", "<<
      cables[7]->getRestLength() <<", "<<
      cables[8]->getRestLength() <<", "<<
      cables[9]->getRestLength() <<", "<<
      cables[10]->getRestLength() <<", "<<
      cables[11]->getRestLength() << endl;
    file.close();
    cout<< "done!"<<endl;
  }
  else {
    cout<< "Unable to open file"<<endl;
  }
  // finished = true;
  return;
}




/* tightens some cables and lengthens others.
 */
void dataCollection::onStep(TensegrityModel& subject, double dt)
{
  timePassed += dt;


  /* Debugging */
  // if( timePassed > CENTER_TIME ) {
  //   // if enough time has passed, actuate cables
  //   for (size_t i = 0; i < cables.size(); i ++) {	
  //     cables[i]->setControlInput(0.01, dt);
  //   }
  // }
  // cout<< cables.size()<<endl;

  // Fall to a random face
  // if( timePassed < SETUP_TIME ) {
  if( simMode == 0 ) {
    randomizeRLengths();
    // if( timePassed <= dt ) {
    if( steps == 0 ) {
      cout<< "moving to random face"<<endl;
    }
    // setup superball on a random face
    for (size_t i = 0; i < cables.size(); i ++) {	
      cables[i]->setControlInput(lengths[i], dt);
    }

    steps++;
    if( steps == 20000 ) {
      simMode = 1;
      steps = 0;
    }
  }
  // Center the CUBE!!!
  // else if( (timePassed < CENTER_TIME ) ){
  else if( simMode == 1 ){
    // if( (timePassed - SETUP_TIME)<dt) {
    if( steps == 0 ) {
      cout << "re-centering cube"<<endl;
    }
    // }
    for (size_t i = 0; i < cables.size(); i ++) {	
      // cables[i]->setControlInput(triangleStart[i], dt);
      cables[i]->setControlInput(centerCube[i], dt);
    }

    steps++;
    if( steps == 25000 ) {
      simMode = 2;
      steps= 0;
    }
  }
  // get random inputs to use for the rLengths, initialize values used in future
  else if( simMode == 2 ) {
      // run this once at the beginning
      randomizeRLengths();
      initialCOM = getModelCOM();
      initialOrientation = cube[0]->orientation();
      cout<< "finding random rLengths"<<endl;

      simMode = 3;
  }
  // Set cable rest lengths to the random ones we have picked
  else if( simMode == 3) {
    if( steps == 0 ) {
      cout<< "sending commands"<<endl;
    }
    for (size_t i = 0; i < cables.size(); i ++) {	
      if( (cables[i]->getTension() < MIN_TENSION)&&
          (cables[i]->getRestLength() > MIN_RL)&&
          (steps>10000) ){
        // if cable is below min tension, shorten lengths
        lengths[i] -= RL_STEP_SIZE;
      }
      cables[i]->setControlInput(lengths[i], dt);
    }

    steps++;
    // wait for cube to slow down before writing to file
    if( steps > 50000 ) {
      if( cablesAboveTension( MIN_TENSION ) ) {
        writeData( outFile );
      }
      else{
        cout<< "Data not written to file, tensions too low" <<endl;
      }
      // /* Debugging */
      // cout<< "Done with commanded lengths: ";
      // for( int i = 0; i < 12; i++ ) {
      //   cout<< lengths[i] << ", ";
      // }
      // cout<< endl;
      // cout<< "Actual rest lengths: ";
      // for( int i = 0; i < 12; i++ ) {
      //   cout<< cables[i]->getRestLength() <<", ";
      // }
      // cout<< endl;
      steps = 0;
      simMode = 1;
    }
  }

}





/*  ///////////////// Linear Math Functions /////////////////  */

/* make a diagonal matrix out of a vector
*/
mat dataCollection::diag( vec inVec ) {

  mat diagonal = mat( inVec.size(), inVec.size() );

  for( int row = 0; row < inVec.size(); row++ ) {
    for( int col = 0; col < inVec.size(); col++ ) {
      diagonal( row, col ) = 0;
    }
  }
  for( int index = 0; index < inVec.size(); index++ ) {
    diagonal( index, index ) = inVec(index);
  }

  return diagonal;
}

/* Find the projection of vector a onto vetor e
*/
vec dataCollection::proj(vec a, vec e) { // projection of vector A onto e
  vec result = e*( inner_prod(e, a) / (inner_prod(e, e) ) );
  return result;
}


pair<mat, mat> dataCollection::grammyDecomp( mat A ) {
  // cout<< "intput to decomp: " << A <<endl;
  mat U = mat(A.size1(), A.size2() );
  mat E = mat(A.size1(), A.size2() );

  // cout<< "loops ends when col = " << A.size1()
  for( int col = 0; col < A.size2(); col++ ) {
    // cout<< "col is "<<col<<endl;
    ublas::column(U, col) = ublas::column(A, col);
    for( int j = 0; j < col; j++ ) {
      // cout<< "j is "<<j<<endl;
      ublas::column(U, col) -= proj( ublas::column(A, col), ublas::column(U, j));
      // cout<< "proj works"<<endl;
    }

    ublas::column(E, col) = ublas::column(U, col) / norm_2( ublas::column(U, col) );
  }
  mat Q = E;
  mat R = prod(ublas::trans(Q),A);
  // cout<< "U: " <<U << endl;
  // cout<< "Q: " <<Q << endl;
  // cout<< "R: " <<R << endl;
  return pair<mat, mat>(Q, R);
}


bool dataCollection::InvertMatrix(const mat* input, mat* inverse)
{
  typedef ublas::permutation_matrix<std::size_t> pmatrix;

  // create a working copy of the input
  mat A(*input);

  // create a permutation matrix for the LU-factorization
  pmatrix pm(A.size1());

  // perform LU-factorization
  int res = lu_factorize(A, pm);
  if (res != 0) {
    return false;
  }
  inverse->assign(ublas::identity_matrix<double>(A.size1(), A.size2()));

  // backsubstitute to get the inverse
  lu_substitute(A, pm, *inverse);

  return true;
}





