/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 2.1                               *
 *                                                                       *
 * "forceModel" library , Copyright (C) 2007 CMU, 2009 MIT, 2014 USC     *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Research: Jernej Barbic, Fun Shing Sin, Daniel Schroeder,             *
 *           Doug L. James, Jovan Popovic                                *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
 *          Singapore-MIT GAMBIT Game Lab,                               *
 *          Zumberge Research and Innovation Fund at USC                 *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of the BSD-style license that is            *
 * included with this library in the file LICENSE.txt                    *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the file     *
 * LICENSE.TXT for more details.                                         *
 *                                                                       *
 *************************************************************************/

/*
  Force model corresponding to the StVK material.
*/

#ifndef _STVKFORCEMODEL_H_
#define _STVKFORCEMODEL_H_

#include "StVKInternalForces.h"
#include "StVKStiffnessMatrix.h"
#include "forceModel.h"

class StVKForceModel : virtual public ForceModel
{
public:
  StVKForceModel(StVKInternalForces * stVKInternalForces, StVKStiffnessMatrix * stVKStiffnessMatrix=NULL);
  virtual ~StVKForceModel(); 
//  void GetForceAndTangentStiffnessMatrix(double* u, double* internalForces, SparseMatrix* tangentStiffnessMatrix);
  virtual void GetInternalForce(double * u, double * internalForces);
  virtual void GetTangentStiffnessMatrixTopology(SparseMatrix ** tangentStiffnessMatrix);
  virtual void GetTangentStiffnessMatrix(double * u, SparseMatrix * tangentStiffnessMatrix); 

protected:
  StVKInternalForces * stVKInternalForces;
  StVKStiffnessMatrix * stVKStiffnessMatrix;
  bool ownStiffnessMatrix;
};

#endif

