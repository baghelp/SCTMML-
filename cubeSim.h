
#ifndef CUBE_SIM_H
#define CUBE_SIM_H

/**
 * @file cubeSim.h
 * @brief has stuff I intend to use for data collection on superball
 * @author Michael Bagherpour, heavily ripping off Drew Sabelhaus
 */


// This application
#include "yamlbuilder/TensegrityModel.h"
#include "dataCollection.h"
// This library
#include "core/terrain/tgBoxGround.h"
#include "core/tgModel.h"
#include "core/tgSimulation.h"
#include "core/tgSimViewGraphics.h"
#include "core/tgWorld.h"
// Bullet Physics
#include "LinearMath/btVector3.h"
// The C++ Standard Library
#include <iostream>
#include <string>
#include <vector>
#include "cubeSim.h"


#define MIN_RL 0.5
#define MAX_RL 10
#define RL_STEP 1


double rLength[12] = {1, 9, 9, 1,
1, 1, 1, 1,9, 1, 1, 1};

#endif // CUBE_SIM_H
