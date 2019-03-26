#pragma once
#include "sqlite/sqlite3.h"

class CChatRecord
{
private:
	CChatRecord();
	CChatRecord(const CChatRecord &);
	CChatRecord & operator = (const CChatRecord &);
public:
	static CChatRecord & GetInstance() {
		static CChatRecord instance;
		return instance;
	}

	LONG Connect(char *dbPath);
	LONG Close();
	LONG WriteFriendChatRecord(WCHAR *friendID, int type, WCHAR *data);
	LONG WriteGroupChatRecord(WCHAR *groupID, WCHAR *memberID, int type, WCHAR *data);

private:
	sqlite3 *m_pDb;
};

