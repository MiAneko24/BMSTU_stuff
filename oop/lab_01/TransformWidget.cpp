#include "TransformWidget.h"

TransformWidget::TransformWidget(QWidget *parent)
	: QWidget(parent)
{
	view = new FigureView(this, this->figure);
	//view->resize(500, 500);

	QLabel *move_label = new QLabel(tr("Смещение вдоль осей координат"), this);
	QLabel *dx_label = new QLabel(tr("Вдоль OX:"), this);
	QLabel *dy_label = new QLabel(tr("Вдоль OY:"), this);
	QLabel *dz_label = new QLabel(tr("Вдоль OZ:"), this);

	QLabel *scale_label = new QLabel(tr("Масштабирование относительно центра фигуры"), this);
	QLabel *kx_label = new QLabel(tr("Вдоль OX:"), this);
	QLabel *ky_label = new QLabel(tr("Вдоль OY:"), this);
	QLabel *kz_label = new QLabel(tr("Вдоль OZ:"), this);

	QLabel *rotate_label = new QLabel(tr("Вращение относительно центра фигуры (в углах)"), this);
	QLabel *xy_angle_label = new QLabel(tr("Поворот относительно OX:"), this);
	QLabel *yz_angle_label = new QLabel(tr("Поворот относительно OY:"), this);
	QLabel *xz_angle_label = new QLabel(tr("Поворот относительно OZ:"), this);
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
	QPushButton *load_from_btn = new QPushButton("Загрузить фигуру", this);
	QPushButton *load_to_file_btn = new QPushButton("Сохранить фигуру", this);

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
	mainLayout->addWidget(view, 0, 3, 17, 10);
	setLayout(mainLayout);

	setWindowTitle(tr("3D application"));
}

TransformWidget::~TransformWidget()
{
	make_action(this->figure, this->params, free_memory);
}

void TransformWidget::moveClicked()
{
    error_code result = no_errors;
	int i = 0;
	bool dx_empty = dx_entry->text().isEmpty();
	bool dy_empty = dy_entry->text().isEmpty();
	bool dz_empty = dz_entry->text().isEmpty();
	if (this->figure.points_amount == 0)
		result = error_void;
	else
	{
		if (dx_empty && dy_empty && dz_empty)
			result = error_input;
		if (!dx_empty)
		{
			this->params.move[i] = dx_entry->text().toDouble();
			i++;
		}
		else
		{
			this->params.move[i] = 0;
			i++;
		}
		if (!dy_empty)
		{
			this->params.move[i] = dy_entry->text().toDouble();
			i++;
		}
		else
		{
			this->params.move[i] = 0;
			i++;
		}
		if (!dz_empty)
		{
			this->params.move[i] = dz_entry->text().toDouble();
			i++;
		}
		else
		{
			this->params.move[i] = 0;
			i++;
		}
		if (!result)
		{
			result = make_action(this->figure, this->params, move_action);
		}
	}
	if (!result)
	{
		view->figure = figure;
		view->change_pic();
	}
	printf("error was %d\n", result);
//	double got_x = this->dy_entry->text().toDouble();
}

void TransformWidget::scaleClicked()
{
	error_code result = no_errors;
	int i = 0;
	bool kx_empty = kx_entry->text().isEmpty();
	bool ky_empty = ky_entry->text().isEmpty();
	bool kz_empty = kz_entry->text().isEmpty();
	if (this->figure.points_amount == 0)
	{
		if (kx_empty && ky_empty && kz_empty)
			result = error_input;
		if (!kx_empty)
		{
			this->params.k[i] = kx_entry->text().toDouble();
			i++;
		}
		else
		{
			this->params.k[i] = 0;
			i++;
		}
		if (!ky_empty)
		{
			this->params.k[i] = ky_entry->text().toDouble();
			i++;
		}
		else
		{
			this->params.k[i] = 0;
			i++;
		}
		if (!kz_empty)
		{
			this->params.k[i] = kz_entry->text().toDouble();
			i++;
		}
		else
		{
			this->params.k[i] = 0;
			i++;
		}
		if (!result)
		{
			result = make_action(this->figure, this->params, scale_action);
		}
	}
	if (!result)
	{
		view->figure = figure;
		view->change_pic();
	}
	printf("error was %d\n", result);
}

void TransformWidget::loadToClicked()
{
	error_code result = make_action(this->figure, this->params, save_model);

	printf("error was %d\n", result);
}

void TransformWidget::rotateClicked()
{
	error_code result = no_errors;
	int i = 0;
	bool xy_empty = xy_angle_entry->text().isEmpty();
	bool yz_empty = yz_angle_entry->text().isEmpty();
	bool xz_empty = xz_angle_entry->text().isEmpty();
	if (this->figure.points_amount == 0)
		result = error_void;
	else
	{
		if (xy_empty && yz_empty && xz_empty)
			result = error_input;
		if (!xy_empty)
		{
			this->params.angle[i] = xy_angle_entry->text().toDouble() * M_PI / 180;
			i++;
		}
		else
		{
			this->params.angle[i] = 0;
			i++;
		}
		if (!yz_empty)
		{
			this->params.angle[i] = yz_angle_entry->text().toDouble() * M_PI / 180;
			i++;
		}
		else
		{
			this->params.angle[i] = 0;
			i++;
		}
		if (!xz_empty)
		{
			this->params.angle[i] = xz_angle_entry->text().toDouble() * M_PI / 180;
			i++;
		}
		else
		{
			this->params.angle[i] = 0;
			i++;
		}
		if (!result)
		{
			result = make_action(this->figure, this->params, rotate_action);
		}
	}

	if (!result)
	{
		view->figure = figure;
		view->change_pic();
	}

	printf("error was %d\n", result);
}

void TransformWidget::loadFromClicked()
{
	error_code result = make_action(this->figure, this->params, get_model);
	
	if (!result)
	{
		view->figure = figure;
		view->change_pic();
	}
	printf("Error %d\n", result);
}
