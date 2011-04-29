#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuTextBlock.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	typedef const char* TOE_CHAR_Z;

	int32 ExtractUtfCode(TOE_CHAR_Z & c)
	{
		if (!*c)
			return -1;
		int32 r = (uint8)*c;
		++c;
		if (0==(r & 0x080))
			return r;
		if (0x0C0 == (r & 0x0E0))
		{
			r = r&0x01F;
			r = (r<<6) | (0x3F&(uint8)*c);
			++c;
		}
		else if (0x0E0 == (r & 0x0F0))
		{
			r = r&0x0F;
			r = (r<<6) | (0x3F&(uint8)*c);
			++c;
			r = (r<<6) | (0x3F&(uint8)*c);
			++c;
		}
		else if (0x0F0 == (r & 0x0F8))
		{
			r = r&0x07;
			r = (r<<6) | (0x3F&(uint8)*c);
			++c;
			r = (r<<6) | (0x3F&(uint8)*c);
			++c;
		}
		return r;
	}
	bool IsWhiteSpace(int32 code)
	{
		if (code == ' ' || code == '\t')
			return true;
		return false;
	}
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuTextBlock);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuTextBlock);

//Constructor
CtoeSimpleMenuTextBlock::CtoeSimpleMenuTextBlock()
{
	utf8string = 0;
}
//Desctructor
CtoeSimpleMenuTextBlock::~CtoeSimpleMenuTextBlock()
{
	if (utf8string)
	{
		delete [] utf8string;
		utf8string= 0;
	}
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuTextBlock::Serialise ()
{
	CtoeSimpleMenuItem::Serialise();
	size_t len = 0;
	if (IwSerialiseIsReading())
	{
		IwSerialiseUInt32(len);
		if (len)
		{
			utf8string = new char[len+1];
			IwSerialiseString(utf8string);
		}
	}
	else
	{
		if (utf8string)
		{
			len = strlen(utf8string);
			IwSerialiseUInt32(len);
			IwSerialiseString(utf8string);
		}
		else
		{
			IwSerialiseUInt32(len);
		}
	}
}
void CtoeSimpleMenuTextBlock::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	cachedGlyphs.clear();
	totalGlyphs = 0;
	int16 xPos=IwGxGetScreenWidth()/2;
	int16 yPos=10;
	bool leftToRight = true;
	if (utf8string > 0)
	{
		CtoeFreeTypeFont* f = renderContext->font;
		const char* c = utf8string;
		bool newWord = true;
		while (*c)
		{
			int32 code = ExtractUtfCode(c);
			if (code < 0) break;
			if (IsWhiteSpace(code))
			{
				newWord = true;
				continue;
			}
			if (code == '\n')
			{
				xPos =IwGxGetScreenWidth()/2;
				yPos += 32;
				newWord = true;
			}
			bool isCurrentleftToRight = CtoeFreeTypeFont::IsRightToLeft(code);
			newWord |= isCurrentleftToRight!=leftToRight;
			leftToRight = isCurrentleftToRight;
			CtoeFreeTypeGlyph* glyph = f->GetGlyph(code, renderContext->fontSize);
			if (glyph)
			{
				if (newWord)
				{
					cachedGlyphs.push_back();
					newWord = false;
				}
				cachedGlyphs.back().push_back();
				CtoeCachedGlyphData & g = cachedGlyphs.back().back();
				g.texture = glyph->texture;
				g.uv.x = glyph->x*IW_GEOM_ONE/TOE_GLYPHATLASSIZE;
				g.uv.y = glyph->y*IW_GEOM_ONE/TOE_GLYPHATLASSIZE;
				g.uvSize.x = (glyph->width)*IW_GEOM_ONE/TOE_GLYPHATLASSIZE;
				g.uvSize.y = (glyph->height)*IW_GEOM_ONE/TOE_GLYPHATLASSIZE;
				g.stepX = glyph->width;
				g.stepY = glyph->height;
				if (glyph->advance.x < 0)
					xPos+=glyph->advance.x;
				g.pos.x = xPos+glyph->offset.x;
				g.pos.y = yPos+glyph->offset.y;
				g.size.x = glyph->width;
				g.size.y = glyph->height;
				if (glyph->advance.x > 0)
					xPos+=glyph->advance.x;
				++totalGlyphs;
			}
		}
	}

}
//Render image on the screen surface
void CtoeSimpleMenuTextBlock::Render(toeSimpleMenuItemContext* renderContext)
{
	if (totalGlyphs == 0)
		return;

	int index = 0;
	CIwMaterial* m=0;
	CIwTexture* prevTex=0;
	IwGxLightingOff();
	for (CIwArray<CIwArray<CtoeCachedGlyphData> >::iterator word=cachedGlyphs.begin(); word!=cachedGlyphs.end();++word)
	{
		for (CIwArray<CtoeCachedGlyphData>::iterator glyph=word->begin(); glyph!=word->end();++glyph)
		{
			if (prevTex != glyph->texture)
			{
				prevTex = glyph->texture;
				m = IW_GX_ALLOC_MATERIAL();
				m->SetTexture(prevTex);
				m->SetColEmissive(255,255,255,255);
				m->SetColDiffuse(255,255,255,255);
				m->SetAlphaMode(CIwMaterial::ALPHA_BLEND);
				IwGxSetMaterial(m);
			}
			static CIwColour col[4];
			col[0].Set(0xFFFFFFFF);
			col[1].Set(0xFFFFFFFF);
			col[2].Set(0xFFFFFFFF);
			col[3].Set(0xFFFFFFFF);
			IwGxDrawRectScreenSpace (&glyph->pos,&glyph->size,&glyph->uv,&glyph->uvSize,col);
		}
	}
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuTextBlock::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("text",pAttrName))
	{
		utf8string = pParser->ReadString();
		return true;
	}
	return CtoeSimpleMenuItem::ParseAttribute(pParser, pAttrName);
}

#endif
