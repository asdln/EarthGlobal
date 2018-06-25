#pragma once

#include <QtCore/QString>

class Document
{
public:

	static Document* Instance()
	{
		static Document* s_document = 0;
		if(s_document == 0)
		{
			s_document = new Document;
		}
		return s_document;
	}

	const QString& GetSavePath();

	void SetSavePath(const QString& strPath);

	void CreateNewProject();

	void OpenProjectXML();

	void SaveAsProject();

	void OpenProjectXML(const QString& strPath);

	const QString& GetAirDataDir(){ return m_strAirDataDir; }

protected:

	QString m_strSavePath;

	QString m_strAirDataPath;

	QString m_strTargetDataPath;

	QString m_strAirDataDir;

	QString m_strXMLPath;

protected:

	Document();
	~Document();

	Document(const Document&);
	const Document& operator= (const Document&);
};

