/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2019 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "MyoscillatingRotatingMotion.H"
#include "addToRunTimeSelectionTable.H"
#include "unitConversion.H"
#include <fstream>
//#include <iostream>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace solidBodyMotionFunctions
{
    defineTypeNameAndDebug(MyoscillatingRotatingMotion, 0);
    addToRunTimeSelectionTable
    (
        solidBodyMotionFunction,
        MyoscillatingRotatingMotion,
        dictionary
    );
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::solidBodyMotionFunctions::MyoscillatingRotatingMotion::
MyoscillatingRotatingMotion
(
    const dictionary& SBMFCoeffs,
    const Time& runTime
)
:
    solidBodyMotionFunction(SBMFCoeffs, runTime)
{
    read(SBMFCoeffs);
//    scalar Ampli = 0.1;
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //


#include "Amplitude_Member_Function.H"

Foam::septernion
Foam::solidBodyMotionFunctions::MyoscillatingRotatingMotion::
transformation() const
{


					
	
    scalar t = time_.value();
    
	vector eulerAngles = Amplitude()*sin(omega_*t);			//Funktion für vector Amplitude(),;
//	vector eulerAngles = amplitude_*sin(omega_*t);			//Funktion für Amplitude();



    // Convert the rotational motion from deg to rad
    eulerAngles *= degToRad();

    quaternion R(quaternion::XYZ, eulerAngles);
    septernion TR(septernion(-origin_)*R*septernion(origin_));

    DebugInFunction << "Time = " << t << " transformation: " << TR << endl;

    return TR;
}





bool Foam::solidBodyMotionFunctions::MyoscillatingRotatingMotion::read
(
    const dictionary& SBMFCoeffs
)
{
    solidBodyMotionFunction::read(SBMFCoeffs);

    SBMFCoeffs_.readEntry("origin", origin_);
//    SBMFCoeffs_.readEntry("amplitude", amplitude_);
    SBMFCoeffs_.readEntry("omega", omega_);

    return true;
}





// ************************************************************************* //