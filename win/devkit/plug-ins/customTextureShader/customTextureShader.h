//-
// Copyright 2012 Autodesk, Inc.  All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license agreement
// provided at the time of installation or download, or which otherwise
// accompanies this software in either electronic or hard copy form.
//+

#ifndef CUSTOMTEXTURENODE_H
#define CUSTOMTEXTURENODE_H

#include <maya/MPxHardwareShader.h>

class customTextureShader : public MPxHardwareShader
{
public:
	customTextureShader();
	~customTextureShader();

	static void* creator();
	static MStatus initialize();
	virtual MStatus	render(MGeometryList& iterator);

	static const MTypeId m_TypeId;
	static const MString m_TypeName;
	static const MString m_RegistrantId;
	static const MString m_drawDbClassification;
};


#endif