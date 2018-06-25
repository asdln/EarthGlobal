#include "JetHideCallback.h"
#include <osg/Switch>

JetHideCallback::JetHideCallback(TargetPath* ap)
{
	m_ptrTargetAnimationPath = ap;
}

JetHideCallback::~JetHideCallback()
{

}

void JetHideCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	osg::Switch* sw = dynamic_cast<osg::Switch*>(node);
	if (sw && nv)
	{
		const osg::FrameStamp* fs = nv->getFrameStamp();
		if (fs)
		{
			/*if (_fireStartFrame < fs->getSimulationTime())
			{
			sw->setValue(0, false);
			sw->setValue(1, true);
			}*/

			double animTime = fs->getSimulationTime();
			const std::map<double, osg::AnimationPath::ControlPoint>& mapCP = m_ptrTargetAnimationPath->getTimeControlPointMap();

			double modulated_time = (animTime - m_ptrTargetAnimationPath->getFirstTime()) / m_ptrTargetAnimationPath->getPeriod();
			double fraction_part = modulated_time - floor(modulated_time);
			animTime = m_ptrTargetAnimationPath->getFirstTime() + fraction_part * m_ptrTargetAnimationPath->getPeriod();

			const std::map<double, unsigned int>&  mapJetStates = m_ptrTargetAnimationPath->GetMapJetStateTag();

			const std::map<double, unsigned int>::const_iterator second = mapJetStates.lower_bound(animTime);
			unsigned int nTag = second->second;

			if (nTag == 0)
			{
				sw->setValue(0, 0);
				sw->setValue(1, 0);

				sw->setValue(2, 0);
				sw->setValue(3, 0);

				sw->setValue(4, 0);
				sw->setValue(5, 0);

				sw->setValue(6, 0);
				sw->setValue(7, 0);
			}

			if (nTag == 1)
			{
				sw->setValue(0, 1);
				sw->setValue(1, 1);

				sw->setValue(2, 0);
				sw->setValue(3, 0);

				sw->setValue(4, 0);
				sw->setValue(5, 0);

				sw->setValue(6, 0);
				sw->setValue(7, 0);
			}

			if (nTag == 2)
			{
				sw->setValue(0, 0);
				sw->setValue(1, 0);

				sw->setValue(2, 1);
				sw->setValue(3, 1);

				sw->setValue(4, 0);
				sw->setValue(5, 0);

				sw->setValue(6, 0);
				sw->setValue(7, 0);
			}

			if (nTag == 3)
			{
				sw->setValue(0, 0);
				sw->setValue(1, 0);

				sw->setValue(2, 0);
				sw->setValue(3, 0);

				sw->setValue(4, 1);
				sw->setValue(5, 1);

				sw->setValue(6, 0);
				sw->setValue(7, 0);
			}

			if (nTag == 4)
			{
				sw->setValue(0, 0);
				sw->setValue(1, 0);

				sw->setValue(2, 0);
				sw->setValue(3, 0);

				sw->setValue(4, 0);
				sw->setValue(5, 0);

				sw->setValue(6, 1);
				sw->setValue(7, 1);
			}

			if (nTag == 5)
			{
				sw->setValue(0, 1);
				sw->setValue(1, 1);

				sw->setValue(2, 1);
				sw->setValue(3, 1);

				sw->setValue(4, 0);
				sw->setValue(5, 0);

				sw->setValue(6, 0);
				sw->setValue(7, 0);
			}

			if (nTag == 6)
			{
				sw->setValue(0, 1);
				sw->setValue(1, 1);

				sw->setValue(2, 0);
				sw->setValue(3, 0);

				sw->setValue(4, 1);
				sw->setValue(5, 1);

				sw->setValue(6, 0);
				sw->setValue(7, 0);
			}

			if (nTag == 7)
			{
				sw->setValue(0, 1);
				sw->setValue(1, 1);

				sw->setValue(2, 0);
				sw->setValue(3, 0);

				sw->setValue(4, 0);
				sw->setValue(5, 0);

				sw->setValue(6, 1);
				sw->setValue(7, 1);
			}

			if (nTag == 8)
			{
				sw->setValue(0, 0);
				sw->setValue(1, 0);

				sw->setValue(2, 1);
				sw->setValue(3, 1);

				sw->setValue(4, 1);
				sw->setValue(5, 1);

				sw->setValue(6, 0);
				sw->setValue(7, 0);
			}

			if (nTag == 9)
			{
				sw->setValue(0, 0);
				sw->setValue(1, 0);

				sw->setValue(2, 1);
				sw->setValue(3, 1);

				sw->setValue(4, 0);
				sw->setValue(5, 0);

				sw->setValue(6, 1);
				sw->setValue(7, 1);
			}

			if (nTag == 10)
			{
				sw->setValue(0, 0);
				sw->setValue(1, 0);

				sw->setValue(2, 0);
				sw->setValue(3, 0);

				sw->setValue(4, 1);
				sw->setValue(5, 1);

				sw->setValue(6, 1);
				sw->setValue(7, 1);
			}

			if (nTag == 11)
			{
				sw->setValue(0, 1);
				sw->setValue(1, 1);

				sw->setValue(2, 1);
				sw->setValue(3, 1);

				sw->setValue(4, 1);
				sw->setValue(5, 1);

				sw->setValue(6, 0);
				sw->setValue(7, 0);
			}

			if (nTag == 12)
			{
				sw->setValue(0, 1);
				sw->setValue(1, 1);

				sw->setValue(2, 1);
				sw->setValue(3, 1);

				sw->setValue(4, 0);
				sw->setValue(5, 0);

				sw->setValue(6, 1);
				sw->setValue(7, 1);
			}

			if (nTag == 13)
			{
				sw->setValue(0, 1);
				sw->setValue(1, 1);

				sw->setValue(2, 0);
				sw->setValue(3, 0);

				sw->setValue(4, 1);
				sw->setValue(5, 1);

				sw->setValue(6, 1);
				sw->setValue(7, 1);
			}

			if (nTag == 14)
			{
				sw->setValue(0, 0);
				sw->setValue(1, 0);

				sw->setValue(2, 1);
				sw->setValue(3, 1);

				sw->setValue(4, 1);
				sw->setValue(5, 1);

				sw->setValue(6, 1);
				sw->setValue(7, 1);
			}

			if (nTag == 15)
			{
				sw->setValue(0, 1);
				sw->setValue(1, 1);

				sw->setValue(2, 1);
				sw->setValue(3, 1);

				sw->setValue(4, 1);
				sw->setValue(5, 1);

				sw->setValue(6, 1);
				sw->setValue(7, 1);
			}
		}
	}

	traverse(node, nv);
}
