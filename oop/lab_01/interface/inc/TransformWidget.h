#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QRegExpValidator>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMessageBox>
#include "FigureView.h"
#define VALID_EXP "^([\\+ | \\-]?[1-9][0-9]*[\\.][0-9]*|0|[\\+ | \\-]?[0]{1}[\\.][0-9]*)"

class TransformWidget : public QWidget
{
	Q_OBJECT

//private: 

private slots:
	void loadToClicked();
	void loadFromClicked();
	void moveClicked();
	void scaleClicked();
	void rotateClicked();

//protected:


public: 
	TransformWidget(QWidget *parent = nullptr);
	~TransformWidget();
	void error_hadling(error_code &result);
	changes_params_t params;
	math_model_t figure;
	QLineEdit *dx_entry;
	QLineEdit *dy_entry;
	QLineEdit *dz_entry;
	QLineEdit *kx_entry;
	QLineEdit *ky_entry;
	QLineEdit *kz_entry;
	QLineEdit *xy_angle_entry;
	QLineEdit *yz_angle_entry;
	QLineEdit *xz_angle_entry;
	FigureView *view;

};

#endif