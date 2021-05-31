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

private slots:
	void loadToClicked();
	void loadFromClicked();
	void moveClicked();
	void scaleClicked();
	void rotateClicked();

public: 
	TransformWidget(QWidget *parent = nullptr);
	~TransformWidget();
	void error_hadling(error_code &result);
	changes_params_t params;
	QLabel *move_label;
	QLabel *dx_label;
	QLabel *dy_label;
	QLabel *dz_label;

	QLabel *scale_label;
	QLabel *kx_label;
	QLabel *ky_label;
	QLabel *kz_label;

	QLabel *rotate_label;
	QLabel *yz_angle_label;
	QLabel *xz_angle_label;
	QLabel *xy_angle_label;

	QLabel *file_label;

	QLineEdit *dx_entry;
	QLineEdit *dy_entry;
	QLineEdit *dz_entry;

	QLineEdit *kx_entry;
	QLineEdit *ky_entry;
	QLineEdit *kz_entry;
	
	QLineEdit *xy_angle_entry;
	QLineEdit *yz_angle_entry;
	QLineEdit *xz_angle_entry;
	
	QLineEdit *file_entry;

	QPushButton *move_btn;
	QPushButton *scale_btn;
	QPushButton *rotate_btn;
	QPushButton *load_from_btn;
	QPushButton *load_to_file_btn;

	QGridLayout *mainLayout;
	FigureView *view;
};

#endif