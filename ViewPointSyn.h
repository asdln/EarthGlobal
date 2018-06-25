#ifndef VIEWPOINTSYN_H
#define VIEWPOINTSYN_H

#include <QObject>

class ViewPointSyn : public QObject
{
	Q_OBJECT

public:

	ViewPointSyn(QObject* parent = NULL);
	~ViewPointSyn();

public slots:

	void slotDoSyn();
};

#endif // VIEWPOINTSYN_H
