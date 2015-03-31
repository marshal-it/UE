#include "MyProject.h"
#include "BinaryLoadItem.h"
#include "ByteBuffer.h"

//UBinaryLoadItem::UBinaryLoadItem(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//
//}

void UBinaryLoadItem::loadFile(const FString& Filename)
{
	// if the file has some data in it, read it in
	if (IFileManager::Get().FileSize(*Filename) >= 0)
	{
		FString Text;
		if (FFileHelper::LoadFileToString(Text, *Filename))
		{
			ByteBuffer* fileBU = new ByteBuffer(Text.GetAllocatedSize());
			fileBU->writeBytes(TCHAR_TO_ANSI(Text.GetData()), 0, Text.GetAllocatedSize());
		}
	}
}