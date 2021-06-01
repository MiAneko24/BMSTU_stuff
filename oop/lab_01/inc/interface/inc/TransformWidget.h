#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QRegExpValidator>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include "../../draw/drawer.h"
#include "../../facade/facade.hpp"

#define VALID_EXP "^([\\+ | \\-]?[1-9][0-9]*[\\.][0-9]*|0|[\\+ | \\-]?[0]{1}[\\.][0-9]*)"

class TransformWidget : public QWidget
{
	Q_OBJECT

private slots:
	void loadModelClicked();
	void removeModelClicked();
	void moveModelClicked();
	void scaleModelClicked();
	void rotateModelClicked();


	void addCameraClicked();
	void removeCameraClicked();
	void moveCameraClicked();
	void scaleCameraClicked();
	void rotateCameraClicked();

	void cameraChanged();
	void modelChanged();

public: 
	TransformWidget(QWidget *parent = nullptr);
	~TransformWidget();
	QLabel *modelBoxLabel;
	QComboBox *modelBox;
	QLabel *move_model_label;
	QLabel *dx_model_label;
	QLabel *dy_model_label;
	QLabel *dz_model_label;

	QLabel *scale_model_label;
	QLabel *kx_model_label;
	QLabel *ky_model_label;
	QLabel *kz_model_label;

	QLabel *rotate_model_label;
	QLabel *yz_angle_model_label;
	QLabel *xz_angle_model_label;
	QLabel *xy_angle_model_label;

	QLineEdit *dx_model_entry;
	QLineEdit *dy_model_entry;
	QLineEdit *dz_model_entry;

	QLineEdit *kx_model_entry;
	QLineEdit *ky_model_entry;
	QLineEdit *kz_model_entry;
	
	QLineEdit *xy_model_angle_entry;
	QLineEdit *yz_model_angle_entry;
	QLineEdit *xz_model_angle_entry;

	QPushButton *move_model_btn;
	QPushButton *scale_model_btn;
	QPushButton *rotate_model_btn;
	QPushButton *load_model;
	QPushButton *remove_model;

	QLabel *cameraBoxLabel;
	QComboBox *cameraBox;

	QLabel *move_camera_label;
	QLabel *dx_camera_label;
	QLabel *dy_camera_label;
	QLabel *dz_camera_label;

	QLabel *scale_camera_label;
	QLabel *kx_camera_label;
	QLabel *ky_camera_label;
	QLabel *kz_camera_label;

	QLabel *rotate_camera_label;
	QLabel *yz_angle_camera_label;
	QLabel *xz_angle_camera_label;
	QLabel *xy_angle_camera_label;
	
	QLineEdit *dx_camera_entry;
	QLineEdit *dy_camera_entry;
	QLineEdit *dz_camera_entry;

	QLineEdit *kx_camera_entry;
	QLineEdit *ky_camera_entry;
	QLineEdit *kz_camera_entry;
	
	QLineEdit *xy_camera_angle_entry;
	QLineEdit *yz_camera_angle_entry;
	QLineEdit *xz_camera_angle_entry;

	QPushButton *load_scene;
	QPushButton *add_camera;
	QPushButton *remove_camera;
	QPushButton *move_camera_btn;
	QPushButton *scale_camera_btn;
	QPushButton *rotate_camera_btn;

	QGraphicsView *graphicsView;

	QGridLayout *mainLayout;

	private:
		QGraphicsScene *scene;
		std::shared_ptr<Facade> facade;
		std::shared_ptr<Drawer> drawer;
};

#endif