#pragma once
#include <iostream>

/* ��������� ����� ����� ��������,
�� ������������ ������ �������� -
����� ���'����, ��� � �� ��������� ������������� */
class Anthen { // ���
public:
	virtual void Info() = 0;
};

class Flag { // ������
public:
	virtual void Info() = 0;
};

class Blazon { // ����
public:
	virtual void Info() = 0;
};

/* ��� ����� �������� ������, �� ������������ ������ �������� -
����� ���'����, ��� � �� ��������� ������������� */
class UkrAnthen : public Anthen {
public:
	virtual void Info() { std::cout << " �� �� ������ ������ " << std::endl; }
};

class UkrFlag : public Flag {
public:
	virtual void Info() { std::cout << " ��������-������ "; }
};

class UkrBlazon : public Blazon {
public:
	virtual void Info() { std::cout << " ������ "; }
};

/* ��� ����� �������� ������, �� ������������ ������ �������� -
����� ���'����, ��� � �� ��������� ������������� */
class PolAnthen : public Anthen {
public:
	virtual void Info() {std::cout << " ��� ������ �� ��i����� " << std::endl;}
};

class PolFlag : public Flag {
public:
	virtual void Info() { std::cout << " �i��-�������� "; }
};

class PolBlazon : public Blazon {
public:
	virtual void Info() { std::cout << " �i��� ���� "; }
};

/* ��� ����� �������� ������, �� ������������ ������ �������� -
����� ���'����, ��� � �� ��������� ������������� */
class BolAnthen : public Anthen {
public:
	virtual void Info() { std::cout << " ���� ������ " << std::endl; }
};

class BolFlag : public Flag {
public:
	virtual void Info() { std::cout << " �i��-������-�������� "; }
};

class BolBlazon : public Blazon {
public:
	virtual void Info() { std::cout << " ������� ��� "; }
};