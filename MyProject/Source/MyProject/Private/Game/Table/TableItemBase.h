﻿#ifndef __TableItemBase_H_
#define __TableItemBase_H_

#include "HAL/Platform.h"

class TableItemHeader;
class TableItemBodyBase;
class ByteBuffer;

class TableItemBase
{
public:
	TableItemHeader* m_itemHeader;
    TableItemBodyBase* m_itemBody;

public:
	TableItemBase();
	virtual void parseHeaderByteArray(ByteBuffer* bytes);

	template <class T>
	void parseBodyByteArray(ByteBuffer* bytes, uint32 offset);

	template <class T>
	void parseAllByteArray(ByteBuffer* bytes);
};

template <class T>
void TableItemBase::parseBodyByteArray(ByteBuffer* bytes, uint32 offset)
{
	if (nullptr == m_itemBody)
	{
		m_itemBody = (TableItemBodyBase *)new T();
	}

	m_itemBody->parseBodyByteArray(bytes, offset);
}

template <class T>
void TableItemBase::parseAllByteArray(ByteBuffer* bytes)
{
	// 解析头
	parseHeaderByteArray(bytes);
	// 保存下一个 Item 的头位置
	UtilTable::m_prePos = bytes->position;
	// 解析内容
	parseBodyByteArray<T>(bytes, m_itemHeader->m_offset);
	// 移动到下一个 Item 头位置
	bytes->pos(UtilTable::m_prePos);
}

#endif