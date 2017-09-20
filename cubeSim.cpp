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
 * @file AppHorizontalSpine.cpp
 * @brief Contains the definition function main() for App3BarYAML
 * which builds an example 3 bar prism using YAML.
 * @author Andrew Sabelhaus
 * $Id$
 */

#include "cubeSim.h"

/**
 * The entry point.
 * @param[in] argc the number of command-line arguments
 * @param[in] argv argv[0] is the executable name
 * @param[in] argv argv[1] is the path of the YAML encoded structure
 * @param[in] argv argv[2] is the path of the YAML encoded structure
 * @return 0
 */
int main(int argc, char** argv)
{

    // For this YAML parser app, need to check that an argument path was
    // passed in.
    if (argv[1] == NULL)
    {
      std::cout<< "cubeSim.cpp, line 43"<<std::endl;
      throw std::invalid_argument("Not enough arguments passed in to the application. You need to specify which YAML file you would like to build, as well as a file to write data to.");
    }
    if (argv[2] == NULL)
    {
      std::cout<< "cubeSim.cpp, line 48"<<std::endl;
      throw std::invalid_argument("Not enough arguments passed in to the application. You need to specify which YAML file you would like to build, as well as a file to write data to.");
    }
  
    // create the ground and world. Specify ground rotation in radians
    const double yaw = 0.0;
    const double pitch = 0.0;
    const double roll = 0.0;
    const tgBoxGround::Config groundConfig(btVector3(yaw, pitch, roll));
    // the world will delete this
    tgBoxGround* ground = new tgBoxGround(groundConfig);

    const tgWorld::Config config(98.1); // gravity, dm/sec^2
    tgWorld world(config, ground);

    // create the view
    // const double timestep_physics = 1.f/60.f; // seconds
    const double timestep_physics = 0.0001;
    const double timestep_graphics = 1.f/60.f; // seconds
    // const double timestep_graphics = 1.0; // seconds
    tgSimViewGraphics view(world, timestep_physics, timestep_graphics);

    // create the simulation
    tgSimulation simulation(view);

    // create the models with their controllers and add the models to the simulation
    // This constructor for TensegrityModel takes the 'debugging' flag as the
    // second argument.
    cout<< std::string(argv[2]) <<endl;
    TensegrityModel* const myModel = new TensegrityModel(argv[1],false);

    // Attach a controller to the model, if desired.
    // This is a controller that interacts with a generic TensegrityModel as
    // built by the TensegrityModel file.

    // Parameters for the dataCollection are specified in that .h file,
    // repeated here:
    // double minTension = 1;
    // double rate = 9.0;
    // double angleOfTravel = 0;
    // std::vector<std::string> lengthenTags;
    // std::vector<std::string> shortenTags;
    // See the threeBarModel.YAML file to see where "vertical_string" is used.
    // lengthenTags.push_back("top_string");
    // shortenTags.push_back("bottom_string");
    //lengthenTags.push_back("cube_string");
    
    // Create the controller
    // dataCollection* const myController = new dataCollection( minTension, rate, angleOfTravel);
    dataCollection* const myController = new dataCollection( std::string( argv[2] ) );
    // FILL IN 6.6 HERE
    // FILL_IN* const myController = new FILL_IN( minLength, rate, tagsToControl);
    
    // Attach the controller to the model
    myModel->attach(myController);
    // FILL IN 6.7 HERE

    // Add the model to the world
    simulation.addModel(myModel);
    simulation.run();
    // teardown is handled by delete
    return 0;
}


