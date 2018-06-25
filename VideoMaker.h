#ifndef VIDEOMAKER_H
#define VIDEOMAKER_H

#include <QtCore/QString>

class VideoMaker
{
public:
	VideoMaker();
	~VideoMaker();

	static void MakeVideo(const QString& strDir);

private:
	
};

#endif // VIDEOMAKER_H
