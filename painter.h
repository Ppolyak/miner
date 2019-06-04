#pragma once

#pragma once

class Painter
{
public:
	static const int CELL_SIZE = 16;
	void DrawClosedCell(int x, int y); //��������� �������� ������
	void DrawOpenedCell(int x, int y, int MinesAround); //��������� �������� ������
	void DrawFlag(int x, int y); //��������� �����
	void DrawMine(int x, int y); //��������� ����
	void DrawComplete(const char *text, int x, int y, int z, int u, int i, int j, int k); //����� ����
private:
	void DrawOpenedCell(int x, int y); //��������� ��������� ������.Private, ������ ��� ������������ ������ ������ ���������
};