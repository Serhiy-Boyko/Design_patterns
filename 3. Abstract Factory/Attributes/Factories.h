#pragma once
#include "Attributes.h"

// ���������� ������� ��� ����������� ��������
class Factory {
protected:
	std::string name; // ����� �����
public:
	Factory(std::string n) : name(n) {}
	std::string getName() { return name; }
	virtual Anthen *createAnthen() = 0;
	virtual  Flag  *createFlag() = 0;
	virtual Blazon *createBlazon() = 0;
	virtual ~Factory() {}
};

/* ������� ��� ��������� �������� ������ -
�� �������� ����������� ��������� ���������
������� � ����� �������� */
class UkrFactory : public Factory {
public:
	UkrFactory() : Factory("Ukraine") {}
	virtual Anthen *createAnthen() { return new UkrAnthen; }
	virtual  Flag  *createFlag() { return new UkrFlag; }
	virtual Blazon *createBlazon() { return new UkrBlazon; }
};

/* ������� ��� ��������� �������� ������ -
�� �������� ����������� ��������� ���������
������� � ����� �������� */
class PolFactory : public Factory {
public:
	PolFactory() : Factory("Poland") {}
	virtual Anthen *createAnthen() { return new PolAnthen; }
	virtual  Flag  *createFlag() { return new PolFlag; }
	virtual Blazon *createBlazon() { return new PolBlazon; }
};

/* ������� ��� ��������� �������� ������ -
�� �������� ����������� ��������� ���������
������� � ����� �������� */
class BolFactory : public Factory {
public:
	BolFactory() : Factory("Bulgaria") {}
	virtual Anthen *createAnthen() { return new BolAnthen; }
	virtual  Flag  *createFlag() { return new BolFlag; }
	virtual Blazon *createBlazon() { return new BolBlazon; }
};