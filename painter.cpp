#include "pch.h"
#include "painter.h"
#include <glut.h>
#include <cmath>
#include <windows.h>
#include "game.h"
#include <string.h>
#include <iostream>

static const double PI = 3.1415926;

void Painter::DrawClosedCell(int x, int y) //��������� �������� ������
{
	glColor3f(0.8f, 0.8f, 0.8f); //����� ����� //������-�����
	glBegin(GL_QUADS); //��������� ��������
	glVertex2f(x * CELL_SIZE, y * CELL_SIZE); //������ ����������
	glVertex2f((x + 1) * CELL_SIZE, y * CELL_SIZE); //������ ����������
	glVertex2f((x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE); //������ ����������
	glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE); //�������� ����������
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES); //��������� ����������� �����
	glVertex2f(x * CELL_SIZE, y * CELL_SIZE);
	glVertex2f((x + 1) * CELL_SIZE - 1, y * CELL_SIZE);
	glVertex2f(x * CELL_SIZE, y * CELL_SIZE);
	glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE - 1);
	glEnd();

	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_LINES); //��������� ����������� �����
	glVertex2f((x + 1) * CELL_SIZE - 1, y * CELL_SIZE);
	glVertex2f((x + 1) * CELL_SIZE - 1, (y + 1) * CELL_SIZE - 1);
	glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE - 1);
	glVertex2f((x + 1) * CELL_SIZE - 1, (y + 1) * CELL_SIZE - 1);
	glEnd();
}

void Painter::DrawOpenedCell(int x, int y, int MinesAround) //��������� �������� ������
{
	DrawOpenedCell(x, y);
	if (MinesAround > 0)
	{
		switch (MinesAround)
		{
		case 1:
			glColor3f(0.0f, 1.0f, 0.0f); //�������
			break;
		case 2:
			glColor3f(0.0f, 0.0f, 1.0f); //�����
			break;
		case 3:
			glColor3f(1.0f, 0.0f, 0.0f); //�������
			break;
		case 4:
			glColor3f(0.0f, 0.3f, 0.0f); //Ҹ���-�������
			break;
		case 5:
			glColor3f(0.3f, 0.0f, 0.0f); //����������
			break;
		case 6:
			glColor3f(0.0f, 1.0f, 1.0f); //�������
			break;
		case 7:
			glColor3f(0.1f, 0.1f, 0.1f); //׸����
			break;
		case 8:
			glColor3f(0.9f, 0.0f, 0.0f); //���������
			break;
		}

		glRasterPos2f(x * CELL_SIZE + 2, (y + 1) * CELL_SIZE - 4); //��������� ����� � ������������ ������
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + MinesAround);
	}
}

void Painter::DrawFlag(int x, int y)
{
	glColor3f(0.8f, 0.8f, 0.8f); //����� ����� //������-�����
	glBegin(GL_QUADS); //��������� ��������
	glVertex2f(x * CELL_SIZE, y * CELL_SIZE); //������ ����������
	glVertex2f((x + 1) * CELL_SIZE, y * CELL_SIZE); //������ ����������
	glVertex2f((x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE); //������ ����������
	glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE); //�������� ����������
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES); //��������� ����������� �����
	glVertex2f(x * CELL_SIZE, y * CELL_SIZE);
	glVertex2f((x + 1) * CELL_SIZE - 1, y * CELL_SIZE);
	glVertex2f(x * CELL_SIZE, y * CELL_SIZE);
	glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE - 1);
	glEnd();

	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_LINES); //��������� ����������� �����
	glVertex2f((x + 1) * CELL_SIZE - 1, y * CELL_SIZE);
	glVertex2f((x + 1) * CELL_SIZE - 1, (y + 1) * CELL_SIZE - 1);
	glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE - 1);
	glVertex2f((x + 1) * CELL_SIZE - 1, (y + 1) * CELL_SIZE - 1);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + 1);
	glVertex2f(x * CELL_SIZE + CELL_SIZE / 2, (y + 1) * CELL_SIZE - 3);
	glVertex2f(x * CELL_SIZE + CELL_SIZE / 2 - 2.5, (y + 1) * CELL_SIZE - 3);
	glVertex2f(x * CELL_SIZE + CELL_SIZE / 2 + 2.5, (y + 1) * CELL_SIZE - 3);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + 1);
	glVertex2f(x * CELL_SIZE + CELL_SIZE / 2 - 3, y * CELL_SIZE + 4);
	glVertex2f(x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + 7);
	glEnd();
}

void Painter::DrawMine(int x, int y)
{
	DrawOpenedCell(x, y);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 360; ++i)
	{
		glVertex2f(x * CELL_SIZE + CELL_SIZE / 2 + 5 * cos(2 * PI * i / 360) - 1.5,
			y * CELL_SIZE + CELL_SIZE / 2 + 5 * sin(2 * PI * i / 360) - 1);
	}

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 0.5f);
	for (int i = 0; i < 360; ++i)
	{
		glVertex2f(x * CELL_SIZE + CELL_SIZE / 2 + 1.5 * cos(2 * PI * i / 360) - 2.5,
			y * CELL_SIZE + CELL_SIZE / 2 + 1.5 * sin(2 * PI * i / 360) - 2.5);
	}

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 360; ++i)
	{
		glVertex2f(x * CELL_SIZE + CELL_SIZE / 2 + 1 * cos(2 * PI * i / 360) - 3,
			y * CELL_SIZE + CELL_SIZE / 2 + 1 * sin(2 * PI * i / 360) - 3);
	}

	glEnd();
}

void Painter::DrawComplete(const char *text, int x, int y, int z, int u, int i, int j, int k)
{
	Game game;
	const char *scores = "scores: ";
	const char *time = "time: ";

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(CELL_SIZE * Game::FIELD_WIDTH, 0);
	glVertex2f(CELL_SIZE * Game::FIELD_WIDTH, CELL_SIZE * Game::FIELD_HEIGHT);
	glVertex2f(0, CELL_SIZE * Game::FIELD_HEIGHT);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2i(103 - x, 88);
	for (int i = 0; i < strlen(text); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	glRasterPos2i(90 - x, 180);
	for (int i = 0; i < strlen(scores); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, scores[i]);
	glRasterPos2i(90 - x, 200);
	for (int i = 0; i < strlen(time); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, time[i]);
	glRasterPos2f(144, 200);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + i);
	glRasterPos2f(152, 200);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + j);
	glRasterPos2f(160, 200);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + k);
	glRasterPos2f(144, 180);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + y);
	glRasterPos2f(152, 180);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + z);
	glRasterPos2f(160, 180);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + u);

}

void Painter::DrawOpenedCell(int x, int y)
{
	glColor3f(0.5f, 0.5f, 0.5f); //�����-�����
	glBegin(GL_QUADS);
	glVertex2f(x * CELL_SIZE, y * CELL_SIZE);
	glVertex2f((x + 1) * CELL_SIZE, y * CELL_SIZE);
	glVertex2f((x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
	glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE);
	glEnd();

	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_LINES); //��������� ����������� �����
	glVertex2f((x + 1) * CELL_SIZE - 1, y * CELL_SIZE);
	glVertex2f((x + 1) * CELL_SIZE - 1, (y + 1) * CELL_SIZE - 1);
	glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE - 1);
	glVertex2f((x + 1) * CELL_SIZE - 1, (y + 1) * CELL_SIZE - 1);
	glEnd();
}