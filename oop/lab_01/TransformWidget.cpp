#include "TransformWidget.h"

TransformWidget::TransformWidget(QWidget *parent)
	: QWidget(parent)
{
	QLabel *move_label = new QLabel(tr("Смещение вдоль осей координат"), this);
	QLabel *dx_label = new QLabel(tr("Вдоль OX:"), this);
	QLabel *dy_label = new QLabel(tr("Вдоль OY:"), this);
	QLabel *dz_label = new QLabel(tr("Вдоль OZ:"), this);

	QLabel *scale_label = new QLabel(tr("Масштабирование относительно центра фигуры"), this);
	QLabel *kx_label = new QLabel(tr("Вдоль OX:"), this);
	QLabel *ky_label = new QLabel(tr("Вдоль OY:"), this);
	QLabel *kz_label = new QLabel(tr("Вдоль OZ:"), this);

	QLabel *rotate_label = new QLabel(tr("Вращение относительно центра фигуры"), this);
	QLabel *xy_angle_label = new QLabel(tr("Угол поворота относительно OX:"), this);
	QLabel *yz_angle_label = new QLabel(tr("Угол поворота относительно OY:"), this);
	QLabel *xz_angle_label = new QLabel(tr("Угол поворота относительно OZ:"), this);
	dx_entry = new QLineEdit(this);
	dy_entry = new QLineEdit(this);
	dz_entry = new QLineEdit(this);
	dx_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	dy_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	dz_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	
	kx_entry = new QLineEdit(this);
	ky_entry = new QLineEdit(this);
	kz_entry = new QLineEdit(this);
	kx_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	ky_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	kz_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	
	xy_angle_entry = new QLineEdit(this);
	yz_angle_entry = new QLineEdit(this);
	xz_angle_entry = new QLineEdit(this);
	
	xy_angle_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	yz_angle_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	xz_angle_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	
	QPushButton *move_btn = new QPushButton("Переместить", this);
	QPushButton *scale_btn = new QPushButton("Масштабировать", this);
	QPushButton *rotate_btn = new QPushButton("Повернуть", this);
	QPushButton *load_from_btn = new QPushButton("Загрузить фигуру из файла", this);
	QPushButton *load_to_file_btn = new QPushButton("Сохранить фигуру в файл", this);

	connect(move_btn, SIGNAL(clicked()), this, SLOT(moveClicked()));
	connect(scale_btn, SIGNAL(clicked()), this, SLOT(scaleClicked()));
	connect(rotate_btn, SIGNAL(clicked()), this, SLOT(rotateClicked()));
	connect(load_from_btn, SIGNAL(clicked()), this, SLOT(loadFromClicked()));
	connect(load_to_file_btn, SIGNAL(clicked()), this, SLOT(loadToClicked()));

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	
	mainLayout->addWidget(move_label, 0, 0, 1, 3);

	mainLayout->addWidget(dx_label, 1, 0);
	mainLayout->addWidget(dx_entry, 1, 1, 1, 2);
	mainLayout->addWidget(dy_label, 2, 0);
	mainLayout->addWidget(dy_entry, 2, 1, 1, 2);
	mainLayout->addWidget(dz_label, 3, 0);
	mainLayout->addWidget(dz_entry, 3, 1, 1, 2);

	mainLayout->addWidget(move_btn, 4, 1);

	mainLayout->addWidget(scale_label, 6, 0, 1, 5);

	mainLayout->addWidget(kx_label, 7, 0);
	mainLayout->addWidget(kx_entry, 7, 1, 1, 2);
	mainLayout->addWidget(ky_label, 8, 0);
	mainLayout->addWidget(ky_entry, 8, 1, 1, 2);
	mainLayout->addWidget(kz_label, 9, 0);
	mainLayout->addWidget(kz_entry, 9, 1, 1, 2);

	mainLayout->addWidget(scale_btn, 10, 1);

	mainLayout->addWidget(rotate_label, 11, 0, 1, 4);

	mainLayout->addWidget(xy_angle_label, 12, 0);
	mainLayout->addWidget(xy_angle_entry, 12, 1, 1, 2);
	mainLayout->addWidget(yz_angle_label, 13, 0);
	mainLayout->addWidget(yz_angle_entry, 13, 1, 1, 2);
	mainLayout->addWidget(xz_angle_label, 14, 0);
	mainLayout->addWidget(xz_angle_entry, 14, 1, 1, 2);

	mainLayout->addWidget(rotate_btn, 15, 1);

	mainLayout->addWidget(load_from_btn, 17, 1);
	mainLayout->addWidget(load_to_file_btn, 17, 2);

	setLayout(mainLayout);

	setWindowTitle(tr("3D application"));
}

void TransformWidget::moveClicked()
{
    printf("Okaaaaaaaay\n");

	if (dx_entry->text().isEmpty())
		printf("Error\n");
	else
	{
    	double got = dx_entry->text().toDouble();
		printf("x = %lf\n", got);

	}
//	double got_x = this->dy_entry->text().toDouble();
}

void TransformWidget::scaleClicked()
{

}

void TransformWidget::loadToClicked()
{

}

void TransformWidget::rotateClicked()
{

}

void TransformWidget::loadFromClicked()
{

}
