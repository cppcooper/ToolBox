#pragma region "MIT License"

/*
v1.0.1
The MIT License (MIT)

Copyright (c) <2015> <Josh S, Cooper>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.*/

#pragma endregion

#ifndef _ASSETFACULTIES_H
#define _ASSETFACULTIES_H

#pragma region "Why, What, and the Problems With"

/* BUT FIRST, A FRIENDLY DISCLAIMER:
This body of work was designed and implemented as a self-learning exercise, and
as such it gives little consideration to data locality. As a useful component to an
optimized game engine, this codebase certainly would not be contributing any
optimizations. Though future versions may in fact be redesigned for data locality
and have optimized algorithms.


More on this as a research project.. =)
--------------------------------------------------------------------------
Excuse the unoriginal basis for this analogy.

I strongly believe the best way to learn how to create a wheel is to re-invent the wheel.
If you can understand the purpose for a wheel, and you can come up with a reason to
use a wheel, then you are able to design a wheel without ever having seen a wheel.

By designing a solution to a problem you end up forcing yourself to explore many
lines of thought. During the planning you can find more problems with a particular
branch of designs. When you begin implementing you find more things that need
to be redesigned. Of course after you're finished you see the, sometimes, many
different problems with the final design you came up with.

By first learning "the best known way" to implement a design pattern I'd be
making it harder to understand or learn, tangibly, why it is "the best known way".
Furthermore, I'd find it impossible to imagine ways of possibly improving upon it.
--------------------------------------------------------------------------

New features not withstanding, this project was for compiling a static library devoted
to implementing core asset features. Eg. The code that loads an image as a texture.
While I was in the neigbourhood I decided features for managing these derived assets
would be a smart idea now instead of later. Though derived assets may be warrant
separation later on; however due to the coupling of assets to their own management,
that may prove extremely difficult.

The features I was interested in were the following:
*Centralized Memory Allocation
*Generic Object Pooling
*Generic Object Factories
*Automated Generic Loading
*Generic Object Retrieval

*/

//TODO: Remove using namespace from the headers global space
#pragma endregion

#include "InterAccess.h"

#include "Components/Storage.h"
#include "Components/Pool.h"
#include "Components/Factory.h"
#include "Components/AssetMgr.h"
#include "Components/Loader.h"

#include "AssetTypes/BasicTypes.h"
#include "AssetTypes/Graphic.h"
#include "AssetTypes/TileSet.h"
#include "AssetTypes/Sprite.h"
#include "AssetTypes/Font.h"
#include "AssetTypes/Mesh.h"
#include "AssetTypes/SceneNodes.h"

#ifdef _DEBUG
#pragma comment (lib,"Cheryl-Engine/AssetFaculties_Debug.lib")
#else
#pragma comment (lib,"Cheryl-Engine/AssetFaculties_Release.lib")
#endif

#endif