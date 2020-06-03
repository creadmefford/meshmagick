/*
This file is part of MeshMagick - An Ogre mesh file manipulation tool.
Copyright (C) 2007-2010 Daniel Wickert

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
THE SOFTWARE.
*/

#include "MmStatefulSkeletonSerializer.h"

#include <OgreOldSkeletonManager.h>
#include <OgreResourceGroupManager.h>

#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>

#include "MmEditableSkeleton.h"

using namespace Ogre;

namespace meshmagick
{
    const unsigned short HEADER_CHUNK_ID = 0x1000;

    v1::SkeletonPtr StatefulSkeletonSerializer::loadSkeleton(const String& name)
    {
        // Resource already created upon mesh loading?
        mSkeleton = v1::OldSkeletonManager::getSingleton().getByName(name);
        if (!mSkeleton)
        {
            // Nope. We create it here then.
            mSkeleton = v1::OldSkeletonManager::getSingleton().create(name, 
                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        }

		mSkeleton = v1::SkeletonPtr(new EditableSkeleton(*mSkeleton.get()));

        std::ifstream ifs;
        ifs.open(name.c_str(), std::ios_base::in | std::ios_base::binary);
        if (!ifs)
        {
            throw std::ios_base::failure(("cannot open file " + name).c_str());
        }

        DataStreamPtr stream(new FileStreamDataStream(name, &ifs, false));

        determineFileFormat(stream);

        importSkeleton(stream, mSkeleton.get());

        ifs.close();

		return mSkeleton;
    }

    void StatefulSkeletonSerializer::saveSkeleton(const String& name, bool keepEndianess)
    {
        if (!mSkeleton)
        {
            throw std::logic_error("No skeleton to save set.");
        }

        Endian endianMode = keepEndianess ? mSkeletonFileEndian : ENDIAN_NATIVE;
        exportSkeleton(mSkeleton.get(), name, v1::SKELETON_VERSION_LATEST, endianMode);
    }

    void StatefulSkeletonSerializer::clear()
    {
        mSkeleton.reset();
    }

    v1::SkeletonPtr StatefulSkeletonSerializer::getSkeleton() const
    {
        return mSkeleton;
    }

    void StatefulSkeletonSerializer::determineFileFormat(DataStreamPtr stream)
    {
        determineEndianness(stream);

#if OGRE_ENDIAN == OGRE_ENDIAN_BIG
        mSkeletonFileEndian = mFlipEndian ? ENDIAN_LITTLE : ENDIAN_BIG;
#else
        mSkeletonFileEndian = mFlipEndian ? ENDIAN_BIG : ENDIAN_LITTLE;
#endif
    }
}
