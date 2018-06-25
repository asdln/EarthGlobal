#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include "CameraPath.h"
#include "TargetPath.h"
#include "TargetDataReader.h"

#include <QtCore/QString>

class AnimationController
{
public:

	static AnimationController* Instance()
	{
		static AnimationController* s_pbuffer = 0;
		if(s_pbuffer == 0)
		{
			s_pbuffer = new AnimationController;
		}
		return s_pbuffer;
	}

	static int GetCaptureFrameIndex();

	static void BeginPathFrame(int nStartIndex = 0);

	static void EndPathFrame();

	//是否正在按帧输出图像
	static bool IsPathFrameRunning();

	static void CaptureFrameIndexIncrement();

public:

	void StartAnimation();

	void StopAnimation();

	void OutputAnimation();


	void LoadCameraPath(const QString& strPath);

	void LoadTargetPath(const QString& strPath);

	void LoadAirData(const QString& strPath, double dResX = 1.0, double dResY = 1.0);

	void LoadTargetData(const TargetDataPara& para);

	CameraPath* GetCameraPath() { return m_ptrCameraAnimationPath.get(); }

	TargetPath* GetTargetPath() { return m_ptrTargetAnimationPath.get(); }

protected:

	osg::ref_ptr<CameraPath> m_ptrCameraAnimationPath;
	osg::ref_ptr<TargetPath> m_ptrTargetAnimationPath;

	QString m_strCameraAnimationPath;
	QString m_strTargetAnimationPath;

protected:

	AnimationController();
	~AnimationController();

	AnimationController(const AnimationController&);
	const AnimationController& operator= (const AnimationController&);
	
};

#endif // ANIMATIONCONTROLLER_H
