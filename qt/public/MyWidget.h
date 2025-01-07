#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: MyWidget.h
// Author: wangwenxi
// Date: 2022.07.15
// Comment: 常用的widget模板
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

