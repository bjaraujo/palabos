/* This file is part of the Palabos library.
 *
 * Copyright (C) 2011-2015 FlowKit Sarl
 * Route d'Oron 2
 * 1010 Lausanne, Switzerland
 * E-mail contact: contact@flowkit.com
 *
 * The most recent release of Palabos can be downloaded at 
 * <http://www.palabos.org/>
 *
 * The library Palabos is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * The library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FINITE_DIFFERENCE_BOUNDARY_PROCESSOR_2D_H
#define FINITE_DIFFERENCE_BOUNDARY_PROCESSOR_2D_H

#include "core/globalDefs.h"
#include "atomicBlock/dataProcessingFunctional2D.h"
#include "atomicBlock/blockLattice2D.h"

namespace plb {

/**
* This class computes the Skordos BC
* on a flat wall in 2D but with a limited number of terms added to the
* equilibrium distributions (i.e. only the Q_i : Pi term)
*/
template<typename T, template<typename U> class Descriptor, int direction, int orientation>
class StraightFdBoundaryFunctional2D : public BoxProcessingFunctional2D_L<T,Descriptor> {
public:
    virtual void process(Box2D domain, BlockLattice2D<T,Descriptor>& lattice);
    virtual StraightFdBoundaryFunctional2D<T,Descriptor,direction,orientation>* clone() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const {
        modified[0] = modif::staticVariables;
    }
public:
    static void processCell(plint iX, plint iY, BlockLattice2D<T,Descriptor>& lattice);
private:
    template<int deriveDirection>
    static void interpolateGradients (
            BlockLattice2D<T,Descriptor> const& lattice,
            Array<T,Descriptor<T>::d>& velDeriv, plint iX, plint iY );
    virtual int getStaticId() const { return staticId; }
    static const int staticId;
};

/**
* This class computes the Skordos BC in 2D on a convex
* corner but with a limited number of terms added to the
* equilibrium distributions (i.e. only the Q_i : Pi term)
*/
template<typename T, template<typename U> class Descriptor, int xNormal, int yNormal>
class OuterVelocityCornerFunctional2D : public BoxProcessingFunctional2D_L<T,Descriptor>
{
public:
    virtual void process(Box2D domain, BlockLattice2D<T,Descriptor>& lattice);
    virtual OuterVelocityCornerFunctional2D<T,Descriptor,xNormal,yNormal>* clone() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const {
        modified[0] = modif::staticVariables;
    }
    virtual int getStaticId() const { return staticId; }
public:
    static void processCell(plint iX, plint iY, BlockLattice2D<T,Descriptor>& lattice);
    static const int staticId;
};

}  // namespace plb

#endif  // FINITE_DIFFERENCE_BOUNDARY_PROCESSOR_2D_H
