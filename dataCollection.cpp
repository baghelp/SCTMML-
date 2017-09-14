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
dataCollection::dataCollection(double startTime,
    double minTension,
    double rate,
    double angleOfTravel) {
  //vector<string> rods,
  //vector<string> strings) :
  // startTime(startTime),
  // minTension(minTension),
  // rate(rate),
  // angleOfTravel(angleOfTravel),
  // timePassed(0.0)
  //{
  this->startTime = startTime;
  this->minTension = minTension;
  this->rate = rate;
  this->angleOfTravel = angleOfTravel;
  this->timePassed =  0.0;
  // start time must be greater than or equal to zero
  if( startTime < 0.0 ) {
    throw invalid_argument("Start time must be greater than or equal to zero.");
  }
  // minTension must be greater than some lower bound
  else if( minTension <= 0 ) {
    throw invalid_argument(
        "Tension is not high enough. min is currently set to 1." );
  }
  // rate must be greater than zero
  else if( rate < 0.0 ) {
    throw invalid_argument("Rate cannot be negative.");
  }
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
  for( int i = 0; i < sizeof(CABLES)/sizeof(CABLES[0]); i++ ) {
    string tag = CABLES[i];
    tgBasicActuator* grabbedCable = subject.find<tgBasicActuator>(tag).front();
    cout<< "cable length: " << grabbedCable->getRestLength() <<endl;
    cout<< "cable tension: " << grabbedCable->getRestLength() <<endl;
    cables.push_back(grabbedCable);
  }
  // for each name in RODS, add the corresponding rod to the rods array
  for( int i = 0; i < sizeof(RODS)/sizeof(RODS[0]); i++ ) {
    string tag = RODS[i];
    tgRod* grabbedRod = subject.find<tgRod>(tag).front();
    rods.push_back(grabbedRod);
  }
  // grab the box
  string tag = CUBE;
  tgBox* box = subject.find<tgBox>(tag).front();

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
  btVector3 top = btVector3();
  btVector3* middle = new btVector3();
  btVector3 bottom = btVector3();
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
  initializeController();
  // For all the strings in the list, call initializeActuators.
  cout << "Finished setting up the controller." << endl;    
  moveTheBall( 1, 1, 1);
}


void dataCollection::moveTheBall( double x, double y, double z ) {
  // 1.create connectivity matrix, calling from and to to get points and stuff
  int rodsAndCables = 12 + 6;
  int nodes = 12 + 12;
  double Connectivity[nodes][rodsAndCables];
}

void dataCollection::initializeController() {

  for( rLength[1] = MIN_RL; rLength[1] < MAX_RL; rLength[1]+=0.25 ) {
    for( rLength[2] = MIN_RL; rLength[2] < MAX_RL; rLength[2]+=0.25 ) {
      for( rLength[3] = MIN_RL; rLength[3] < MAX_RL; rLength[3]+=0.25 ) {
        for( rLength[4] = MIN_RL; rLength[4] < MAX_RL; rLength[4]+=0.25 ) {
          for( rLength[5] = MIN_RL; rLength[5] < MAX_RL; rLength[5]+=0.25 ) {
            for( rLength[6] = MIN_RL; rLength[6] < MAX_RL; rLength[6]+=0.25 ) {
              for( rLength[7] = MIN_RL; rLength[7] < MAX_RL; rLength[7]+=0.25 ) {
                for( rLength[8] = MIN_RL; rLength[8] < MAX_RL; rLength[8]+=0.25 ) {
                  for( rLength[9] = MIN_RL; rLength[9] < MAX_RL; rLength[9]+=0.25 ) {
                    for( rLength[10] = MIN_RL; rLength[10] < MAX_RL; rLength[10]+=0.25 ) {
                      for( rLength[11] = MIN_RL; rLength[11] < MAX_RL; rLength[11]+=0.25 ) {
                        for( rLength[12] = MIN_RL; rLength[12] < MAX_RL; rLength[12]+=0.25 ) {


                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}



/* old playing around-thing, tightens some cables and lengthens others.
 * maintains a min tension as well
 */
void dataCollection::onStep(TensegrityModel& subject, double dt)
{
  double nextRestLength;
  double currRestLength;
  double minRestLength;
  timePassed += dt;

  /*
   * 1. Recalculate center of mass 
   *    a. if change is below threshold and all ropes
   * maintain the minimum tension:
   *       i. print the commanded rLengths and the output
   * center of mass to a file
   *       ii. while(true) {
   *          increase rLengths[index] by 0.25.
   *          if(rLengths[index]>MAX_RL) {
   *             set rLengths[index] to MIN_RL
   *             increment index. if index > 
   *          else{
   *             break;
   *          }
   *
   *               
   *
   * 2. increment the current rLengths index

  /*
     if( timePassed > startTime ) {
  // if enough time has passed, actuate cables
  for (size_t i = 0; i < shorten_vector.size(); i ++) {	
  // shorten the cables in shorten_vector
  currRestLength = shorten_vector[i]->getRestLength();
  // Calculate the minimum rest length for this cable.
  // Remember that minLength is a percent.
  minRestLength = initialRL[shorten_vector[i]->getTags()] * minLength;
  // If the current rest length is not too small
  if( currRestLength > minRestLength ) {
  // output a progress bar for the controller, to track when control occurs.
  cout << ".";
  nextRestLength = currRestLength - rate * dt;
  //DEBUGGING
  //cout << "Next Rest Length: " << nextRestLength << endl;
  shorten_vector[i]->setControlInput(nextRestLength,dt);
  }
  }   
  for (size_t i = 0; i < lengthen_vector.size(); i ++) {	
  // lengthen the cables in lengthen_vector
  currRestLength = lengthen_vector[i]->getRestLength();
  // Calculate the minimum rest length for this cable.
  // Remember that minLength is a percent.
  minRestLength = initialRL[lengthen_vector[i]->getTags()] * minLength;
  // If the current rest length is not too small
  if( lengthen_vector[i]->getTension() > 1 ){
  // output a progress bar for the controller, to track when control occurs.
  cout << "lengthen";
  nextRestLength = currRestLength + rate * dt;
  //DEBUGGING
  //cout << "Next Rest Length: " << nextRestLength << endl;
  lengthen_vector[i]->setControlInput(nextRestLength,dt);
  }
  else if( currRestLength > minRestLength) {
  cout << "shorten";
  nextRestLength = currRestLength - rate * dt;
  //DEBUGGING
  //cout << "Next Rest Length: " << nextRestLength << endl;
  lengthen_vector[i]->setControlInput(nextRestLength,dt);
  }

  }   
  }
  */
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





