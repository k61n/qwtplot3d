#ifndef qwt3d_io_gl2ps_h__2004_05_07_01_16_begin_guarded_code
#define qwt3d_io_gl2ps_h__2004_05_07_01_16_begin_guarded_code

#include <time.h>

#include "qwt3d_types.h"
#include "qwt3d_io.h"

namespace Qwt3D
{

//! Provides EPS, PS, PDF and TeX output
/*!

 */
class QWT3D_EXPORT VectorWriter : public IO::Functor
{
friend class IO;

public:
	//! The possible output formats for the text parts of the scene
	enum TEXTMODE
	{
		PIXEL, //!< All text will be converted to pixmaps
		NATIVE, //!< Text output in the native output format
		TEX //!< Text output in additional LaTeX file as an overlay
	};
	//! The possible behaviour for landscape settings
	enum LANDSCAPEMODE
	{
		ON,  //!< Landscape mode on
		OFF, //!< Landscape mode off
		AUTO //!< The output orientation depends on the plot widgets aspect ratio (default)
	};

	//! The possible sorting types which are translated in gl2ps types
	enum SORTMODE
	{
		NOSORT,  //!< No sorting at all
		SIMPLESORT, //!< A more simple (yet quicker) algorithm (default)
		BSPSORT //!< BSP SORT (best and slow!)
	};

	VectorWriter();

	void setLandscape(LANDSCAPEMODE val) {landscape_ = val;} //!< Sets landscape mode.
	LANDSCAPEMODE landscape() const {return landscape_;} //!< Returns the current landscape mode

	void setTextMode(TEXTMODE val, QString fname = "");
	TEXTMODE textMode() const {return textmode_;} //!< Return current text output mode.

	void setExportSize(const QSize& size){export_size_ = size;};//!< Sets a custom output size.
	QSize exportSize(){return export_size_;};//!< Return current output size.

	//! Sets one of the SORTMODE sorting modes.
	void setSortMode(SORTMODE val) {sortmode_ = val;}
	SORTMODE sortMode() const {return sortmode_;} //!< Returns gl2ps sorting type.
	//! Turns compressed output on or off (no effect if zlib support is not available)
	void setCompressed(bool val);
	//! Returns compression mode (always false if zlib support has not been set)
	bool compressed() const {return compressed_;}

	bool setFormat(QString const& format);

private:
	IO::Functor* clone() const;
	bool operator()(Plot3D* plot, QString const& fname);
	bool operator()(QImage* image, QString const& fname)
	{
	Q_UNUSED(image); Q_UNUSED(fname); return false;		// Can't vectorise a bitmap image.
	}

	GLint gl2ps_format_;
	bool formaterror_;
	bool compressed_;
	SORTMODE sortmode_;
	LANDSCAPEMODE landscape_;
	TEXTMODE textmode_;
	QString texfname_;
	QSize export_size_;
};

GLint setDeviceLineWidth(GLfloat val);
GLint setDevicePointSize(GLfloat val);
GLint drawDevicePixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
GLint drawDeviceText(const char* str, const char* fontname, int fontsize, Qwt3D::Triple pos, Qwt3D::RGBA rgba, Qwt3D::ANCHOR align, double gap, double angle);
void setDevicePolygonOffset(GLfloat factor, GLfloat units);


} // ns

#endif /* include guarded */
