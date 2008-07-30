/*
This file is part of MeshMagick - An Ogre mesh file manipulation tool.
Copyright (C) 2007 - Daniel Wickert

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef __MM_TOOL_UTILS_H__
#define __MM_TOOL_UTILS_H__

#include "MeshMagickPrerequisites.h"

#include <OgreAxisAlignedBox.h>
#include <OgreMatrix3.h>
#include <OgreMatrix4.h>
#include <OgreVector3.h>
#include <OgreVector4.h>

namespace meshmagick
{
    /// General purpose utility functions, what doesn't fit elsewhere fits here.
    class _MeshMagickExport ToolUtils
    {
    public:
        static Ogre::String getPrettyVectorString(const Ogre::Vector3&, unsigned short precision=2,
            unsigned short width=0, char fill= ' ', std::ios::fmtflags flags=std::ios::fmtflags(0));
        static Ogre::String getPrettyVectorString(const Ogre::Vector4&, unsigned short precision=2,
            unsigned short width=0, char fill= ' ', std::ios::fmtflags flags=std::ios::fmtflags(0));
        static Ogre::String getPrettyAabbString(const Ogre::AxisAlignedBox&, unsigned short precision=2,
            unsigned short width=0, char fill= ' ', std::ios::fmtflags flags=std::ios::fmtflags(0));
        static Ogre::String getPrettyMatrixString(const Ogre::Matrix4&, unsigned short precision=2,
            unsigned short width=0, char fill= ' ', std::ios::fmtflags flags=std::ios::fmtflags(0));
        static Ogre::String getPrettyMatrixString(const Ogre::Matrix3&, unsigned short precision=2,
            unsigned short width=0, char fill= ' ', std::ios::fmtflags flags=std::ios::fmtflags(0));
    };
}
#endif