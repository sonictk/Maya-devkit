//-
// Copyright 2012 Autodesk, Inc.  All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license agreement
// provided at the time of installation or download, or which otherwise
// accompanies this software in either electronic or hard copy form.
//+

#ifndef CUSTOMTEXTURESHADEROVERRIDE_H
#define CUSTOMTEXTURESHADEROVERRIDE_H

#include <maya/MPxShaderOverride.h>
#include <maya/MShaderManager.h>


class customTextureShaderOverride : public MHWRender::MPxShaderOverride
{
public:
	customTextureShaderOverride(const MObject& obj);
	static MHWRender::MPxShaderOverride* Creator(const MObject& obj);

	virtual ~customTextureShaderOverride();

	virtual MString initialize( const MInitContext& initContext,MInitFeedback& initFeedback);
	MHWRender::MShaderInstance* shaderInstance() const;

	virtual void updateDG(MObject object);
	virtual void updateDevice();
	virtual void endUpdate();

	virtual bool handlesDraw(MHWRender::MDrawContext& context);
	virtual void activateKey(MHWRender::MDrawContext& context, const MString& key);
	virtual bool draw(MHWRender::MDrawContext& context,const MHWRender::MRenderItemList& renderItemList) const;
	virtual void terminateKey(MHWRender::MDrawContext& context, const MString& key);

	virtual MHWRender::DrawAPI supportedDrawAPIs() const;
	virtual bool isTransparent();
	virtual bool overridesDrawState();

private:
	void updateShaderInstance();
	void generateCustomTexture();
	void buildAndUpdateCustomDataTextureViaMaya();

	// beauty shader
	MHWRender::MShaderInstance *m_beautyShaderInstance;

	bool m_shaderBound;
	bool m_inBeautyPass;

	// custom texture data:
	unsigned char* m_customTextureData;
	MHWRender::MTextureDescription m_desc;
};

#endif