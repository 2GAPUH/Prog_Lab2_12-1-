#pragma once
#include <stdlib.h>

struct descriptor
{
	int** array = NULL;
	int* columnsCount = NULL;
	int rows = 0;
};


void GetRows(int* rows);
void MainMalloc(descriptor* desc);
void ManualArrayFilling(descriptor* desc);
void ArrayPrinting(descriptor const desc);
void MemoryFree(descriptor* desc);
void GetFileName(char fileName[]);
void ArraySaveTextFile(descriptor const desc);
void TextFileArrayFilling(descriptor* desc);
void ArraySaveBinFile(descriptor const desc);
void BinFileArrayFilling(descriptor* desc);
void AddLine(descriptor* desc);
void DeleteLine(descriptor* desc);
void RowsShift(descriptor* desc);
void ColumnsShift(descriptor* desc);