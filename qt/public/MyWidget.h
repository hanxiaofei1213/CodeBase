#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: MyWidget.h
// Author: wangwenxi
// Date: 2022.07.15
// Comment: ���õ�widgetģ��
//////////////////////////////////////////////////////////////////////////
#include <QWidget>


class MyWidget : public QWidget {
	Q_OBJECT
public:
	MyWidget(QWidget* parent = nullptr);
	~MyWidget();

protected:
	void initUI();
	void initConnect();

private:


};

